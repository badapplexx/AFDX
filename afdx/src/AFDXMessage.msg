//
// Copyright (C) 2013 OpenSim Ltd.
// Copyright (C) 2021 Emre Atik
// Copyright (C) 2022 Ipek Gokce
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//


cplusplus {{
#include "Job.h"
}}

import Job;

namespace afdx;

//
// A Message describing an AFDX msg. (length)  
//
message AFDXMessage extends queueing::Job
{
    int networkId;       // (1) used as [n]
    int equipmentId;     // (1) used as [e]
    int interfaceId;     // (3bit) used as [i] 
    int virtualLinkId;   // (2) used as [v]
    int seqNum;          // (1) used as [s]
    int partitionId;     // (5bit) used as [p] 
    double bagValue;
	double rho;			//used in token bucket algorithm
	double sigma;			//used in token bucket algorithm
	
	simtime_t AFDXMarshallingTime;
	simtime_t regLogExitTime;
	simtime_t regLogEntryTime;
	
    // preamble (7)
    // SFD (1)
    // *** start ethernet frame ***
    // abstract string ethDestAddr; // (6) derived as: 00000011 00000000 00000000 00000000 vvvvvvvv vvvvvvvv     
    // abstract string ethSrcAddr; // (6) derived as: 00000010 00000000 00000000 nnnnnnnn eeeeeeee iii00000
    // type (2) - always IPv4
    // payload (46-1500)
    // FCS (4)
    // *** end ethernet frame ***
    // IFG (12)

    // *** start ip layer ***  
    // length, frag control, checksum not modeled - (12)
    // abstract string ipSrcAddress; // (4) derived as : 00001010 nnnnnnnn eeeeeeee xxxppppp
    // abstract string ipDestAddress; // (4) derived as: 11100000 11100000 vvvvvvvv vvvvvvvv 
    // *** end ip layer ***
      
    // *** start udp header ***
    int udpSrcPort;    // (2)
    int udpDestPort;   // (2)
    // payload length - not modeled (2)
    // CRC - not modeled (2)
    // *** end udp header ***
    
}
