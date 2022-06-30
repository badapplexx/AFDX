//
// Copyright (C) 2013 OpenSim Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//

package afdx;

//
// TODO auto-generated module
//
simple RedundancyController
{
    @display("i=block/fork");
    bool copyToLinkA = default(true);
    bool copyToLinkB = default(true);
    gates:
        input in[];
        output outA;
        output outB;
}
