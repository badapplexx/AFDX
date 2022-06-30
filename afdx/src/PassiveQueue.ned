//
// Copyright (C) 2013 OpenSim Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//
 
package afdx;

//
// Passive queue. Messages have to be requested via direct method call.
// Its output must be connected to a Server.
//
// @author rhornig
// @todo minDelay not implemented
//
simple PassiveQueue
{
    parameters:
//        @group(Queueing);
        @signal[dropped](type="long");
        @signal[queueLength](type="long");
        @signal[queueingTime](type="simtime_t");
        @statistic[dropped](title="drop event";record=vector?,count;interpolationmode=none);
        @statistic[queueLength](title="queue length";record=vector,timeavg,max;interpolationmode=sample-hold);
        @statistic[queueingTime](title="queueing time at dequeue";record=vector?,mean,max;unit=s;interpolationmode=none);
        @display("i=block/passiveq;q=queue");

        int capacity = default(-1);  // negative capacity means unlimited queue
        bool fifo = default(true);   // whether the module works as a queue (fifo=true) or a stack (fifo=false)
        string sendingAlgorithm @enum("priority","random","roundRobin","minDelay") = default("priority");
                                     // how the queue tries to find a suitable server for an incoming job
    gates:
        input in[];
        output out[];
}
