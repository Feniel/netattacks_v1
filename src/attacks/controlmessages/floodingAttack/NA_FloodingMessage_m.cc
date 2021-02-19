//
// Generated file, do not edit! Created by opp_msgc 4.3 from attacks/controlmessages/floodingAttack/NA_FloodingMessage.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "NA_FloodingMessage_m.h"

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// Another default rule (prevents compiler from choosing base class' doPacking())
template<typename T>
void doPacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doPacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}

template<typename T>
void doUnpacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doUnpacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}




Register_Class(NA_FloodingMessage);

NA_FloodingMessage::NA_FloodingMessage(const char *name, int kind) : cMessage(name,kind)
{
    this->floodingGradeIndicator_var = 0;
}

NA_FloodingMessage::NA_FloodingMessage(const NA_FloodingMessage& other) : cMessage(other)
{
    copy(other);
}

NA_FloodingMessage::~NA_FloodingMessage()
{
}

NA_FloodingMessage& NA_FloodingMessage::operator=(const NA_FloodingMessage& other)
{
    if (this==&other) return *this;
    cMessage::operator=(other);
    copy(other);
    return *this;
}

void NA_FloodingMessage::copy(const NA_FloodingMessage& other)
{
    this->floodingGradeIndicator_var = other.floodingGradeIndicator_var;
}

void NA_FloodingMessage::parsimPack(cCommBuffer *b)
{
    cMessage::parsimPack(b);
    doPacking(b,this->floodingGradeIndicator_var);
}

void NA_FloodingMessage::parsimUnpack(cCommBuffer *b)
{
    cMessage::parsimUnpack(b);
    doUnpacking(b,this->floodingGradeIndicator_var);
}

double NA_FloodingMessage::getFloodingGradeIndicator() const
{
    return floodingGradeIndicator_var;
}

void NA_FloodingMessage::setFloodingGradeIndicator(double floodingGradeIndicator)
{
    this->floodingGradeIndicator_var = floodingGradeIndicator;
}

class NA_FloodingMessageDescriptor : public cClassDescriptor
{
  public:
    NA_FloodingMessageDescriptor();
    virtual ~NA_FloodingMessageDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(NA_FloodingMessageDescriptor);

NA_FloodingMessageDescriptor::NA_FloodingMessageDescriptor() : cClassDescriptor("NA_FloodingMessage", "cMessage")
{
}

NA_FloodingMessageDescriptor::~NA_FloodingMessageDescriptor()
{
}

bool NA_FloodingMessageDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<NA_FloodingMessage *>(obj)!=NULL;
}

const char *NA_FloodingMessageDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int NA_FloodingMessageDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
}

unsigned int NA_FloodingMessageDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *NA_FloodingMessageDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "floodingGradeIndicator",
    };
    return (field>=0 && field<1) ? fieldNames[field] : NULL;
}

int NA_FloodingMessageDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='f' && strcmp(fieldName, "floodingGradeIndicator")==0) return base+0;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *NA_FloodingMessageDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "double",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : NULL;
}

const char *NA_FloodingMessageDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int NA_FloodingMessageDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    NA_FloodingMessage *pp = (NA_FloodingMessage *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string NA_FloodingMessageDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    NA_FloodingMessage *pp = (NA_FloodingMessage *)object; (void)pp;
    switch (field) {
        case 0: return double2string(pp->getFloodingGradeIndicator());
        default: return "";
    }
}

bool NA_FloodingMessageDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    NA_FloodingMessage *pp = (NA_FloodingMessage *)object; (void)pp;
    switch (field) {
        case 0: pp->setFloodingGradeIndicator(string2double(value)); return true;
        default: return false;
    }
}

const char *NA_FloodingMessageDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        NULL,
    };
    return (field>=0 && field<1) ? fieldStructNames[field] : NULL;
}

void *NA_FloodingMessageDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    NA_FloodingMessage *pp = (NA_FloodingMessage *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


