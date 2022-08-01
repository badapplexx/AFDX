//
// Copyright (C) 2022 Ipek Gokce
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//


package afdx;

simple AFDXMarshall
{
    @class(AFDXMarshall);
    volatile int networkId;       // (1) used as [n]
    volatile int equipmentId;     // (1) used as [e]
    volatile int interfaceId;     // (3bit) used as [i] 
    volatile int virtualLinkId;   // (2) used as [v]
    volatile int seqNum;          // (1) used as [s]
    volatile int udpSrcPort;    // (2)
    volatile int udpDestPort;   // (2)
    volatile int frameHeaderLength;
    volatile double BAG @unit(s);
    volatile double rho @unit(bps);
    volatile double sigma;
    int deltaPacketLengthMaxLimit = default(0);
    double delay @unit(s) = default(0.0s);
    @display("i=block/classifier2");
    gates:
        input in;
        output out;
}
