//
// Copyright (C) 2013 OpenSim Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//

package afdx;

//
// Filter received packets
// 
// The frame size is verified to be within the defined limits of VL length (between SMIN and LMAX/SMAX).
// The frame is verified to have an integer number of bytes to check alignment.
// The FCS for the frame is calculated and verified against the value contained in the frame.
// The incoming switch port assignment for the VL is verified.
// The destination MAC addressed for the VL is verified as reachable.

simple FrameFilter
{
    @display("i=block/filter");
    gates:
        input in;
        output out;
}
