//
// Copyright (C) 2013 OpenSim Ltd.
// Copyright (C) 2022 Ipek Gokce
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//

#ifndef __MESSAGESOURCE_H__
#define __MESSAGESOURCE_H__

#include "AFDXDefs.h"
#include "SubsystemMessage_m.h"
#include "Source.h"
#include "NetworkStatistics.h"

using namespace queueing;
namespace afdx {
class Source_ext : public Source
{
private:
    simtime_t startTime;
    simtime_t stopTime;
    int numJobs;
    int jobCounter;
    simtime_t interArrivaltime;
    simtime_t deltaInterArrivalTime;
    double baudrate;

protected:
    Job* createJob() override;
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};
}
;
// namespace afdx

#endif
