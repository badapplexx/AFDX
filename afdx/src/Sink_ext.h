//
// Copyright (C) 2013 OpenSim Ltd.
// Copyright (C) 2022 Ipek Gokce
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//

#ifndef __AFDX_SINK_EXT_H_
#define __AFDX_SINK_EXT_H_

#include "Sink.h"
#include "AFDXDefs.h"
#include "AFDXMessage_m.h"
#include "NetworkStatistics.h"

namespace afdx {

using namespace queueing;

class Sink_ext: public Sink {
private:
    uint32_t ESIndex = 0;
protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

} //namespace

#endif
