//
// Copyright (C) 2013 OpenSim Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//


package afdx;

// 
// A channel representing a twisted pair 100MBps ethernet line
//
//
// Represents an AFDX switch
//
module Switch
{
    parameters:
        @display("i=block/switch");
        int noOfPorts = default(24);
    gates:
        inout ethPort[this.noOfPorts] @labels(eth100);
    submodules:
        switchPort[this.noOfPorts]: SwitchPort {
            @display("p=398,144,ri,180");
        }
        switchFabric: SwitchFabric {
            @display("p=228,144");
            gates:
                port[parent.noOfPorts];
        }
    connections:
        for i=0..noOfPorts-1 {
            ethPort[i] <--> switchPort[i].ethPort;
        }
        for i=0..noOfPorts-1 {
            switchPort[i].toFabric <--> switchFabric.port[i];
        }
}
