//
// Copyright (C) 2022 Ipek Gokce
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//

#ifndef __AFDX_SKEWMAXTESTER_H_
#define __AFDX_SKEWMAXTESTER_H_

#include <omnetpp.h>
#include "AFDXMessage_m.h"

using namespace omnetpp;

namespace afdx {
class SkewMaxTester: public cSimpleModule {
protected:
    bool isSkewMaxTestEnabled;
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
};

} //namespace

#endif
