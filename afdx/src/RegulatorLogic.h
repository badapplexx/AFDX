//
// Copyright (C) 2013 OpenSim Ltd.
// Copyright (C) 2021 Emre Atik
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//

#ifndef __REGULATORLOGIC_H__
#define __REGULATORLOGIC_H__

#include <map>
#include <queue>
#include "AFDXDefs.h"
#include "AFDXMessage_m.h"
#include "NetworkStatistics.h"

namespace afdx {

class RegulatorLogic : public cSimpleModule
{
private:
    typedef int TVirtualLinkId;
    typedef std::map<TVirtualLinkId, bool> BagFlagsPerVL_t;
    typedef std::map<TVirtualLinkId, std::queue<cMessage*>> BagQueuePerVL_t;

    int maxVLIDQueueSize; // size limit of the queue(for each VL id)
    BagFlagsPerVL_t bagFlagsPerVL;
    BagQueuePerVL_t bagQueue;

protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
};

}
;
// namespace afdx

#endif
