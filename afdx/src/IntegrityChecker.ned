//
// Copyright (C) 2013 OpenSim Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//


package afdx;

//
// Checks the integrity and sequence number of a received frame
//
simple IntegrityChecker
{
    @display("i=block/filter");
    gates:
        input in;
        output out;
}
