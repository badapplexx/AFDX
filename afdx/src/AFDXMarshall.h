//
// Copyright (C) 2022 Ipek Gokce
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//

#ifndef AFDXMARSHALL_H_
#define AFDXMARSHALL_H_

#include "AFDXDefs.h"
#include "AFDXMessage_m.h"
#include "SubsystemMessage_m.h"
#include "NetworkStatistics.h"

namespace afdx {

class AFDXMarshall : public cSimpleModule
{
private:
    //Parameters
    double delay = 0;
    uint32_t numbeOfSwitches = 0;
    uint32_t numberOfEndSystems = 0;
    AFDXMessage* createAFDXMessage(cMessage *msg);
protected:
    virtual void handleMessage(cMessage *msg);
    virtual void initialize();
};

}

#endif /* AFDXMARSHALL_H_ */
