//
// Copyright (C) 2013 OpenSim Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//

#include "FrameFilter.h"

namespace afdx {

Define_Module(FrameFilter);

void FrameFilter::initialize() {
    // TODO - Generated method body
}

void FrameFilter::handleMessage(cMessage *msg) {
    send(msg, "out");
}

}
;
// namespace afdx

