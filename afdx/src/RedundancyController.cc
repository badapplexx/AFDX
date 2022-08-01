//
// Copyright (C) 2013 OpenSim Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//

#include "RedundancyController.h"
#include "AFDXMessage_m.h"

#define APPLY_FAULTY_PACKET_TEST    0

namespace afdx {

Define_Module(RedundancyController);
void RedundancyController::initialize()
{
    isNetworkA_Enabled = par("copyToLinkA");
    isNetworkB_Enabled = par("copyToLinkB");
}

void RedundancyController::handleMessage(cMessage *msg)
{
    AFDXMessage *afdxMsg = check_and_cast<AFDXMessage*>(msg);
    int vlId = afdxMsg->getVirtualLinkId();
    afdxMsg->setSeqNum(seqNum[vlId]);

    afdxMsg->setRegLogExitTime(simTime());
    simtime_t bagLatency = simTime() - afdxMsg->getRegLogEntryTime();
    NetworkStatistics::getInstance()->record(ES_BAG_LATENCY_PER_VL, vlId, bagLatency.dbl());

    if (isNetworkA_Enabled) {
        afdxMsg->setInterfaceId(1);     // set to 1 for interface A
        send((cMessage*) afdxMsg, "outA");
        if (isNetworkB_Enabled) {
            AFDXMessage *afdxMsg2 = check_and_cast<AFDXMessage*>(msg->dup());
            afdxMsg2->setInterfaceId(2);    // set to 2 for interface B
            send((cMessage*) afdxMsg2, "outB");
        }
    }
    else if (isNetworkB_Enabled) {
        afdxMsg->setInterfaceId(2);     // set to 2 for interface B
        send((cMessage*) afdxMsg, "outB");
    }
    else {
        error("redundancy controller has no enabled output");
    }
    if (++seqNum[vlId] > 255) {
        // wrap around the sequence number according to the specification
        seqNum[vlId] = 1;
    }
}

}
;

// namespace afdx

