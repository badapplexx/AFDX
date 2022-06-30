//
// Copyright (C) 2013 OpenSim Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//


package afdx;

//
// TODO auto-generated module
//
simple RedundancyChecker
{
    @display("i=block/join");
    bool enabled = default(true);  // whether redundacy checking is enabled/disabled.
    double skewMax @unit(s) = default(20ms);
    gates:
        input inA;
        input inB;
        output out;
}
