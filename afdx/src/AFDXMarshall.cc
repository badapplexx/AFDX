//
// Copyright (C) 2022 Ipek Gokce
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//

#include "AFDXMarshall.h"

namespace afdx {

Define_Module(AFDXMarshall);
#define NUMBER_OF_PORTS 24

void AFDXMarshall::initialize()
{
    this->delay = par("delay");

    cModule *systemModule = this->getSimulation()->getSystemModule();
    if (systemModule->hasSubmoduleVector("SwitchA")) {
        this->numbeOfSwitches = systemModule->getSubmoduleVectorSize("SwitchA");
    }
    else {
        this->numbeOfSwitches = 0;
    }
    this->numberOfEndSystems = this->getParentModule()->getVectorSize();
}

void AFDXMarshall::handleMessage(cMessage *msg)
{
    if (!(msg->isSelfMessage())) //new message received
    {
        scheduleAt(simTime() + this->delay, msg); //delay the message
    }
    else	//delayed message received
    {
        AFDXMessage *afdxMsg = this->createAFDXMessage(msg);
        send(afdxMsg, "out");
    }
}

AFDXMessage* AFDXMarshall::createAFDXMessage(cMessage *msg)
{
    SubsystemMessage *temp = check_and_cast<SubsystemMessage*>(msg);
    AFDXMessage *afdxMsg = new AFDXMessage();
    afdxMsg->setPartitionId(temp->getPartitionId());
    int length = temp->getPacketLength() + par("frameHeaderLength").intValue();
    afdxMsg->setByteLength(length);
    afdxMsg->setKind(temp->getKind());
    afdxMsg->setPriority(temp->getPriority());
    afdxMsg->setTimestamp(temp->getCreationTime());
    delete temp;

    afdxMsg->setNetworkId(par("networkId").intValue());
    afdxMsg->setEquipmentId(par("equipmentId").intValue());
    afdxMsg->setInterfaceId(par("interfaceId").intValue());
    afdxMsg->setVirtualLinkId(par("virtualLinkId").intValue());
    afdxMsg->setKind(afdxMsg->getVirtualLinkId());
    afdxMsg->setSeqNum(par("seqNum").intValue());
    afdxMsg->setUdpSrcPort(par("udpSrcPort").intValue());
    afdxMsg->setUdpDestPort(par("udpDestPort").intValue());
    afdxMsg->setBagValue(par("BAG").doubleValue());
    afdxMsg->setRho(par("rho").doubleValue());
    afdxMsg->setSigma(par("sigma").doubleValue());

    afdxMsg->setAFDXMarshallingTime(simTime());

    afdx::NetworkStatistics::getInstance()->createRecorder(E2E_LATENCY_PER_VL, afdxMsg->getVirtualLinkId());
    afdx::NetworkStatistics::getInstance()->createRecorder(ES_SCHEDULING_LATENCY_PER_VL, afdxMsg->getVirtualLinkId());
    afdx::NetworkStatistics::getInstance()->createRecorder(ES_TOTAL_LATENCY_PER_VL, afdxMsg->getVirtualLinkId());
    afdx::NetworkStatistics::getInstance()->createRecorder(ES_BAG_LATENCY_PER_VL, afdxMsg->getVirtualLinkId());
    afdx::NetworkStatistics::getInstance()->createRecorder(DROPPED_FRAMES_IN_QUEUE_PER_VL, afdxMsg->getVirtualLinkId());
    afdx::NetworkStatistics::getInstance()->createRecorder(DROPPED_FRAMES_TRAFFIC_POLICY_PER_VL,
            afdxMsg->getVirtualLinkId());
    afdx::NetworkStatistics::getInstance()->createRecorder(TRAFFIC_SOURCE_PER_VL, afdxMsg->getVirtualLinkId());
    afdx::NetworkStatistics::getInstance()->record(TRAFFIC_SOURCE_PER_VL, afdxMsg->getVirtualLinkId(),
            afdxMsg->getCreationTime().dbl());

    for (uint32_t i = 0; i < this->numbeOfSwitches; i++) {
        afdx::NetworkStatistics::getInstance()->createRecorder(CREDIT_PER_VL_PER_SW, afdxMsg->getVirtualLinkId(), i);
        afdx::NetworkStatistics::getInstance()->createRecorder(SWITCH_QUEUEING_TIME_PER_VL_PER_SW,
                afdxMsg->getVirtualLinkId(), i);
    }

    for (uint32_t i = 0; i < this->numberOfEndSystems; i++) {
        afdx::NetworkStatistics::getInstance()->createRecorder(E2E_LATENCY_PER_VL_PER_RECEIVER_ES,
                afdxMsg->getVirtualLinkId(), i);
    }
    return afdxMsg;

}

}
