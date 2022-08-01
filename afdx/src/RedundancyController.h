//
// Copyright (C) 2013 OpenSim Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//

#ifndef __REDUNDANCYCONTROLLER_H__
#define __REDUNDANCYCONTROLLER_H__

#include "AFDXDefs.h"
#include "NetworkStatistics.h"
#include <map>

namespace afdx {

/**
 * Copy the incoming frame to link A or link B or both.
 * Also add increasing sequence number to the frames, and
 * set the interface id too in the frame
 */
class RedundancyController : public cSimpleModule
{
private:
    bool isNetworkA_Enabled;
    bool isNetworkB_Enabled;
    typedef std::map<int, int> VlIdToSeqNumMap_t;
    VlIdToSeqNumMap_t seqNum;

protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
};

}
;
// namespace afdx

#endif
