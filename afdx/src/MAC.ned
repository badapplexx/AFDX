//
// Copyright (C) 2013 OpenSim Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//

package afdx;

//
// Handles the TX/RX over the ethernet cable. 
// Encasulation/decasulation is done here i.e. the packetLength is modified to
// add/substract the ethernet frame size. Also preamble and IFG is handled here  
// TX: Invalid or expired packets are dropped.
// RX: timestamp the message with last bit received time.
//
simple MAC
{
    @display("i=block/rxtx");
    string fetchingAlgorithm @enum("priority","random","roundRobin","longestQueue") = default("roundRobin");
             // how the next job will be choosen from the attached queues
    double maxFrameAge @unit("s") = default(1s);
    gates:
        inout eth;
        input in[];
        output out;
}
