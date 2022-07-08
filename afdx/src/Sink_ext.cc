//
// Copyright (C) 2013 OpenSim Ltd.
// Copyright (C) 2022 Ipek Gokce
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//

#include "Sink_ext.h"

namespace afdx {

Define_Module(Sink_ext);

void Sink_ext::initialize() {
    Sink::initialize();
    this->ESIndex = this->getParentModule()->getIndex();
}

void Sink_ext::handleMessage(cMessage *msg) {
    afdx::AFDXMessage *afdxMsg = check_and_cast<afdx::AFDXMessage*>(msg);
    int vlid = afdxMsg->getVirtualLinkId();

    simtime_t e2elatency = simTime() - afdxMsg->getCreationTime();

    afdx::NetworkStatistics::getInstance()->record(afdx::E2E_LATENCY_PER_VL,
            vlid, e2elatency.dbl());
    afdx::NetworkStatistics::getInstance()->record(
            afdx::E2E_LATENCY_PER_VL_PER_RECEIVER_ES, vlid, e2elatency.dbl(),
            this->ESIndex);

    Sink::handleMessage(msg);
}

} //namespace
