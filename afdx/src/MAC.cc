//
// Copyright (C) 2013 OpenSim Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//

#include "MAC.h"
#include "IPassiveQueue.h"

namespace afdx {

Define_Module(MAC);

MAC::MAC()
{
    this->selectionStrategy = NULL;
    this->isReserved = false;
    this->endServiceMsg = NULL;
}

MAC::~MAC()
{
    delete selectionStrategy;
    cancelAndDelete(endServiceMsg);
}

void MAC::initialize()
{
    this->endServiceMsg = new cMessage("end-tx");
    this->isReserved = false;
    this->selectionStrategy = queueing::SelectionStrategy::create(par("fetchingAlgorithm"), this, true);
    if (!selectionStrategy) {
        error("invalid selection strategy");
    }
    this->maxFrameAge = 1000; //par("maxFrameAge");//ip
}

//when the passive queue block who is connected to this server(MAC) has a new message to send,
//it first tries to select and in select() there is a isIdle() call. If MAC is not idle, queue won't send message and will
//wait for a request() call
//tl;dr: Check IServer.h for usage.
bool MAC::isIdle()
{
    return !(this->isReserved);
}

void MAC::allocate()
{
    Enter_Method("allocate()"); //ip. Calls IServer.reserve()
    if (isReserved) {
        error("trying to reserve a server which is already reserved");
    }
    this->isReserved = true;
}
/*
 * As long as a real message is received, this function will work periodically.
 * It keeps schedule'in endServiseMsgs whether when an error occured or the message sent-out successfully.
 * If an error occurs, it schedules an endServiceMsg. And this action will request a message from a the queue(block next door) which leads to a trigger from port in
 * */
void MAC::handleMessage(cMessage *msg)
{
    std::string blockName = (this->getParentModule()->getParentModule())->getName();
    AFDXMessage *afdxMsg;

    // serviceMessage.
    // tx end. Free up the interface and request additional frames if any
    if (msg == endServiceMsg) {
        ASSERT(isReserved);
        this->isReserved = false;

        int gateNumber = this->selectionStrategy->select(); // examine all input queues, and request a new frame from a non empty queue
        if (gateNumber >= 0) {
            EV << "requesting frame from queue " << gateNumber << endl;
            cGate *gate = selectionStrategy->selectableGate(gateNumber);
            check_and_cast<queueing::IPassiveQueue*>(gate->getOwnerModule())->request(gate->getIndex());
            this->isReserved = true;
        }
        return;
    }
    else {
        afdxMsg = check_and_cast<afdx::AFDXMessage*>(msg);
    }

    // received on Ethernet in port
    if (msg->arrivedOn("eth$i")) {
        // Decapsulation
        cPacket *cpkt = check_and_cast<cPacket*>(msg);
        cpkt->setByteLength(cpkt->getByteLength() - 7 - 1); // decrease the size (PREAMBLE + SFD)
        msg->setTimestamp(); // store the current timestamp (the time of last bit received). Can be used to drop timed out frames
        send(msg, "out"); 		// send out to upper layers
        return; // do not allow a fall-back because msg->arrivedOn("in") would return now true (we already sent out the message)
    }

    // frame to be sent to Ethernet out port
    if (msg->arrivedOn("in")) {
        if (!isReserved) {
            error("frame arrived but the MAC was not correctly reserved");
        }

        cGate *ethOutGate = gate("eth$o");
        if (!ethOutGate->isPathOK()) {
            EV << "dropping frame. " << getParentModule()->getFullName() << " is not connected. " << endl;
            scheduleAt(simTime(), this->endServiceMsg); // reschedule the message for now, try to get an other frame
            delete msg;
            return;
        }

        cDatarateChannel *drChan = check_and_cast<cDatarateChannel*>(ethOutGate->getTransmissionChannel());
        if (drChan->isBusy()) {
            error("trying to send out on a transmission line while the line is busy");
        }

        if (drChan->isDisabled()) {
            EV << "dropping frame. Channel is disabled. " << endl;
            scheduleAt(simTime(), endServiceMsg); // reschedule the message for now, try to get an other frame
            delete msg;
            return;
        }

        // Encapsulation
        cPacket *cpkt = check_and_cast<cPacket*>(msg);
        cpkt->addByteLength(7 + 1);  // increase length with (PREAMBLE + SFD)

        this->isReserved = true;  // reserve the transmitter and send out (start sending) the frame

        send(msg, ethOutGate);

        // we have scheduled the message so we can get back the transmission finish time now
        // check for frames that are too old
        simtime_t frame_age = drChan->getTransmissionFinishTime() - msg->getTimestamp();
        if (frame_age > maxFrameAge) {
            EV << "dropping frame. It is too old: " << frame_age << "s" << endl;
            cancelAndDelete(msg);
            scheduleAt(simTime(), endServiceMsg); // reschedule the message for now, try to get an other frame
            return;
        }
        // calculate inter-frame gap (12byte) and add it to the processing time
        simtime_t IFG_TIME = 12 * 8 / drChan->getDatarate();
        scheduleAt(drChan->getTransmissionFinishTime() + IFG_TIME, endServiceMsg);

        //The MAC in the end-system is called "macA" or "macB". The one in the is named as "mac".
        if (0 == strcmp(this->getName(), "macA")) {
            //END-SYSTEM ONLY

            simtime_t estotalLat = simTime() - afdxMsg->getCreationTime();
            NetworkStatistics::getInstance()->record(ES_TOTAL_LATENCY_PER_VL, afdxMsg->getVirtualLinkId(),
                    estotalLat.dbl());

            //BAG latency is not included in scheduling latency, it is measured separately.
            // scheduling latency is the time difference between EndSystem output and RegulatorLogic output
            simtime_t schedLatency = simTime() - afdxMsg->getRegLogExitTime();
            NetworkStatistics::getInstance()->record(ES_SCHEDULING_LATENCY_PER_VL, afdxMsg->getVirtualLinkId(),
                    schedLatency.dbl());
        }
        return;
    }
}

}

// namespace afdx
