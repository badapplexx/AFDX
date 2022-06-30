//
// Copyright (C) 2013 OpenSim Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//


package afdx;

//
// Handles the routing frames on different virtual links.
// If an output port cannot handle the output packet (busy, down)
// the packet should be dropped. If a packed is too old 
// (calculated transmission time of last bit - reception time of last bit) 
// it should be dropped too. maxPacketAge is specified for each port.
//
module SwitchFabric
{
    @display("i=block/fork;bgb=504.44998,185.25");
    gates:
        inout port[];
    submodules:
        priorityClassifier: org.omnetpp.queueing.Classifier {
            @display("p=60,82");
            dispatchField = "priority";
            gates:
                out[2];
        }
        lowQueue: PassiveQueue {
            @display("p=149,133");
        }
        highQueue: PassiveQueue {
            @display("p=149,37");
        }
        scheduler: org.omnetpp.queueing.Server {
            @display("p=245,82");
            gates:
                in[2];
        }
        delay: org.omnetpp.queueing.Delay {
            @display("p=312.55,81.7");
        }
        router: VLRouter {
            @display("p=388.55,81.7");
            gates:
                out[sizeof(parent.port)];
        }
    connections allowunconnected:
        for i=0..sizeof(port)-1 {
            port$i[i] --> priorityClassifier.in++;
        }

        priorityClassifier.out[0] --> highQueue.in++;
        priorityClassifier.out[1] --> lowQueue.in++;
        
        highQueue.out++ --> scheduler.in[0];
        lowQueue.out++ --> scheduler.in[1];
        scheduler.out --> delay.in++;
        delay.out --> router.in++;

        for i=0..sizeof(port)-1 {
            router.out[i] --> port$o[i];
        }
}
