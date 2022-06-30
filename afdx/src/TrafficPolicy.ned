//
// Copyright (C) 2013 OpenSim Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//

package afdx;

//
// FIlter frames for bandwith violation
//
// Valid frames are filtered for bandwidth. Any frame that exceeds the defined bandwidth limit
// for the VL is discarded. The standard specifies a token-bucket algorithm for policing bandwidth
// and allows the option of selecting either frame-based or byte-based policing.
//
simple TrafficPolicy
{
    @display("i=block/bucket");
    int bandwidth = default(100); // for max token bucket calculation
    double minJitter @unit(ms) = default(40us);   // maximum allowed jitter 
    gates:
        input in;
        output out;
}
