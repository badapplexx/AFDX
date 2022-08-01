//
// Copyright (C) 2013 OpenSim Ltd.
// Copyright (C) 2021 Emre Atik
// Copyright (C) 2022 Ipek Gokce
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//

#ifndef __TRAFFICPOLICY_H__
#define __TRAFFICPOLICY_H__

#include <map>

#include "AFDXDefs.h"
#include "NetworkStatistics.h"

namespace afdx {

class TrafficPolicy : public cSimpleModule
{
private:
    typedef int VirtualLinkId_t;
    typedef double TokenCredit_t;
    typedef std::map<VirtualLinkId_t, TokenCredit_t> TokenBucketMap_t;
    typedef std::map<VirtualLinkId_t, double> LastTimeRecordMap_t;
    TokenBucketMap_t tokenBucket;
    LastTimeRecordMap_t lastTime;
    double minJitter;
    int bandwidthMbps;

protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
};

}
;
// namespace afdx

#endif
