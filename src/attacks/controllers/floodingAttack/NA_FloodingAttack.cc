#include "NA_FloodingAttack.h"
#include "NA_FloodingMessage_m.h"

typedef cPar* ParPtr;

Define_Module (NA_FloodingAttack);

cMessage *NA_FloodingAttack::generateAttackMessage(const char* cmsg) {

    LOG << "NA_FloodingAttack: generateAttackMessage\n";

    // Specific message for the specifics hacked modules.
    NA_FloodingMessage *msg = new NA_FloodingMessage(cmsg);
    msg->setFloodingAttackQuantity(
            par("floodingAttackQuantity").doubleValue());

    return msg;
}


