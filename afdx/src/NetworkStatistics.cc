//
// Copyright (C) 2022 Ipek Gokce
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//

#include "NetworkStatistics.h"
namespace afdx {

NetworkStatistics *NetworkStatistics::instance_ = nullptr;
NetworkStatistics::NetworkStatistics()
{
}
NetworkStatistics* NetworkStatistics::getInstance()
{
    if (instance_ == nullptr) {
        instance_ = new NetworkStatistics();
    }
    return instance_;
}

std::string NetworkStatistics::toHexString(int num)
{
    std::stringstream ss;
    ss << std::hex << num;
    return ss.str();
}

void NetworkStatistics::createRecorder(RecordType_t type, VLID_t vlid, int index)
{
    RecordPerVL_t *recorPerVl = NULL;
    RecordPerVLPerIndex_t *recordPerVLPerIndex = NULL;

    std::string name = "";

    switch (type) {
        case ES_TOTAL_LATENCY_PER_VL: {
            recorPerVl = &ESTotalLatencyRecorder;
            name = "ESTotalLatency_VL" + toHexString(vlid);
            break;
        }
        case ES_SCHEDULING_LATENCY_PER_VL: {
            recorPerVl = &ESSchedulingLatencyRecorder;
            name = "ESSchedulingLatency_VL" + toHexString(vlid);
            break;
        }
        case ES_BAG_LATENCY_PER_VL: {
            recorPerVl = &ESBaggingLatencyRecorder;
            name = "ESBagLatency_VL" + toHexString(vlid);
            break;
        }
        case DROPPED_FRAMES_IN_QUEUE_PER_VL: {
            recorPerVl = &droppedFramesRecorderInQueue;
            name = "DroppedFrameQueue_VL" + toHexString(vlid);
            break;
        }
        case DROPPED_FRAMES_TRAFFIC_POLICY_PER_VL: {
            recorPerVl = &droppedFramesRecorderInTrafficPolicy;
            name = "DroppedFrameTraffPol_VL" + toHexString(vlid);
            break;
        }
        case TRAFFIC_SOURCE_PER_VL: {
            recorPerVl = &sourceRecorder;
            name = "TrafficSource_VL" + toHexString(vlid);
            break;
        }
        case E2E_LATENCY_PER_VL: {
            recorPerVl = &e2eLatency;
            name = "E2ELatency_VL" + toHexString(vlid);
            break;
        }
        case CREDIT_PER_VL_PER_SW: {
            //index = switch index
            recordPerVLPerIndex = &creditsAtSw;
            name = "TokenBucketCredit#SW" + std::to_string(index) + "_VL" + toHexString(vlid);
            break;
        }
        case SWITCH_QUEUEING_TIME_PER_VL_PER_SW: {
            //index = switch index
            recordPerVLPerIndex = &swQueueingTimePV;
            name = "SWQueueingTime#SW" + std::to_string(index) + "_VL" + toHexString(vlid);
            break;
        }
        case E2E_LATENCY_PER_VL_PER_RECEIVER_ES: {
            recordPerVLPerIndex = &e2eLatencyAtRxES;
            name = "LatencyAt#ES" + std::to_string(index) + "_VL" + toHexString(vlid);
            break;
        }
        default: {
            std::cout << "NetworkStatistics::create::default - 1";
            break;
        }
    }

    if (index == -1) {
        // vlid is the key for the map
        if (recorPerVl->end() == recorPerVl->find(vlid)) {
            cOutVector *temp = new cOutVector;
            temp->setName(name.c_str());
            (*recorPerVl)[vlid] = temp;
        }
    }
    else {
        KeyForRecordPerVLPerIndex_t key;
        key.index = index;
        key.vlid = vlid;

        if (recordPerVLPerIndex->end() == recordPerVLPerIndex->find(key)) {
            cOutVector *temp = new cOutVector;
            temp->setName(name.c_str());
            (*recordPerVLPerIndex)[key] = temp;
        }
    }
}

void NetworkStatistics::createRecorder(RecordType_t type, SwitchDefinition sw, int index)
{
    RecordPerSW_t *recordPerSW = NULL;
    RecordPerSWPerIndex_t *recordPerSWPerIndex = NULL;
    std::string name = "";
    switch (type) {
        case SWITCH_QUEUE_LENGTH_PER_SWITCH: {
            recordPerSW = &swQueueLengthPSRecorder;
            name = "SWQueueLength_SW" + std::to_string(sw.index);
            break;
        }
        case SWITCH_QUEUE_LENGTH_PER_SW_PER_PORT: {
            //index = ES index
            recordPerSWPerIndex = &swQueueingLenPerSwPerPort;
            name = "SWQueueLength#Port" + std::to_string(index) + "_SW" + std::to_string(sw.index);
            break;
        }
        case SWITCH_QUEUEING_TIME_PER_SW_PER_PORT: {
            //index = ES index
            recordPerSWPerIndex = &swQueueingTimePerSwPerPort;
            name = "SWQueueingTime#Port" + std::to_string(index) + "_SW" + std::to_string(sw.index);
            break;
        }
        case SWITCH_QUEUEING_TIME_PER_SWITCH: {
            recordPerSW = &swQueueingTimePSRecorder;
            name = "SWQueueingTime_SW" + std::to_string(sw.index);
            break;
        }
        default: {
            std::cout << "NetworkStatistics::create::default - 2";
            break;
        }
    }

    if (index == -1) {
        if (recordPerSW->end() == recordPerSW->find(sw.index)) {
            cOutVector *temp = new cOutVector;
            temp->setName(name.c_str());
            if (sw.isA)
                (*recordPerSW)[sw.index] = temp;
        }
    }
    else {
        KeyForRecordPerSWPerIndex_t key;
        key.index = index;
        key.sw = sw;
        if (recordPerSWPerIndex->end() == recordPerSWPerIndex->find(key)) {
            cOutVector *temp = new cOutVector;
            temp->setName(name.c_str());
            if (sw.isA)
                (*recordPerSWPerIndex)[key] = temp;
        }
    }

}

void NetworkStatistics::createQueueLengthCounterInBit(SwitchDefinition s)
{
    if ((-1 != s.index) && s.isA) {
        this->queueCounterPerSwitch[s.index] = 0;
        this->queueCounterInBitPerSwitch[s.index] = 0;
    }

}
int NetworkStatistics::getQueueLengthCountInBit(SwitchDefinition s)
{
    int ret = -1;
    if ((-1 != s.index) && s.isA) {
//		ret = this->queueCounterPerSwitch[s.index];
        ret = this->queueCounterInBitPerSwitch[s.index];
    }
    return ret;
}
void NetworkStatistics::increaseQueueLengthCountInBit(SwitchDefinition s, uint64_t messageLenInBit)
{
    if ((-1 != s.index) && s.isA) {
        this->queueCounterPerSwitch[s.index]++;
        this->queueCounterInBitPerSwitch[s.index] += messageLenInBit;
    }
}
void NetworkStatistics::decreaseQueueLengthCountInBit(SwitchDefinition s, uint64_t messageLenInBit)
{
    if ((-1 != s.index) && s.isA) {
        this->queueCounterPerSwitch[s.index]--;
        this->queueCounterInBitPerSwitch[s.index] -= messageLenInBit;
    }
}

void NetworkStatistics::record(RecordType_t type, VLID_t vlid, double value2Record, int swIndex)
{
    RecordPerVL_t *recorPerVl = NULL;
    RecordPerVLPerIndex_t *recordPerVLPerIndex = NULL;

    switch (type) {
        case ES_TOTAL_LATENCY_PER_VL: {
            recorPerVl = &ESTotalLatencyRecorder;
            break;
        }
        case ES_SCHEDULING_LATENCY_PER_VL: {
            recorPerVl = &ESSchedulingLatencyRecorder;
            break;
        }
        case ES_BAG_LATENCY_PER_VL: {
            recorPerVl = &ESBaggingLatencyRecorder;
            break;
        }
        case DROPPED_FRAMES_IN_QUEUE_PER_VL: {
            recorPerVl = &droppedFramesRecorderInQueue;
            break;
        }
        case DROPPED_FRAMES_TRAFFIC_POLICY_PER_VL: {
            recorPerVl = &droppedFramesRecorderInTrafficPolicy;
            break;
        }
        case TRAFFIC_SOURCE_PER_VL: {
            recorPerVl = &sourceRecorder;
            break;
        }
        case E2E_LATENCY_PER_VL: {
            recorPerVl = &e2eLatency;
            break;
        }
        case CREDIT_PER_VL_PER_SW: {
            recordPerVLPerIndex = &creditsAtSw;
            break;
        }
        case SWITCH_QUEUEING_TIME_PER_VL_PER_SW: {
            recordPerVLPerIndex = &swQueueingTimePV;
            break;
        }
        case E2E_LATENCY_PER_VL_PER_RECEIVER_ES: {
            recordPerVLPerIndex = &e2eLatencyAtRxES;
            break;
        }

        default: {
            std::cout << "NetworkStatistics::record::default - 3";
            break;
        }
    }
    if (swIndex == -1) {
        if (recorPerVl->end() != recorPerVl->find(vlid)) // vlid is the key for the map
                {
            (*recorPerVl)[vlid]->record(value2Record);
        }
        else {
            std::cout << "Not found - 3.1" << std::endl;
        }
    }
    else {
        KeyForRecordPerVLPerIndex_t key;
        key.index = swIndex;
        key.vlid = vlid;

        // vlid is the key for the map
        if (recordPerVLPerIndex->end() != recordPerVLPerIndex->find(key)) {
            (*recordPerVLPerIndex)[key]->record(value2Record);
        }
        else {
            std::cout << "Not found - 3.2" << std::endl;
        }

    }

}

void NetworkStatistics::record(RecordType_t type, SwitchDefinition sw, double value2Record, int index)
{
    RecordPerSW_t *recordPerSW = NULL;
    RecordPerSWPerIndex_t *recordPerSWPerIndex = NULL;
    switch (type) {
        case SWITCH_QUEUE_LENGTH_PER_SWITCH: {
            recordPerSW = &swQueueLengthPSRecorder;
            break;
        }
        case SWITCH_QUEUE_LENGTH_PER_SW_PER_PORT: {
            recordPerSWPerIndex = &swQueueingLenPerSwPerPort;
            break;
        }
        case SWITCH_QUEUEING_TIME_PER_SW_PER_PORT: {
            recordPerSWPerIndex = &swQueueingTimePerSwPerPort;
            break;
        }
        case SWITCH_QUEUEING_TIME_PER_SWITCH: {
            recordPerSW = &swQueueingTimePSRecorder;
            break;
        }
        default: {
            std::cout << "NetworkStatistics::record::default - 4";
            break;
        }
    }

    if (index == -1) {
        // if there is a record for this key id
        if (recordPerSW->end() != recordPerSW->find(sw.index)) {
            (*recordPerSW)[sw.index]->record(value2Record);
        }
    }
    else {
        KeyForRecordPerSWPerIndex_t key;
        key.index = index;
        key.sw = sw;
        // if there is a record for this key id
        if (recordPerSWPerIndex->end() != recordPerSWPerIndex->find(key)) {
            (*recordPerSWPerIndex)[key]->record(value2Record);
        }
    }
}

void NetworkStatistics::takeRecordAndCreateIfNotExist(RecordType_t type, SwitchDefinition sw, VLID_t vlid,
        double value2Record, int portIndex)
{
    if (type == SWITCH_QUEUEING_TIME_PER_SW_PER_VL_PER_PORT) {
        KeyForRecordPerSWPerVLPerIndex_t key;
        key.portIndex = portIndex;
        key.swid = sw.index;
        key.vlid = vlid;

        if (this->swQueueingTimePerSWPerVLPerPort.end() == this->swQueueingTimePerSWPerVLPerPort.find(key)) // If record doesn't exist, then create.
                {
            std::string name = "SWQueueingTime#Port" + std::to_string(portIndex) + "#SW" + std::to_string(sw.index)
                    + "_VL" + toHexString(vlid);
            cOutVector *temp = new cOutVector;
            temp->setName(name.c_str());
            if (sw.isA) //take records only in switch A. (no need to record redundant frames)
            {
//				std::cout << "Creating new record: " << name;
                this->swQueueingTimePerSWPerVLPerPort[key] = temp;
                this->swQueueingTimePerSWPerVLPerPort[key]->record(value2Record);
            }
        }
        else {
//			std::cout << "Record exist: SWQueueingTime#Port" << std::to_string(portIndex) + "#SW" + std::to_string(sw.index) + "_VL" + std::to_string (vlid);
            this->swQueueingTimePerSWPerVLPerPort[key]->record(value2Record);
        }
//		std::cout << " |val: " << value2Record << endl;
    }
    else {
        std::cout << "NetworkStatistics::record::unknown type";
    }

}

bool NetworkStatistics::isInSwitchAPort(SwitchDefinition key, int idToCheck) //idToCheck = -1 by default
{
    bool ret = false;
    if ((-1 != key.index) && (key.isA) && (key.isInPort)) {
        if (idToCheck == -1 || idToCheck == key.index) {
            ret = true;
        }
    }
    else {
//		std::cout << "NetStat| Not found - 2" << std::endl;
    }
    return ret;
}

NetworkStatistics::SwitchDefinition NetworkStatistics::getSwitchDefinition(cModule *where)
{
    NetworkStatistics::SwitchDefinition sw;

    std::string::size_type pos = where->getFullPath().find("Switch");
    if (pos == std::string::npos) {
        sw.index = -1;
    }
    else {
        std::string AorB = where->getFullPath().substr(pos + 6, 1);
        sw.isA = (std::string::npos != AorB.find("A"));
        sw.isInPort = (std::string::npos != where->getFullPath().find("switchPort"));
        cModule *m = where;
        while (nullptr != m) {
            std::string n(m->getName());
            if (std::string::npos != n.find("Switch")) {
                sw.index = m->getIndex();
                break;
            }
            else {
                m = m->getParentModule();
            }
        }
    }
    return sw;
}

}
