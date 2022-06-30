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
    SWITCH_QUEUE_LENGTH_PER_VL_PER_SW,
};

class NetworkStatistics
{
public:
    typedef int VLID_t;
    typedef int Index_t;
    struct SwitchDefinition
    {
        int index; //id:-1 means this is not a switch
        bool isA;
        bool isInPort;
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
    static NetworkStatistics* getInstance();

    // index is used when additional indexes are needed such as switch index or es-index.
    void createRecorder(RecordType_t type, VLID_t key, int index = -1);
    void createRecorder(RecordType_t type, SwitchDefinition key, int index = -1);

    int record(RecordType_t type, VLID_t key, double value2Record, int swIndex = -1);
    void record(RecordType_t type, SwitchDefinition key, double value2Record, int index = -1);

    int getQueueLengthCount(SwitchDefinition s);
    void increaseQueueLengthCount(SwitchDefinition s);
    void decreaseQueueLengthCount(SwitchDefinition s);
    void createQueueLengthCounter(SwitchDefinition s);

    SwitchDefinition getSwitchDefinition(cModule *where);
    bool isInSwitchAPort(SwitchDefinition key, int idToCheck = -1);

private:
    static NetworkStatistics *instance_;

    typedef std::map<Index_t, cOutVector*> RecordPerSW_t;
    typedef std::map<VLID_t, cOutVector*> RecordPerVL_t;
    typedef std::map<KeyForRecordPerVLPerIndex_t, cOutVector*> RecordPerVLPerIndex_t;
    typedef std::map<KeyForRecordPerSWPerIndex_t, cOutVector*> RecordPerSWPerIndex_t;

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

    RecordPerSW_t swQueueLengthPSRecorder;
    RecordPerSW_t swQueueingTimePSRecorder;
    std::map<int, int> queueCounterPerSwitch;

    NetworkStatistics();
    std::string toHexString(int num);

};

}

#endif /* NETWORKSTATISTICS_H_ */
