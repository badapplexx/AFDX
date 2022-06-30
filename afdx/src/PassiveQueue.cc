//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 2006-2015 OpenSim Ltd.
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//

#include "PassiveQueue.h"
#include "Job.h"
#include "IServer.h"

#ifdef AFDX_PQ
namespace afdx
#else
namespace queueing
#endif
{
Define_Module(PassiveQueue);
PassiveQueue::~PassiveQueue()
{
    delete selectionStrategy;
}

void PassiveQueue::initialize()
{
    capacity = par("capacity");
    queue.setName("queue");
    fifo = par("fifo");

    selectionStrategy = SelectionStrategy::create(par("sendingAlgorithm"), this, false);
    if (!selectionStrategy) {
        throw cRuntimeError("invalid selection strategy");
    }

#ifdef AFDX_PQ
    afdx::NetworkStatistics::SwitchDefinition sw = afdx::NetworkStatistics::getInstance()->getSwitchDefinition(this);
    if (afdx::NetworkStatistics::getInstance()->isInSwitchAPort(sw)) {
        this->swPortIndex = this->getParentModule()->getIndex(); //switch port index
        afdx::NetworkStatistics::getInstance()->createRecorder(afdx::SWITCH_QUEUE_LENGTH_PER_SWITCH, sw);
        afdx::NetworkStatistics::getInstance()->createQueueLengthCounter(sw);
        afdx::NetworkStatistics::getInstance()->createRecorder(afdx::SWITCH_QUEUEING_TIME_PER_SWITCH, sw);
        afdx::NetworkStatistics::getInstance()->createRecorder(SWITCH_QUEUE_LENGTH_PER_VL_PER_SW, sw,
                this->swPortIndex);
    }
#else
	droppedSignal = registerSignal("dropped");
	queueingTimeSignal = registerSignal("queueingTime");
	queueLengthSignal = registerSignal("queueLength");
	emit(queueLengthSignal, 0);
#endif

}

void PassiveQueue::handleMessage(cMessage *msg)
{
    Job *job = check_and_cast<Job*>(msg);

#ifdef AFDX_PQ
    NetworkStatistics::SwitchDefinition sw = NetworkStatistics::getInstance()->getSwitchDefinition(this);
    bool isSWAPort = NetworkStatistics::getInstance()->isInSwitchAPort(sw);
#else
	job->setTimestamp();
	#endif

    // check for container capacity
    if (capacity >= 0 && queue.getLength() >= capacity) {
        EV << "Queue full! Job dropped.\n";
        if (hasGUI()) {
            bubble("Dropped!");
        }
#ifdef AFDX_PQ
        afdx::AFDXMessage *afdxMsg = check_and_cast<afdx::AFDXMessage*>(msg);
        if (isSWAPort) {
            afdx::NetworkStatistics::getInstance()->record(afdx::DROPPED_FRAMES_IN_QUEUE_PER_VL,
                    afdxMsg->getVirtualLinkId(), this->getIndex());
        }
#else
		emit(droppedSignal, 1);
		#endif
        delete msg;
        return;
    }

#ifdef AFDX_PQ
    afdx::AFDXMessage *afdxMsg = check_and_cast<afdx::AFDXMessage*>(msg);
    if (isSWAPort) {
        job->setTimestamp();
    }
#endif

    int k = selectionStrategy->select();
    if (k < 0) // enqueue if no idle server found
            {
        queue.insert(job);
#ifdef AFDX_PQ
        //isSWA check is already included in the record and increase functions.

        if (isSWAPort) {
            int qLen = afdx::NetworkStatistics::getInstance()->getQueueLengthCount(sw);
            afdx::NetworkStatistics::getInstance()->record(afdx::SWITCH_QUEUE_LENGTH_PER_SWITCH, sw, qLen);
            afdx::NetworkStatistics::getInstance()->record(afdx::SWITCH_QUEUE_LENGTH_PER_VL_PER_SW, sw, qLen,
                    this->swPortIndex);

            afdx::NetworkStatistics::getInstance()->increaseQueueLengthCount(sw);
            qLen = afdx::NetworkStatistics::getInstance()->getQueueLengthCount(sw);

            afdx::NetworkStatistics::getInstance()->record(afdx::SWITCH_QUEUE_LENGTH_PER_SWITCH, sw, qLen);
            afdx::NetworkStatistics::getInstance()->record(afdx::SWITCH_QUEUE_LENGTH_PER_VL_PER_SW, sw, qLen,
                    this->swPortIndex);
        }

#else
		emit(queueLengthSignal, length());
		job->setQueueCount(job->getQueueCount() + 1);
		#endif
    }
    else if (length() == 0) // send through without queueing
            {
        sendJob(job, k);
#ifdef AFDX_PQ
        if (isSWAPort) {
            afdx::NetworkStatistics::getInstance()->record(afdx::SWITCH_QUEUEING_TIME_PER_VL_PER_SW,
                    afdxMsg->getVirtualLinkId(), 0, sw.index);
            afdx::NetworkStatistics::getInstance()->record(afdx::SWITCH_QUEUEING_TIME_PER_SWITCH, sw, 0);

            int qLen = afdx::NetworkStatistics::getInstance()->getQueueLengthCount(sw);
            afdx::NetworkStatistics::getInstance()->record(afdx::SWITCH_QUEUE_LENGTH_PER_SWITCH, sw, qLen);
            afdx::NetworkStatistics::getInstance()->record(afdx::SWITCH_QUEUE_LENGTH_PER_VL_PER_SW, sw, qLen,
                    this->swPortIndex);
        }
#endif
    }
    else
        throw cRuntimeError("This should not happen. Queue is NOT empty and there is an IDLE server attached to us.");
}

void PassiveQueue::refreshDisplay() const
{
    // change the icon color
    getDisplayString().setTagArg("i", 1, queue.isEmpty() ? "" : "cyan");
}

int PassiveQueue::length()
{
    return queue.getLength();
}

void PassiveQueue::request(int gateIndex)
{
    Enter_Method("request()!");
    ASSERT(!queue.isEmpty());
    Job *job;

#ifdef AFDX_PQ
    NetworkStatistics::SwitchDefinition sw = NetworkStatistics::getInstance()->getSwitchDefinition(this);
    bool isSWAPort = NetworkStatistics::getInstance()->isInSwitchAPort(sw);
#endif

    if (fifo) {
        job = (Job*) queue.pop();
    }
    else {
        job = (Job*) queue.back();
        queue.remove(job); // FIXME this may have bad performance as remove uses linear search
    }
#ifdef AFDX_PQ
    if (isSWAPort) {
        simtime_t d = simTime() - job->getTimestamp();
        job->setTotalQueueingTime(job->getTotalQueueingTime() + d);
        afdx::AFDXMessage *afdxMsg = check_and_cast<afdx::AFDXMessage*>(job);

        afdx::NetworkStatistics::getInstance()->record(afdx::SWITCH_QUEUEING_TIME_PER_VL_PER_SW,
                afdxMsg->getVirtualLinkId(), job->getTotalQueueingTime().dbl(), sw.index);
        afdx::NetworkStatistics::getInstance()->record(afdx::SWITCH_QUEUEING_TIME_PER_SWITCH, sw,
                job->getTotalQueueingTime().dbl());

        int qLen = afdx::NetworkStatistics::getInstance()->getQueueLengthCount(sw);
        afdx::NetworkStatistics::getInstance()->record(afdx::SWITCH_QUEUE_LENGTH_PER_SWITCH, sw, qLen);
        afdx::NetworkStatistics::getInstance()->record(afdx::SWITCH_QUEUE_LENGTH_PER_VL_PER_SW, sw, qLen,
                this->swPortIndex);
        afdx::NetworkStatistics::getInstance()->decreaseQueueLengthCount(sw);
        afdx::NetworkStatistics::getInstance()->record(afdx::SWITCH_QUEUE_LENGTH_PER_SWITCH, sw, qLen);
        afdx::NetworkStatistics::getInstance()->record(afdx::SWITCH_QUEUE_LENGTH_PER_VL_PER_SW, sw, qLen,
                this->swPortIndex);
    }
#else
	emit(queueLengthSignal, length());
	job->setQueueCount(job->getQueueCount()+1);
	simtime_t d = simTime() - job->getTimestamp();
	job->setTotalQueueingTime(job->getTotalQueueingTime() + d);
	emit(queueingTimeSignal, d);
	#endif
    sendJob(job, gateIndex);
}

void PassiveQueue::sendJob(Job *job, int gateIndex)
{
    cGate *out = gate("out", gateIndex);
    send(job, out);
    check_and_cast<IServer*>(out->getPathEndGate()->getOwnerModule())->allocate();
}

}
;
//namespace

