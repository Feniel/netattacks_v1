//
// Generated file, do not edit! Created by opp_msgc 4.3 from attacks/controlmessages/floodingAttack/NA_FloodingMessage.msg.
//

#ifndef _NA_FLOODINGMESSAGE_M_H_
#define _NA_FLOODINGMESSAGE_M_H_

#include <omnetpp.h>

// opp_msgc version check
#define MSGC_VERSION 0x0403
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of opp_msgc: 'make clean' should help.
#endif

// cplusplus {{
#include "omnetpp.h"
typedef cPar *ParPtr;
// }}



/**
 * Class generated from <tt>attacks/controlmessages/floodingAttack/NA_FloodingMessage.msg</tt> by opp_msgc.
 * <pre>
 * message NA_FloodingMessage {
 *     int floodingGradeIndicator;
 * }
 * </pre>
 */
class NA_FloodingMessage : public ::cMessage
{
  protected:
    int floodingGradeIndicator_var;

  private:
    void copy(const NA_FloodingMessage& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const NA_FloodingMessage&);

  public:
    NA_FloodingMessage(const char *name=NULL, int kind=0);
    NA_FloodingMessage(const NA_FloodingMessage& other);
    virtual ~NA_FloodingMessage();
    NA_FloodingMessage& operator=(const NA_FloodingMessage& other);
    virtual NA_FloodingMessage *dup() const {return new NA_FloodingMessage(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual int getFloodingGradeIndicator() const;
    virtual void setFloodingGradeIndicator(int floodingGradeIndicator);
};

inline void doPacking(cCommBuffer *b, NA_FloodingMessage& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, NA_FloodingMessage& obj) {obj.parsimUnpack(b);}


#endif // _NA_FLOODINGMESSAGE_M_H_
