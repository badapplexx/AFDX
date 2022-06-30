//
// Copyright (C) 2013 OpenSim Ltd.
// Copyright (C) 2022 Ipek Gokce
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//


package afdx;

import org.omnetpp.queueing.Source;

simple Source_ext extends Source
{
    @class(Source_ext);
    volatile int packetLength = default(128);       			// the legth of AFDX Ethernet frame
    volatile int partitionId;     								// (5bit) used as [p] 
    volatile double baudrate @unit(bps) = default(0bps);
	volatile double cableLength @unit(m) = default(0m);
	double deltaInterArrivalTimeMaxLimit @unit(s) = default(0s);
}
