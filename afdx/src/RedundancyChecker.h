//
// Copyright (C) 2013 OpenSim Ltd.
// Copyright (C) 2021 Emre Atik
// Copyright (C) 2022 Ipek Gokce
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//

#ifndef __REDUNDANCYCHECKER_H__
#define __REDUNDANCYCHECKER_H__

#include "AFDXDefs.h"
#include <map>

namespace afdx {

class RedundancyChecker: public cSimpleModule {
private:
    bool isEnabled;
    simtime_t skewMax;

    typedef std::map<int, simtime_t> LastFrameTimeToVLID_t;
    typedef std::map<int, int> SeqNoToVLID_t;

    LastFrameTimeToVLID_t lastFrameReceived;
    SeqNoToVLID_t previousSeqNo;
    SeqNoToVLID_t nexSeqNo;

protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
};

}
;
// namespace afdx

#endif
