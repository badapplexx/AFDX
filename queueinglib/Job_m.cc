//
// Generated file, do not edit! Created by opp_msgtool 6.0 from Job.msg.
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
#include "Job_m.h"

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

namespace queueing {

Job_Base::Job_Base(const char *name, short kind) : ::omnetpp::cPacket(name, kind)
{
}

Job_Base::Job_Base(const Job_Base& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

Job_Base::~Job_Base()
{
}

Job_Base& Job_Base::operator=(const Job_Base& other)
{
    if (this == &other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void Job_Base::copy(const Job_Base& other)
{
    this->priority = other.priority;
    this->totalQueueingTime = other.totalQueueingTime;
    this->totalServiceTime = other.totalServiceTime;
    this->totalDelayTime = other.totalDelayTime;
    this->queueCount = other.queueCount;
    this->delayCount = other.delayCount;
    this->generation = other.generation;
}

void Job_Base::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->priority);
    doParsimPacking(b,this->totalQueueingTime);
    doParsimPacking(b,this->totalServiceTime);
    doParsimPacking(b,this->totalDelayTime);
    doParsimPacking(b,this->queueCount);
    doParsimPacking(b,this->delayCount);
    doParsimPacking(b,this->generation);
}

void Job_Base::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->priority);
    doParsimUnpacking(b,this->totalQueueingTime);
    doParsimUnpacking(b,this->totalServiceTime);
    doParsimUnpacking(b,this->totalDelayTime);
    doParsimUnpacking(b,this->queueCount);
    doParsimUnpacking(b,this->delayCount);
    doParsimUnpacking(b,this->generation);
}

int Job_Base::getPriority() const
{
    return this->priority;
}

void Job_Base::setPriority(int priority)
{
    this->priority = priority;
}

::omnetpp::simtime_t Job_Base::getTotalQueueingTime() const
{
    return this->totalQueueingTime;
}

void Job_Base::setTotalQueueingTime(::omnetpp::simtime_t totalQueueingTime)
{
    this->totalQueueingTime = totalQueueingTime;
}

::omnetpp::simtime_t Job_Base::getTotalServiceTime() const
{
    return this->totalServiceTime;
}

void Job_Base::setTotalServiceTime(::omnetpp::simtime_t totalServiceTime)
{
    this->totalServiceTime = totalServiceTime;
}

::omnetpp::simtime_t Job_Base::getTotalDelayTime() const
{
    return this->totalDelayTime;
}

void Job_Base::setTotalDelayTime(::omnetpp::simtime_t totalDelayTime)
{
    this->totalDelayTime = totalDelayTime;
}

int Job_Base::getQueueCount() const
{
    return this->queueCount;
}

void Job_Base::setQueueCount(int queueCount)
{
    this->queueCount = queueCount;
}

int Job_Base::getDelayCount() const
{
    return this->delayCount;
}

void Job_Base::setDelayCount(int delayCount)
{
    this->delayCount = delayCount;
}

int Job_Base::getGeneration() const
{
    return this->generation;
}

void Job_Base::setGeneration(int generation)
{
    this->generation = generation;
}

class JobDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_priority,
        FIELD_totalQueueingTime,
        FIELD_totalServiceTime,
        FIELD_totalDelayTime,
        FIELD_queueCount,
        FIELD_delayCount,
        FIELD_generation,
    };
  public:
    JobDescriptor();
    virtual ~JobDescriptor();

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

Register_ClassDescriptor(JobDescriptor)

JobDescriptor::JobDescriptor() : omnetpp::cClassDescriptor("queueing::Job", "omnetpp::cPacket")
{
    propertyNames = nullptr;
}

JobDescriptor::~JobDescriptor()
{
    delete[] propertyNames;
}

bool JobDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Job_Base *>(obj)!=nullptr;
}

const char **JobDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "customize",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *JobDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "customize")) return "true";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int JobDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 7+base->getFieldCount() : 7;
}

unsigned int JobDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_priority
        FD_ISEDITABLE,    // FIELD_totalQueueingTime
        FD_ISEDITABLE,    // FIELD_totalServiceTime
        FD_ISEDITABLE,    // FIELD_totalDelayTime
        FD_ISEDITABLE,    // FIELD_queueCount
        FD_ISEDITABLE,    // FIELD_delayCount
        FD_ISEDITABLE,    // FIELD_generation
    };
    return (field >= 0 && field < 7) ? fieldTypeFlags[field] : 0;
}

const char *JobDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "priority",
        "totalQueueingTime",
        "totalServiceTime",
        "totalDelayTime",
        "queueCount",
        "delayCount",
        "generation",
    };
    return (field >= 0 && field < 7) ? fieldNames[field] : nullptr;
}

int JobDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "priority") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "totalQueueingTime") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "totalServiceTime") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "totalDelayTime") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "queueCount") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "delayCount") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "generation") == 0) return baseIndex + 6;
    return base ? base->findField(fieldName) : -1;
}

const char *JobDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_priority
        "omnetpp::simtime_t",    // FIELD_totalQueueingTime
        "omnetpp::simtime_t",    // FIELD_totalServiceTime
        "omnetpp::simtime_t",    // FIELD_totalDelayTime
        "int",    // FIELD_queueCount
        "int",    // FIELD_delayCount
        "int",    // FIELD_generation
    };
    return (field >= 0 && field < 7) ? fieldTypeStrings[field] : nullptr;
}

const char **JobDescriptor::getFieldPropertyNames(int field) const
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

const char *JobDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int JobDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Job_Base *pp = omnetpp::fromAnyPtr<Job_Base>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void JobDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Job_Base *pp = omnetpp::fromAnyPtr<Job_Base>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Job_Base'", field);
    }
}

const char *JobDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Job_Base *pp = omnetpp::fromAnyPtr<Job_Base>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string JobDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Job_Base *pp = omnetpp::fromAnyPtr<Job_Base>(object); (void)pp;
    switch (field) {
        case FIELD_priority: return long2string(pp->getPriority());
        case FIELD_totalQueueingTime: return simtime2string(pp->getTotalQueueingTime());
        case FIELD_totalServiceTime: return simtime2string(pp->getTotalServiceTime());
        case FIELD_totalDelayTime: return simtime2string(pp->getTotalDelayTime());
        case FIELD_queueCount: return long2string(pp->getQueueCount());
        case FIELD_delayCount: return long2string(pp->getDelayCount());
        case FIELD_generation: return long2string(pp->getGeneration());
        default: return "";
    }
}

void JobDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Job_Base *pp = omnetpp::fromAnyPtr<Job_Base>(object); (void)pp;
    switch (field) {
        case FIELD_priority: pp->setPriority(string2long(value)); break;
        case FIELD_totalQueueingTime: pp->setTotalQueueingTime(string2simtime(value)); break;
        case FIELD_totalServiceTime: pp->setTotalServiceTime(string2simtime(value)); break;
        case FIELD_totalDelayTime: pp->setTotalDelayTime(string2simtime(value)); break;
        case FIELD_queueCount: pp->setQueueCount(string2long(value)); break;
        case FIELD_delayCount: pp->setDelayCount(string2long(value)); break;
        case FIELD_generation: pp->setGeneration(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Job_Base'", field);
    }
}

omnetpp::cValue JobDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Job_Base *pp = omnetpp::fromAnyPtr<Job_Base>(object); (void)pp;
    switch (field) {
        case FIELD_priority: return pp->getPriority();
        case FIELD_totalQueueingTime: return pp->getTotalQueueingTime().dbl();
        case FIELD_totalServiceTime: return pp->getTotalServiceTime().dbl();
        case FIELD_totalDelayTime: return pp->getTotalDelayTime().dbl();
        case FIELD_queueCount: return pp->getQueueCount();
        case FIELD_delayCount: return pp->getDelayCount();
        case FIELD_generation: return pp->getGeneration();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Job_Base' as cValue -- field index out of range?", field);
    }
}

void JobDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Job_Base *pp = omnetpp::fromAnyPtr<Job_Base>(object); (void)pp;
    switch (field) {
        case FIELD_priority: pp->setPriority(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_totalQueueingTime: pp->setTotalQueueingTime(value.doubleValue()); break;
        case FIELD_totalServiceTime: pp->setTotalServiceTime(value.doubleValue()); break;
        case FIELD_totalDelayTime: pp->setTotalDelayTime(value.doubleValue()); break;
        case FIELD_queueCount: pp->setQueueCount(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_delayCount: pp->setDelayCount(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_generation: pp->setGeneration(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Job_Base'", field);
    }
}

const char *JobDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr JobDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Job_Base *pp = omnetpp::fromAnyPtr<Job_Base>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void JobDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Job_Base *pp = omnetpp::fromAnyPtr<Job_Base>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Job_Base'", field);
    }
}

}  // namespace queueing

namespace omnetpp {

}  // namespace omnetpp

