//
// Generated file, do not edit! Created by opp_msgtool 6.0 from AFDXMessage.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include <memory>
#include <type_traits>
#include "AFDXMessage_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp

namespace afdx {

Register_Class(AFDXMessage)

AFDXMessage::AFDXMessage(const char *name, short kind) : ::queueing::Job(name, kind)
{
}

AFDXMessage::AFDXMessage(const AFDXMessage& other) : ::queueing::Job(other)
{
    copy(other);
}

AFDXMessage::~AFDXMessage()
{
}

AFDXMessage& AFDXMessage::operator=(const AFDXMessage& other)
{
    if (this == &other) return *this;
    ::queueing::Job::operator=(other);
    copy(other);
    return *this;
}

void AFDXMessage::copy(const AFDXMessage& other)
{
    this->networkId = other.networkId;
    this->equipmentId = other.equipmentId;
    this->interfaceId = other.interfaceId;
    this->virtualLinkId = other.virtualLinkId;
    this->seqNum = other.seqNum;
    this->partitionId = other.partitionId;
    this->bagValue = other.bagValue;
    this->rho = other.rho;
    this->sigma = other.sigma;
    this->AFDXMarshallingTime = other.AFDXMarshallingTime;
    this->regLogExitTime = other.regLogExitTime;
    this->regLogEntryTime = other.regLogEntryTime;
    this->udpSrcPort = other.udpSrcPort;
    this->udpDestPort = other.udpDestPort;
}

void AFDXMessage::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::queueing::Job::parsimPack(b);
    doParsimPacking(b,this->networkId);
    doParsimPacking(b,this->equipmentId);
    doParsimPacking(b,this->interfaceId);
    doParsimPacking(b,this->virtualLinkId);
    doParsimPacking(b,this->seqNum);
    doParsimPacking(b,this->partitionId);
    doParsimPacking(b,this->bagValue);
    doParsimPacking(b,this->rho);
    doParsimPacking(b,this->sigma);
    doParsimPacking(b,this->AFDXMarshallingTime);
    doParsimPacking(b,this->regLogExitTime);
    doParsimPacking(b,this->regLogEntryTime);
    doParsimPacking(b,this->udpSrcPort);
    doParsimPacking(b,this->udpDestPort);
}

void AFDXMessage::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::queueing::Job::parsimUnpack(b);
    doParsimUnpacking(b,this->networkId);
    doParsimUnpacking(b,this->equipmentId);
    doParsimUnpacking(b,this->interfaceId);
    doParsimUnpacking(b,this->virtualLinkId);
    doParsimUnpacking(b,this->seqNum);
    doParsimUnpacking(b,this->partitionId);
    doParsimUnpacking(b,this->bagValue);
    doParsimUnpacking(b,this->rho);
    doParsimUnpacking(b,this->sigma);
    doParsimUnpacking(b,this->AFDXMarshallingTime);
    doParsimUnpacking(b,this->regLogExitTime);
    doParsimUnpacking(b,this->regLogEntryTime);
    doParsimUnpacking(b,this->udpSrcPort);
    doParsimUnpacking(b,this->udpDestPort);
}

int AFDXMessage::getNetworkId() const
{
    return this->networkId;
}

void AFDXMessage::setNetworkId(int networkId)
{
    this->networkId = networkId;
}

int AFDXMessage::getEquipmentId() const
{
    return this->equipmentId;
}

void AFDXMessage::setEquipmentId(int equipmentId)
{
    this->equipmentId = equipmentId;
}

int AFDXMessage::getInterfaceId() const
{
    return this->interfaceId;
}

void AFDXMessage::setInterfaceId(int interfaceId)
{
    this->interfaceId = interfaceId;
}

int AFDXMessage::getVirtualLinkId() const
{
    return this->virtualLinkId;
}

void AFDXMessage::setVirtualLinkId(int virtualLinkId)
{
    this->virtualLinkId = virtualLinkId;
}

int AFDXMessage::getSeqNum() const
{
    return this->seqNum;
}

void AFDXMessage::setSeqNum(int seqNum)
{
    this->seqNum = seqNum;
}

int AFDXMessage::getPartitionId() const
{
    return this->partitionId;
}

void AFDXMessage::setPartitionId(int partitionId)
{
    this->partitionId = partitionId;
}

double AFDXMessage::getBagValue() const
{
    return this->bagValue;
}

void AFDXMessage::setBagValue(double bagValue)
{
    this->bagValue = bagValue;
}

double AFDXMessage::getRho() const
{
    return this->rho;
}

void AFDXMessage::setRho(double rho)
{
    this->rho = rho;
}

double AFDXMessage::getSigma() const
{
    return this->sigma;
}

void AFDXMessage::setSigma(double sigma)
{
    this->sigma = sigma;
}

::omnetpp::simtime_t AFDXMessage::getAFDXMarshallingTime() const
{
    return this->AFDXMarshallingTime;
}

void AFDXMessage::setAFDXMarshallingTime(::omnetpp::simtime_t AFDXMarshallingTime)
{
    this->AFDXMarshallingTime = AFDXMarshallingTime;
}

::omnetpp::simtime_t AFDXMessage::getRegLogExitTime() const
{
    return this->regLogExitTime;
}

void AFDXMessage::setRegLogExitTime(::omnetpp::simtime_t regLogExitTime)
{
    this->regLogExitTime = regLogExitTime;
}

::omnetpp::simtime_t AFDXMessage::getRegLogEntryTime() const
{
    return this->regLogEntryTime;
}

void AFDXMessage::setRegLogEntryTime(::omnetpp::simtime_t regLogEntryTime)
{
    this->regLogEntryTime = regLogEntryTime;
}

int AFDXMessage::getUdpSrcPort() const
{
    return this->udpSrcPort;
}

void AFDXMessage::setUdpSrcPort(int udpSrcPort)
{
    this->udpSrcPort = udpSrcPort;
}

int AFDXMessage::getUdpDestPort() const
{
    return this->udpDestPort;
}

void AFDXMessage::setUdpDestPort(int udpDestPort)
{
    this->udpDestPort = udpDestPort;
}

class AFDXMessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_networkId,
        FIELD_equipmentId,
        FIELD_interfaceId,
        FIELD_virtualLinkId,
        FIELD_seqNum,
        FIELD_partitionId,
        FIELD_bagValue,
        FIELD_rho,
        FIELD_sigma,
        FIELD_AFDXMarshallingTime,
        FIELD_regLogExitTime,
        FIELD_regLogEntryTime,
        FIELD_udpSrcPort,
        FIELD_udpDestPort,
    };
  public:
    AFDXMessageDescriptor();
    virtual ~AFDXMessageDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(AFDXMessageDescriptor)

AFDXMessageDescriptor::AFDXMessageDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(afdx::AFDXMessage)), "queueing::Job")
{
    propertyNames = nullptr;
}

AFDXMessageDescriptor::~AFDXMessageDescriptor()
{
    delete[] propertyNames;
}

bool AFDXMessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<AFDXMessage *>(obj)!=nullptr;
}

const char **AFDXMessageDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *AFDXMessageDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int AFDXMessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 14+base->getFieldCount() : 14;
}

unsigned int AFDXMessageDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_networkId
        FD_ISEDITABLE,    // FIELD_equipmentId
        FD_ISEDITABLE,    // FIELD_interfaceId
        FD_ISEDITABLE,    // FIELD_virtualLinkId
        FD_ISEDITABLE,    // FIELD_seqNum
        FD_ISEDITABLE,    // FIELD_partitionId
        FD_ISEDITABLE,    // FIELD_bagValue
        FD_ISEDITABLE,    // FIELD_rho
        FD_ISEDITABLE,    // FIELD_sigma
        FD_ISEDITABLE,    // FIELD_AFDXMarshallingTime
        FD_ISEDITABLE,    // FIELD_regLogExitTime
        FD_ISEDITABLE,    // FIELD_regLogEntryTime
        FD_ISEDITABLE,    // FIELD_udpSrcPort
        FD_ISEDITABLE,    // FIELD_udpDestPort
    };
    return (field >= 0 && field < 14) ? fieldTypeFlags[field] : 0;
}

const char *AFDXMessageDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "networkId",
        "equipmentId",
        "interfaceId",
        "virtualLinkId",
        "seqNum",
        "partitionId",
        "bagValue",
        "rho",
        "sigma",
        "AFDXMarshallingTime",
        "regLogExitTime",
        "regLogEntryTime",
        "udpSrcPort",
        "udpDestPort",
    };
    return (field >= 0 && field < 14) ? fieldNames[field] : nullptr;
}

int AFDXMessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "networkId") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "equipmentId") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "interfaceId") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "virtualLinkId") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "seqNum") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "partitionId") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "bagValue") == 0) return baseIndex + 6;
    if (strcmp(fieldName, "rho") == 0) return baseIndex + 7;
    if (strcmp(fieldName, "sigma") == 0) return baseIndex + 8;
    if (strcmp(fieldName, "AFDXMarshallingTime") == 0) return baseIndex + 9;
    if (strcmp(fieldName, "regLogExitTime") == 0) return baseIndex + 10;
    if (strcmp(fieldName, "regLogEntryTime") == 0) return baseIndex + 11;
    if (strcmp(fieldName, "udpSrcPort") == 0) return baseIndex + 12;
    if (strcmp(fieldName, "udpDestPort") == 0) return baseIndex + 13;
    return base ? base->findField(fieldName) : -1;
}

const char *AFDXMessageDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_networkId
        "int",    // FIELD_equipmentId
        "int",    // FIELD_interfaceId
        "int",    // FIELD_virtualLinkId
        "int",    // FIELD_seqNum
        "int",    // FIELD_partitionId
        "double",    // FIELD_bagValue
        "double",    // FIELD_rho
        "double",    // FIELD_sigma
        "omnetpp::simtime_t",    // FIELD_AFDXMarshallingTime
        "omnetpp::simtime_t",    // FIELD_regLogExitTime
        "omnetpp::simtime_t",    // FIELD_regLogEntryTime
        "int",    // FIELD_udpSrcPort
        "int",    // FIELD_udpDestPort
    };
    return (field >= 0 && field < 14) ? fieldTypeStrings[field] : nullptr;
}

const char **AFDXMessageDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *AFDXMessageDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int AFDXMessageDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    AFDXMessage *pp = omnetpp::fromAnyPtr<AFDXMessage>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void AFDXMessageDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    AFDXMessage *pp = omnetpp::fromAnyPtr<AFDXMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'AFDXMessage'", field);
    }
}

const char *AFDXMessageDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    AFDXMessage *pp = omnetpp::fromAnyPtr<AFDXMessage>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string AFDXMessageDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    AFDXMessage *pp = omnetpp::fromAnyPtr<AFDXMessage>(object); (void)pp;
    switch (field) {
        case FIELD_networkId: return long2string(pp->getNetworkId());
        case FIELD_equipmentId: return long2string(pp->getEquipmentId());
        case FIELD_interfaceId: return long2string(pp->getInterfaceId());
        case FIELD_virtualLinkId: return long2string(pp->getVirtualLinkId());
        case FIELD_seqNum: return long2string(pp->getSeqNum());
        case FIELD_partitionId: return long2string(pp->getPartitionId());
        case FIELD_bagValue: return double2string(pp->getBagValue());
        case FIELD_rho: return double2string(pp->getRho());
        case FIELD_sigma: return double2string(pp->getSigma());
        case FIELD_AFDXMarshallingTime: return simtime2string(pp->getAFDXMarshallingTime());
        case FIELD_regLogExitTime: return simtime2string(pp->getRegLogExitTime());
        case FIELD_regLogEntryTime: return simtime2string(pp->getRegLogEntryTime());
        case FIELD_udpSrcPort: return long2string(pp->getUdpSrcPort());
        case FIELD_udpDestPort: return long2string(pp->getUdpDestPort());
        default: return "";
    }
}

void AFDXMessageDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    AFDXMessage *pp = omnetpp::fromAnyPtr<AFDXMessage>(object); (void)pp;
    switch (field) {
        case FIELD_networkId: pp->setNetworkId(string2long(value)); break;
        case FIELD_equipmentId: pp->setEquipmentId(string2long(value)); break;
        case FIELD_interfaceId: pp->setInterfaceId(string2long(value)); break;
        case FIELD_virtualLinkId: pp->setVirtualLinkId(string2long(value)); break;
        case FIELD_seqNum: pp->setSeqNum(string2long(value)); break;
        case FIELD_partitionId: pp->setPartitionId(string2long(value)); break;
        case FIELD_bagValue: pp->setBagValue(string2double(value)); break;
        case FIELD_rho: pp->setRho(string2double(value)); break;
        case FIELD_sigma: pp->setSigma(string2double(value)); break;
        case FIELD_AFDXMarshallingTime: pp->setAFDXMarshallingTime(string2simtime(value)); break;
        case FIELD_regLogExitTime: pp->setRegLogExitTime(string2simtime(value)); break;
        case FIELD_regLogEntryTime: pp->setRegLogEntryTime(string2simtime(value)); break;
        case FIELD_udpSrcPort: pp->setUdpSrcPort(string2long(value)); break;
        case FIELD_udpDestPort: pp->setUdpDestPort(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'AFDXMessage'", field);
    }
}

omnetpp::cValue AFDXMessageDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    AFDXMessage *pp = omnetpp::fromAnyPtr<AFDXMessage>(object); (void)pp;
    switch (field) {
        case FIELD_networkId: return pp->getNetworkId();
        case FIELD_equipmentId: return pp->getEquipmentId();
        case FIELD_interfaceId: return pp->getInterfaceId();
        case FIELD_virtualLinkId: return pp->getVirtualLinkId();
        case FIELD_seqNum: return pp->getSeqNum();
        case FIELD_partitionId: return pp->getPartitionId();
        case FIELD_bagValue: return pp->getBagValue();
        case FIELD_rho: return pp->getRho();
        case FIELD_sigma: return pp->getSigma();
        case FIELD_AFDXMarshallingTime: return pp->getAFDXMarshallingTime().dbl();
        case FIELD_regLogExitTime: return pp->getRegLogExitTime().dbl();
        case FIELD_regLogEntryTime: return pp->getRegLogEntryTime().dbl();
        case FIELD_udpSrcPort: return pp->getUdpSrcPort();
        case FIELD_udpDestPort: return pp->getUdpDestPort();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'AFDXMessage' as cValue -- field index out of range?", field);
    }
}

void AFDXMessageDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    AFDXMessage *pp = omnetpp::fromAnyPtr<AFDXMessage>(object); (void)pp;
    switch (field) {
        case FIELD_networkId: pp->setNetworkId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_equipmentId: pp->setEquipmentId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_interfaceId: pp->setInterfaceId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_virtualLinkId: pp->setVirtualLinkId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_seqNum: pp->setSeqNum(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_partitionId: pp->setPartitionId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_bagValue: pp->setBagValue(value.doubleValue()); break;
        case FIELD_rho: pp->setRho(value.doubleValue()); break;
        case FIELD_sigma: pp->setSigma(value.doubleValue()); break;
        case FIELD_AFDXMarshallingTime: pp->setAFDXMarshallingTime(value.doubleValue()); break;
        case FIELD_regLogExitTime: pp->setRegLogExitTime(value.doubleValue()); break;
        case FIELD_regLogEntryTime: pp->setRegLogEntryTime(value.doubleValue()); break;
        case FIELD_udpSrcPort: pp->setUdpSrcPort(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_udpDestPort: pp->setUdpDestPort(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'AFDXMessage'", field);
    }
}

const char *AFDXMessageDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr AFDXMessageDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    AFDXMessage *pp = omnetpp::fromAnyPtr<AFDXMessage>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void AFDXMessageDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    AFDXMessage *pp = omnetpp::fromAnyPtr<AFDXMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'AFDXMessage'", field);
    }
}

}  // namespace afdx

namespace omnetpp {

}  // namespace omnetpp

