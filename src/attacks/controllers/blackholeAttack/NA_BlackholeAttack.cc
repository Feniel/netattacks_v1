#include "NA_BlackholeAttack.h"
#include "NA_BlackholeMessage_m.h"

typedef cPar* ParPtr;

Define_Module (NA_BlackholeAttack);

cMessage *NA_BlackholeAttack::generateAttackMessage(const char *cmsg) {

    LOG << "NA_BlackholeAttack: generateAttackMessage\n";

    // Specific message for the specifics hacked modules.
    NA_BlackholeMessage *msg = new NA_BlackholeMessage(cmsg);
    msg->setBlackholeDropProbability(par("blackholeDropProbability").doubleValue());
    msg->setSeqnoAdded(&par("seqnoAdded"));
    msg->setNumHops(par("numHops"));
    msg->setSaodvAktive(par("saodvAktive").boolValue());
    msg->setFrreqAktive(par("frreqAktive").boolValue());
    return msg;
}
