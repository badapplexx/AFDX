//
// Copyright (C) 2013 OpenSim Ltd.
// Copyright (C) 2021 Emre Atik
// Copyright (C) 2022 Ipek Gokce
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//

#ifndef __VLROUTER_H__
#define __VLROUTER_H__

#include <map>
#include "AFDXDefs.h"
#include "AFDXMessage_m.h"

namespace afdx {

class VLRouter: public cSimpleModule {
private:
    typedef std::multimap<int, int> VirtualLinkIdToPortMap_t;
    VirtualLinkIdToPortMap_t vlToOutPortMappings;
    void getVirtualLinkToPortMappings(VirtualLinkIdToPortMap_t &vlToPortMapping,
            const char *fileName);
    void routePacket(VirtualLinkIdToPortMap_t &VLToPortMapping,
            AFDXMessage *afdxMessage);

protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    std::string configTableName;
};

}
;
// namespace afdx

#endif
