//
// Copyright (C) 2022 Ipek Gokce
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//

#ifndef NETWORKSTATISTICS_H_
#define NETWORKSTATISTICS_H_

#include <omnetpp.h>
#include <map>
#include <vector>

using namespace omnetpp;

namespace afdx {

enum RecordType_t
{
    E2E_LATENCY_PER_VL = 0,
    ES_BAG_LATENCY_PER_VL,
    ES_SCHEDULING_LATENCY_PER_VL,
    ES_TOTAL_LATENCY_PER_VL,
    DROPPED_FRAMES_IN_QUEUE_PER_VL,
    DROPPED_FRAMES_TRAFFIC_POLICY_PER_VL,
    TRAFFIC_SOURCE_PER_VL,
    SWITCH_QUEUEING_TIME_PER_SWITCH,
    SWITCH_QUEUE_LENGTH_PER_SWITCH,

    CREDIT_PER_VL_PER_SW,
    E2E_LATENCY_PER_VL_PER_RECEIVER_ES,
    SWITCH_QUEUEING_TIME_PER_VL_PER_SW,
    SWITCH_QUEUEING_TIME_PER_SW_PER_PORT,
    SWITCH_QUEUE_LENGTH_PER_SW_PER_PORT,
    SWITCH_QUEUEING_TIME_PER_SW_PER_VL_PER_PORT,
};

class NetworkStatistics
{
public:
    typedef int VLID_t;
    typedef int SwitchID_t;
    typedef int Index_t;
    struct SwitchDefinition
    {
        SwitchID_t index; //id:-1 means this is not a switch
        bool isA;
        bool isInPort; //is this record is taken in SwitchPort Block -> added because PassiveQueue block is also included in the ES.
        bool operator <(const SwitchDefinition &rhs) const
        {
            return std::tie(this->isA, this->index, this->isInPort) < std::tie(rhs.isA, rhs.index, rhs.isInPort);
        }
    };
    struct KeyForRecordPerVLPerIndex_t
    {
        VLID_t vlid;
        Index_t index;
        bool operator <(const KeyForRecordPerVLPerIndex_t &rhs) const
        {
            return std::tie(this->vlid, this->index) < std::tie(rhs.vlid, rhs.index);
        }
    };
    struct KeyForRecordPerSWPerIndex_t
    {
        SwitchDefinition sw;
        Index_t index;
        bool operator <(const KeyForRecordPerSWPerIndex_t &rhs) const
        {
            return std::tie(this->sw, this->index) < std::tie(rhs.sw, rhs.index);
        }
    };
    struct KeyForRecordPerSWPerVLPerIndex_t
    {
        VLID_t vlid;
        SwitchID_t swid;
        Index_t portIndex;
        bool operator <(const KeyForRecordPerSWPerVLPerIndex_t &rhs) const
        {
            return std::tie(this->vlid, this->swid, this->portIndex) < std::tie(rhs.vlid, rhs.swid, rhs.portIndex);
        }
    };
    static NetworkStatistics* getInstance();

    // index is used when additional indexes are needed such as switch index, es-index, port index..
    // records are mostly per_vl or per_switch. Some of them are needed to be per_vl_per_something_else. For those, an additional index is added.

    // to create records per_vl, createRecorder function shall be called in where all vl-id's and additional index are known (i.e. where they are created)
    // to create records per_switch, createRecorder function shall be called in where all sw-id's and additional index are known (i.e. some block in the switch)

    //per vl (+ per index) records
    void createRecorder(RecordType_t type, VLID_t key, int index = -1);
    void record(RecordType_t type, VLID_t key, double value2Record, int swIndex = -1);

    //per switch (+ per index) records
    void createRecorder(RecordType_t type, SwitchDefinition sw, int index = -1);
    void record(RecordType_t type, SwitchDefinition sw, double value2Record, int index = -1);

    // per vl per switch (+ per index) records
    // some records are needed to be taken with respect to vl-id, switch id and an additional index(port index). To create this type of records, creator shall be called
    // in where all vl-id's and also sw-id's and port index are known. Well, in trafficSource vl-id's can be known but sw-id--port index match cannot be done.
    // in switch (constructor of a certain block inside the switch), sw-id an related port is known but vl-ids are not known yet.
    // Thus creation and record taking operations are combined into one function. If record doesn't exist, it will be created and this shall be called in one of the switch blocks
    void takeRecordAndCreateIfNotExist(RecordType_t type, SwitchDefinition sw, VLID_t vlid, double value2Record,
            int portIndex);

    int getQueueLengthCountInBit(SwitchDefinition s);
    void increaseQueueLengthCountInBit(SwitchDefinition s, uint64_t messageLenInBit);
    void decreaseQueueLengthCountInBit(SwitchDefinition s, uint64_t messageLenInBit);
    void createQueueLengthCounterInBit(SwitchDefinition s);

    SwitchDefinition getSwitchDefinition(cModule *where);
    bool isInSwitchAPort(SwitchDefinition key, int idToCheck = -1);

private:
    static NetworkStatistics *instance_;

    typedef std::map<Index_t, cOutVector*> RecordPerSW_t;
    typedef std::map<VLID_t, cOutVector*> RecordPerVL_t;
    typedef std::map<KeyForRecordPerVLPerIndex_t, cOutVector*> RecordPerVLPerIndex_t;
    typedef std::map<KeyForRecordPerSWPerIndex_t, cOutVector*> RecordPerSWPerIndex_t;
    typedef std::map<KeyForRecordPerSWPerVLPerIndex_t, cOutVector*> RecordPerSWPerVLPerIndex_t;

    RecordPerVL_t ESTotalLatencyRecorder;
    RecordPerVL_t ESSchedulingLatencyRecorder;
    RecordPerVL_t ESBaggingLatencyRecorder;
    RecordPerVL_t droppedFramesRecorderInQueue;
    RecordPerVL_t droppedFramesRecorderInTrafficPolicy;
    RecordPerVL_t swQueueLengthPVRecorder;
    RecordPerVL_t sourceRecorder;
    RecordPerVL_t e2eLatency;

    RecordPerVLPerIndex_t creditsAtSw;
    RecordPerVLPerIndex_t e2eLatencyAtRxES;
    RecordPerVLPerIndex_t swQueueingTimePV;
    RecordPerSWPerIndex_t swQueueingLenPerSwPerPort;
    RecordPerSWPerIndex_t swQueueingTimePerSwPerPort;
    RecordPerSWPerVLPerIndex_t swQueueingTimePerSWPerVLPerPort;

    RecordPerSW_t swQueueLengthPSRecorder;
    RecordPerSW_t swQueueingTimePSRecorder;
    std::map<int, int> queueCounterPerSwitch;
    std::map<int, int> queueCounterInBitPerSwitch;
    NetworkStatistics();
    std::string toHexString(int num);

};

}

#endif /* NETWORKSTATISTICS_H_ */
