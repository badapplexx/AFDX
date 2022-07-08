//
// Copyright (C) 2013 OpenSim Ltd.
// Copyright (C) 2022 Ipek Gokce
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//

#ifndef __INTEGRITYCHECKER_H__
#define __INTEGRITYCHECKER_H__

#include "AFDXDefs.h"

namespace afdx {

/**
 * TODO - Generated class
 */
class IntegrityChecker: public cSimpleModule {
private:
    int expectedSeqNum;
    typedef std::map<int, int> NextSeqNumberToVLID_t;
    NextSeqNumberToVLID_t psn; //Previous Sequence Number (PSN) is the sequence number of the previous frame received (but not necessarily forwarded) on this VL.
    bool isSequenceNumberOk(int psn, int seqNo);
protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
};

}
;
// namespace afdx

#endif
