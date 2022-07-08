//
// Copyright (C) 2013 OpenSim Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//
//

#ifndef __MAC_H__
#define __MAC_H__

#include "IServer.h"
#include "SelectionStrategies.h"
#include "NetworkStatistics.h"
#include "AFDXMessage_m.h"
namespace afdx {

/**
 * A full duplex Ethernet MAC module
 */
class MAC: public cSimpleModule, public queueing::IServer {
private:
    queueing::SelectionStrategy *selectionStrategy;
    bool isReserved;
    simtime_t maxFrameAge;
    cMessage *endServiceMsg;

protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

public:
    MAC();
    virtual ~MAC();
    virtual bool isIdle();
    virtual void allocate();
};

}
;
// namespace afdx

#endif
