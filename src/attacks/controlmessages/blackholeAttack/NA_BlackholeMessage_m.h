//
// Generated file, do not edit! Created by opp_msgc 4.3 from attacks/controlmessages/blackholeAttack/NA_BlackholeMessage.msg.
//

#ifndef _NA_BLACKHOLEMESSAGE_M_H_
#define _NA_BLACKHOLEMESSAGE_M_H_

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
 * Class generated from <tt>attacks/controlmessages/blackholeAttack/NA_BlackholeMessage.msg</tt> by opp_msgc.
 * <pre>
 * message NA_BlackholeMessage {
 *     double blackholeDropProbability; 	
 *     ParPtr seqnoAdded; 					
 *     int numHops;						
 * }
 * </pre>
 */
class NA_BlackholeMessage : public ::cMessage
{
  protected:
    double blackholeDropProbability_var;
    ParPtr seqnoAdded_var;
    int numHops_var;

  private:
    void copy(const NA_BlackholeMessage& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const NA_BlackholeMessage&);

  public:
    NA_BlackholeMessage(const char *name=NULL, int kind=0);
    NA_BlackholeMessage(const NA_BlackholeMessage& other);
    virtual ~NA_BlackholeMessage();
    NA_BlackholeMessage& operator=(const NA_BlackholeMessage& other);
    virtual NA_BlackholeMessage *dup() const {return new NA_BlackholeMessage(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual double getBlackholeDropProbability() const;
    virtual void setBlackholeDropProbability(double blackholeDropProbability);
    virtual ParPtr& getSeqnoAdded();
    virtual const ParPtr& getSeqnoAdded() const {return const_cast<NA_BlackholeMessage*>(this)->getSeqnoAdded();}
    virtual void setSeqnoAdded(const ParPtr& seqnoAdded);
    virtual int getNumHops() const;
    virtual void setNumHops(int numHops);
};

inline void doPacking(cCommBuffer *b, NA_BlackholeMessage& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, NA_BlackholeMessage& obj) {obj.parsimUnpack(b);}


#endif // _NA_BLACKHOLEMESSAGE_M_H_
