//
// Copyright (C) 2013 OpenSim Ltd.
// Copyright (C) 2021 Emre Atik
// Copyright (C) 2022 Ipek Gokce
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//

#include "RedundancyChecker.h"
#include "AFDXMessage_m.h"

namespace afdx {

Define_Module(RedundancyChecker);

void RedundancyChecker::initialize()
{
    this->isEnabled = par("enabled");
    this->skewMax = par("skewMax");
}

void RedundancyChecker::handleMessage(cMessage *msg)
{
    // if not enabled just pass through all frames received
    if (!isEnabled) {
        send(msg, "out");
    }
    else // filter out redundant messages
    {
        std::string nwString = "";
        if (msg->arrivedOn("inA")) {
            nwString = "NW-A";
        }
        else {
            nwString = "NW-B";
        }
        AFDXMessage *afdxMsg = check_and_cast<AFDXMessage*>(msg);
        int vlid = afdxMsg->getVirtualLinkId();
        int currSeqNum = afdxMsg->getSeqNum();

        if (previousSeqNo.end() == previousSeqNo.find(vlid)) {
            previousSeqNo[vlid] = -1;
        }

        // drop the frame if the seqNum is smaller than the one we are expecting
        // and the last frame was received recently (less than skewMax time ago)

        if (currSeqNum == previousSeqNo[vlid]) {
            //same frame again
            if ((simTime() - lastFrameReceived[vlid] <= skewMax)) {
                //less than skewMax time has passed
                delete msg;
            }
            else {
                send(msg, "out");
            }
        }
        else {
            send(msg, "out");
        }
        lastFrameReceived[vlid] = simTime();
        previousSeqNo[vlid] = currSeqNum;
    }
}
}

// namespace afdx

