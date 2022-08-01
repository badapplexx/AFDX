//
// Copyright (C) 2013 OpenSim Ltd.
// Copyright (C) 2022 Ipek Gokce
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//

#include "Source_ext.h"

namespace afdx {

Define_Module(Source_ext);

void Source_ext::initialize()
{
    this->jobCounter = 0;
    this->startTime = par("startTime");
    this->stopTime = par("stopTime");
    this->numJobs = par("numJobs");
    this->baudrate = par("baudrate");
    Source::initialize();
}

void Source_ext::handleMessage(cMessage *msg)
{
    ASSERT(msg->isSelfMessage());

    // reschedule the timer for the next message
    if ((this->numJobs < 0 || this->numJobs > jobCounter) && (this->stopTime < 0 || this->stopTime > simTime())) {
        scheduleAt(simTime() + par("interArrivalTime"), msg);

        if (this->baudrate == 0) {
            SendOptions so;
            so.duration(SIMTIME_ZERO);
            send(this->createJob(), so, "out");
        }
        else {
            send(this->createJob(), "out");
        }
    }
    else {
        delete msg;
    }
}

Job* Source_ext::createJob()
{
    SubsystemMessage *msg = new SubsystemMessage();
    msg->setPriority(par("jobPriority").intValue());
    msg->setPacketLength(par("packetLength").intValue());
    msg->setPartitionId(par("partitionId").intValue());
    this->jobCounter++;

    return msg;
}
}
;
// namespace afdx

