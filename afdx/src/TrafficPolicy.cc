//
// Copyright (C) 2013 OpenSim Ltd.
// Copyright (C) 2021 Emre Atik
// Copyright (C) 2022 Ipek Gokce
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//

/*
 * TODO Byte-based/frame-based filtering selection can be added.
 * In this model byte-based is applied. ACi is decreased as received frame's size each, not Smax.
 * */
#include "TrafficPolicy.h"
#include "AFDXMessage_m.h"

namespace afdx {

Define_Module(TrafficPolicy);

void TrafficPolicy::initialize()
{
    bandwidthMbps = par("bandwidth").intValue();
    minJitter = par("minJitter").doubleValue();
    minJitter /= 1000;
}

void TrafficPolicy::handleMessage(cMessage *msg)
{
    const int phyOverhead_bit = 20 * 8;
    AFDXMessage *afdxMessage = check_and_cast<AFDXMessage*>(msg);
    int VLid = afdxMessage->getVirtualLinkId();
    int rho_bit = (afdxMessage->getRho()); // rho: mb/sec
    int sigma_bit = afdxMessage->getSigma();
    int frameSize_bit = afdxMessage->getBitLength() + phyOverhead_bit;
    double obtainedCredit_bit = 0;
    bool isTokenSufficient = true;
    TokenBucketMap_t::iterator itr = tokenBucket.find(VLid);

    bool isRecordCreditEnabled = false;
    NetworkStatistics::SwitchDefinition sw = NetworkStatistics::getInstance()->getSwitchDefinition(this);
    if (NetworkStatistics::getInstance()->isInSwitchAPort(sw)) {
        isRecordCreditEnabled = true;
    }

    double timeDiff_s = 0;
    if (itr == tokenBucket.end()) {
        tokenBucket[VLid] = sigma_bit;
        if (isRecordCreditEnabled)
            afdx::NetworkStatistics::getInstance()->record(CREDIT_PER_VL_PER_SW, afdxMessage->getVirtualLinkId(),
                    tokenBucket[VLid], sw.index);
    }
    else {
        timeDiff_s = simTime().dbl() - lastTime[VLid];
        obtainedCredit_bit = timeDiff_s * rho_bit;

        if (tokenBucket[VLid] + obtainedCredit_bit > sigma_bit) {
            tokenBucket[VLid] = sigma_bit;
        }
        else {
            tokenBucket[VLid] += obtainedCredit_bit;
        }
        if (isRecordCreditEnabled)
            afdx::NetworkStatistics::getInstance()->record(CREDIT_PER_VL_PER_SW, afdxMessage->getVirtualLinkId(),
                    tokenBucket[VLid], sw.index);
    }
    if (tokenBucket[VLid] < frameSize_bit) {
        isTokenSufficient = false;
        int diff = tokenBucket[VLid] - frameSize_bit;
        if (isRecordCreditEnabled) {
            afdx::NetworkStatistics::getInstance()->record(CREDIT_PER_VL_PER_SW, afdxMessage->getVirtualLinkId(), diff,
                    sw.index);
            afdx::NetworkStatistics::getInstance()->record(CREDIT_PER_VL_PER_SW, afdxMessage->getVirtualLinkId(),
                    tokenBucket[VLid], sw.index);
        }
    }
    else {
        tokenBucket[VLid] -= frameSize_bit;
        if (isRecordCreditEnabled)
            afdx::NetworkStatistics::getInstance()->record(CREDIT_PER_VL_PER_SW, afdxMessage->getVirtualLinkId(),
                    tokenBucket[VLid], sw.index);
    }

    if (isTokenSufficient) {
        send(msg, "out");
    }
    else {
        if (isRecordCreditEnabled)
            NetworkStatistics::getInstance()->record(afdx::DROPPED_FRAMES_TRAFFIC_POLICY_PER_VL,
                    afdxMessage->getVirtualLinkId(), sw.index);
        std::cout << "TOKEN_INSUFFICIENT (VL:" << VLid << ") SW:" << sw.index << endl;
        delete msg;
    }
    lastTime[VLid] = simTime().dbl();
}

}
;
// namespace afdx

