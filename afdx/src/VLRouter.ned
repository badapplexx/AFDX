//
// Copyright (C) 2013 OpenSim Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//

package afdx;

//
// Routes and possibly duplicates the incoming messages to the output, based on 
// the virtual link routing table for this router
//
simple VLRouter
{
    @display("i=block/fork");
    string configTableName = default("Switch.txt");
    gates:
        input in[];
        output out[];
}
