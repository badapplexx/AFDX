//
// Copyright (C) 2013 OpenSim Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//

package afdx;

// A port in the switch. 
// During receive handles integrity checking traffic policing and timestamps 
// the message at the arrival of the last bit.
// on sending handles the sendout at physical layer (deals with preamble and IFG too) 
//
module SwitchPort
{
    @display("i=block/ifcard;bgb=315,242");
    double maxPacketAge @unit(s) = default(50ms);
    gates:
        inout ethPort;
        inout toFabric;
    submodules:
        frameFilter: FrameFilter {
            @display("p=159,79");
        }
        trafficPolicy: TrafficPolicy {
            @display("p=253,79");
            minJitter = 40us;
        }
        mac: MAC {
            @display("p=52,79");
        }
        txQueue: PassiveQueue {
            @display("p=253,169");
        }
    connections:
        ethPort <--> mac.eth;
        mac.out --> frameFilter.in;
        frameFilter.out --> trafficPolicy.in;
        trafficPolicy.out --> toFabric$o;
        txQueue.out++ --> mac.in++;
        toFabric$i --> txQueue.in++;
}
