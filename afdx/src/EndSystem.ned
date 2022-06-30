//
// Copyright (C) 2013 OpenSim Ltd.
// Copyright (C) 2022 Ipek Gokce
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//

package afdx;

import ned.DatarateChannel;
import afdx.Cable;
//
// This module represents an EndSystem device in an AFDX network. It has two 
// separate ethernet interfaces which should be attached to different networks
//

module EndSystem
{
    @display("i=device/device;bgb=243.47353,117.4275,white");
    int messageCount = default(0);

    gates:
        inout ethPortA @labels(Cable);//@labels(eth100);
        inout ethPortB @labels(Cable);// @labels(eth100);
    submodules:
        messageSource[messageCount]: Source_ext {
            @display("p=29.895533,33.396812,c,10,10");
        }
        latencyTechTx: org.omnetpp.queueing.Delay {
            @display("p=98.30513,33.396812");
        }
        messageSink: Sink_ext {
            @display("p=29.895533,79.99075");
        }
        latencyTechRx: org.omnetpp.queueing.Delay {
            @display("p=98.30513,79.99075");
        }
        macB: MAC {
            @display("p=218.0246,58.71644");
        }
        macA: MAC {
            @display("p=218.0246,33.682297");
        }
        txQueueA: PassiveQueue {
            @display("p=182.74922,16.385983");
        }
        txQueueB: PassiveQueue {
            @display("p=184.11472,43.46837");
        }
        integrityCheckerA: IntegrityChecker {
            @display("p=186.84572,66.68185");
        }
        integrityCheckerB: IntegrityChecker {
            @display("p=188.89397,93.30907");
        }
        regulatorLogic: RegulatorLogic {
            @display("p=125.50738,41.476685");
        }
        redundancyChecker: RedundancyChecker {
            @display("p=156.74956,79.99075");
        }
        redundancyController: RedundancyController {
            @display("p=156.80475,33.454716");
        }
        afdxMarshall[messageCount]: AFDXMarshall {
            @display("p=67.33228,41.476685,c,10,10");
        }
    connections:
        ethPortA <--> macA.eth;
        ethPortB <--> macB.eth;
        txQueueA.out++ --> macA.in++;
        txQueueB.out++ --> macB.in++;
        macA.out --> integrityCheckerA.in;
        macB.out --> integrityCheckerB.in;

        for i=0..messageCount-1 {
            messageSource[i].out --> Cable {  datarate = parent.messageSource[i].baudrate; length = parent.messageSource[i].cableLength; } --> afdxMarshall[i].in;
            afdxMarshall[i].out --> latencyTechTx.in++;
        }
        latencyTechTx.out --> regulatorLogic.in++;
        redundancyChecker.out --> latencyTechRx.in++;
        latencyTechRx.out --> messageSink.in++;
        regulatorLogic.out --> redundancyController.in++;
        redundancyController.outA --> txQueueA.in++;
        redundancyController.outB --> txQueueB.in++;
        integrityCheckerA.out --> redundancyChecker.inA;
        integrityCheckerB.out --> redundancyChecker.inB;
}
