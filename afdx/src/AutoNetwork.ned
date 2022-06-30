//
// Copyright (C) 2022 Ipek Gokce
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//
import afdx.EndSystem;
import afdx.Switch;
import afdx.Cable;
import afdx.ConnDef;

package afdx;

network AutoNetwork
{
    int numberOfEndSystems;
    int numberOfSwitches;
    int numberOfConnections = numberOfEndSystems+numberOfSwitches-1;

    double ethSpeed @unit(Mbps) = default(100Mbps);
    //double CableLength @unit(m) = default(10m);
    @display("bgb=692,639");
    submodules:
        connDef[numberOfConnections]: ConnDef {
            @display("p=0,0");
        }
        ESGroup[numberOfEndSystems]: EndSystem {
            @display("p=50,50,ri,250,250");
        }
        SwitchA[numberOfSwitches]: Switch {
            @display("p=249.484,294.494,m,2,100,100");
            noOfPorts = 24;
        }
        SwitchB[numberOfSwitches]: Switch {
            @display("p=249.484,294.494,m,2,100,100");
            noOfPorts = 24;
        }
    connections allowunconnected:
        for i=0..numberOfConnections-1 {
            ESGroup[connDef[i].entryIndex].ethPortA <--> Cable {  datarate = parent.ethSpeed; length = parent.connDef[i].cableLength; } <--> SwitchA[connDef[i].exitIndex].ethPort[i] if (true == connDef[i].isEntryAnEndsystem) && (false == connDef[i].isExitAnEndsystem);
            SwitchA[connDef[i].entryIndex].ethPort[i] <--> Cable {  datarate = parent.ethSpeed; length = parent.connDef[i].cableLength; } <--> ESGroup[connDef[i].exitIndex].ethPortA if (false == connDef[i].isEntryAnEndsystem) && (true == connDef[i].isExitAnEndsystem);
            SwitchA[connDef[i].entryIndex].ethPort[i] <--> Cable {  datarate = parent.ethSpeed; length = parent.connDef[i].cableLength; } <--> SwitchA[connDef[i].exitIndex].ethPort[i] if (false == connDef[i].isEntryAnEndsystem) && (false == connDef[i].isExitAnEndsystem);


            ESGroup[connDef[i].entryIndex].ethPortB <--> Cable {  datarate = parent.ethSpeed; length = parent.connDef[i].cableLength; } <--> SwitchB[connDef[i].exitIndex].ethPort[i] if (true == connDef[i].isEntryAnEndsystem) && (false == connDef[i].isExitAnEndsystem);
            SwitchB[connDef[i].entryIndex].ethPort[i] <--> Cable {  datarate = parent.ethSpeed; length = parent.connDef[i].cableLength; } <--> ESGroup[connDef[i].exitIndex].ethPortB if (false == connDef[i].isEntryAnEndsystem) && (true == connDef[i].isExitAnEndsystem);
            SwitchB[connDef[i].entryIndex].ethPort[i] <--> Cable {  datarate = parent.ethSpeed; length = parent.connDef[i].cableLength; } <--> SwitchB[connDef[i].exitIndex].ethPort[i] if (false == connDef[i].isEntryAnEndsystem) && (false == connDef[i].isExitAnEndsystem);
        }
}
