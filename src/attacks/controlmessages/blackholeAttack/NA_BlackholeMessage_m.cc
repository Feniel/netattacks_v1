//
// Generated file, do not edit! Created by opp_msgc 4.3 from attacks/controlmessages/blackholeAttack/NA_BlackholeMessage.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "NA_BlackholeMessage_m.h"

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




Register_Class(NA_BlackholeMessage);

NA_BlackholeMessage::NA_BlackholeMessage(const char *name, int kind) : cMessage(name,kind)
{
    this->blackholeDropProbability_var = 0;
    this->numHops_var = 0;
}

NA_BlackholeMessage::NA_BlackholeMessage(const NA_BlackholeMessage& other) : cMessage(other)
{
    copy(other);
}

NA_BlackholeMessage::~NA_BlackholeMessage()
{
}

NA_BlackholeMessage& NA_BlackholeMessage::operator=(const NA_BlackholeMessage& other)
{
    if (this==&other) return *this;
    cMessage::operator=(other);
    copy(other);
    return *this;
}

void NA_BlackholeMessage::copy(const NA_BlackholeMessage& other)
{
    this->blackholeDropProbability_var = other.blackholeDropProbability_var;
    this->seqnoAdded_var = other.seqnoAdded_var;
    this->numHops_var = other.numHops_var;
}

void NA_BlackholeMessage::parsimPack(cCommBuffer *b)
{
    cMessage::parsimPack(b);
    doPacking(b,this->blackholeDropProbability_var);
    doPacking(b,this->seqnoAdded_var);
    doPacking(b,this->numHops_var);
}

void NA_BlackholeMessage::parsimUnpack(cCommBuffer *b)
{
    cMessage::parsimUnpack(b);
    doUnpacking(b,this->blackholeDropProbability_var);
    doUnpacking(b,this->seqnoAdded_var);
    doUnpacking(b,this->numHops_var);
}

double NA_BlackholeMessage::getBlackholeDropProbability() const
{
    return blackholeDropProbability_var;
}

void NA_BlackholeMessage::setBlackholeDropProbability(double blackholeDropProbability)
{
    this->blackholeDropProbability_var = blackholeDropProbability;
}

ParPtr& NA_BlackholeMessage::getSeqnoAdded()
{
    return seqnoAdded_var;
}

void NA_BlackholeMessage::setSeqnoAdded(const ParPtr& seqnoAdded)
{
    this->seqnoAdded_var = seqnoAdded;
}

int NA_BlackholeMessage::getNumHops() const
{
    return numHops_var;
}

void NA_BlackholeMessage::setNumHops(int numHops)
{
    this->numHops_var = numHops;
}

class NA_BlackholeMessageDescriptor : public cClassDescriptor
{
  public:
    NA_BlackholeMessageDescriptor();
    virtual ~NA_BlackholeMessageDescriptor();

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

Register_ClassDescriptor(NA_BlackholeMessageDescriptor);

NA_BlackholeMessageDescriptor::NA_BlackholeMessageDescriptor() : cClassDescriptor("NA_BlackholeMessage", "cMessage")
{
}

NA_BlackholeMessageDescriptor::~NA_BlackholeMessageDescriptor()
{
}

bool NA_BlackholeMessageDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<NA_BlackholeMessage *>(obj)!=NULL;
}

const char *NA_BlackholeMessageDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int NA_BlackholeMessageDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount(object) : 3;
}

unsigned int NA_BlackholeMessageDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<3) ? fieldTypeFlags[field] : 0;
}

const char *NA_BlackholeMessageDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "blackholeDropProbability",
        "seqnoAdded",
        "numHops",
    };
    return (field>=0 && field<3) ? fieldNames[field] : NULL;
}

int NA_BlackholeMessageDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='b' && strcmp(fieldName, "blackholeDropProbability")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "seqnoAdded")==0) return base+1;
    if (fieldName[0]=='n' && strcmp(fieldName, "numHops")==0) return base+2;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *NA_BlackholeMessageDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "double",
        "ParPtr",
        "int",
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : NULL;
}

const char *NA_BlackholeMessageDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int NA_BlackholeMessageDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    NA_BlackholeMessage *pp = (NA_BlackholeMessage *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string NA_BlackholeMessageDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    NA_BlackholeMessage *pp = (NA_BlackholeMessage *)object; (void)pp;
    switch (field) {
        case 0: return double2string(pp->getBlackholeDropProbability());
        case 1: {std::stringstream out; out << pp->getSeqnoAdded(); return out.str();}
        case 2: return long2string(pp->getNumHops());
        default: return "";
    }
}

bool NA_BlackholeMessageDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    NA_BlackholeMessage *pp = (NA_BlackholeMessage *)object; (void)pp;
    switch (field) {
        case 0: pp->setBlackholeDropProbability(string2double(value)); return true;
        case 2: pp->setNumHops(string2long(value)); return true;
        default: return false;
    }
}

const char *NA_BlackholeMessageDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        NULL,
        "ParPtr",
        NULL,
    };
    return (field>=0 && field<3) ? fieldStructNames[field] : NULL;
}

void *NA_BlackholeMessageDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    NA_BlackholeMessage *pp = (NA_BlackholeMessage *)object; (void)pp;
    switch (field) {
        case 1: return (void *)(&pp->getSeqnoAdded()); break;
        default: return NULL;
    }
}


