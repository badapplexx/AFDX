//
// Copyright (C) 2022 Ipek Gokce
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//

#include "SkewMaxTester.h"

namespace afdx {

Define_Module(SkewMaxTester);

void SkewMaxTester::initialize()
{
    // TODO - Generated method body
    isSkewMaxTestEnabled = par("skewMaxTestEnabled");
}

void SkewMaxTester::handleMessage(cMessage *msg)
{
    if (!isSkewMaxTestEnabled) {
        // received on Ethernet in port
        if (msg->arrivedOn("in_A")) {
            send(msg, "out_fromA");
        }
        else {
            send(msg, "out_fromB");
        }
    }
    else {

        cGate *ethOutGateA = gate("out_fromA");
        cGate *ethOutGateB = gate("out_fromB");

        std::string networkString = "";
        if (msg->arrivedOn("in_A")) {
            networkString = "NW-A";
        }
        else {
            networkString = "NW-B";
        }
        static int lastSentFrom = 0;
        afdx::AFDXMessage *afdxMsg = check_and_cast<afdx::AFDXMessage*>(msg);
        int seqNo = afdxMsg->getSeqNum();
        int vlid = afdxMsg->getVirtualLinkId();
        if (vlid == 1) {
            if (seqNo == 50) {
                if (0 == lastSentFrom) {
                    if (msg->arrivedOn("in_A")) {
                        lastSentFrom = 1;
                        send(msg, ethOutGateA);
                        std::cout << simTime() << "|SkewTester|Forwarding (SN: " << seqNo << "):NW-A" << endl;
                        return;
                    }
                    else if (msg->arrivedOn("in_B")) {
                        lastSentFrom = 2;
                        send(msg, ethOutGateB);
                        std::cout << simTime() << "|SkewTester|Forwarding (SN: " << seqNo << "):NW-B" << endl;
                        return;
                    }
                }
                else {
                    std::cout << simTime() << "|SkewTester|Deleted (SN: " << seqNo << ")" << endl;
                    return;
                }
            }
            else if (seqNo > 50 && seqNo < 65) {
                std::cout << simTime() << "|SkewTester|Deleted (SN: " << seqNo << "):" << networkString << endl;
                delete msg;
                return;
            }
            else if (seqNo == 65) {
                if (lastSentFrom == 1) {
                    std::cout << simTime() << "|SkewTester|Changed (SN: " << seqNo << " -> ";
                    afdxMsg->setSeqNum(50);
                    send(msg, ethOutGateB);
                    lastSentFrom = 2;
                    std::cout << afdxMsg->getSeqNum() << "):NW-B" << endl;
                    return;
                }
                else if (lastSentFrom == 2) {
                    std::cout << simTime() << "|SkewTester|Changed (SN: " << seqNo << " -> ";
                    afdxMsg->setSeqNum(50);
//					sentOrDeleted = true;
                    send(msg, ethOutGateA);
                    lastSentFrom = 1;
                    std::cout << afdxMsg->getSeqNum() << "):NW-A" << endl;
                    return;
                }
            }
            else {
                lastSentFrom = 0;
            }
        }

        if (msg->arrivedOn("in_A")) {
            if (vlid == 1) {
                std::cout << simTime() << "|SkewTester|Forwarding (SN: " << seqNo << "):NW-A" << endl;
            }
            cGate *ethOutGate = gate("out_fromA");
            send(msg, ethOutGate);
        }
        else if (msg->arrivedOn("in_B")) {
            if (vlid == 1) {
                std::cout << simTime() << "|SkewTester|Forwarding (SN: " << seqNo << "):NW-B" << endl;
            }
            cGate *ethOutGate = gate("out_fromB");
            send(msg, ethOutGate);
        }
        else {
            delete (msg);
        }

    }
}

} //namespace
