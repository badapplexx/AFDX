//
// Copyright (C) 2013 OpenSim Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//

#include "RegulatorLogic.h"

namespace afdx {

Define_Module(RegulatorLogic);

void RegulatorLogic::initialize()
{
    this->maxVLIDQueueSize = par("maxVLIDQueueSize");
}

void RegulatorLogic::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage()) {
        //Let's say a message is received & bag_queue[vlid] was empty -> afdxMsg is sent out.
        //In this case a self message is scheduled for BAG time later. When received, bag_queue will be checked for any other messages that
        //might have received in the mean time.
        int vlId = msg->getKind();
        if (bagQueue[vlId].empty()) {
            // no messages received in the mean time
            bagFlagsPerVL[vlId] = 0;
            delete msg;

        }
        else // some message received in the mean time.
        {
            // Pop and send that message
            // Schedule a self message for bag time later to process further messages(if any)
            AFDXMessage *afdx_msg = check_and_cast<AFDXMessage*>(bagQueue[vlId].front());
            double BAG = afdx_msg->getBagValue();
            send(bagQueue[vlId].front(), "out");

            std::string id = std::to_string(afdx_msg->getId());
            bagQueue[vlId].pop();
            scheduleAt(simTime() + BAG, msg);
        }
    }
    else {
        //If queue is already empty, send message directly and schedule a self message for BAG time later. In the mean time:
        // if message received, push to queue and wait for scheduled self message to come.
        // else, bag_flags_per_vl[ vl_id ] flag will be cleaned by the code above
        AFDXMessage *afdx_msg = check_and_cast<AFDXMessage*>(msg);
        afdx_msg->setRegLogEntryTime(simTime());
        int vlId = afdx_msg->getVirtualLinkId();

        BagFlagsPerVL_t::iterator itr = bagFlagsPerVL.find(vlId);
        if ((itr != bagFlagsPerVL.end()) && (bagFlagsPerVL[vlId] == 1)) {
            //Queue is not empty! Push and wait for already scheduled self-message to be sent after BAG(s) of time.

            //03.05.2022 update
            if (bagQueue[vlId].size() >= this->maxVLIDQueueSize) {
                throw std::runtime_error(
                        std::string("Max limit for VLID queue is reached.(vlid:" + std::to_string(vlId) + ")"));
            }

            bagQueue[vlId].push(msg);
        }
        else	//This is the first message for this VLID or queue is empty
        {
            bagFlagsPerVL[vlId] = 1; //raise the flag to notify upper code about there is a message in the queue

            cMessage *bagTimer = new cMessage("bag_timer");
            bagTimer->setKind(vlId);
            scheduleAt(simTime() + afdx_msg->getBagValue(), bagTimer);

            send(msg, "out"); //send away! Nothing to wait :)
        }
    }
}

}
;
// namespace afdx

