#include "NA_FloodingAttack.h"
//#include "NA_FloodingMessage_m.h"

Define_Module (NA_FloodingAttack);

cMessage *NA_FloodingAttack::generateAttackMessage(const char* cmsg) {

    LOG << "NA_DroppingAttack: generateAttackMessage\n";

    // Specific message for the specifics hacked modules.
    NA_FloodingMessage *msg = new NA_DroppingMessage(cmsg);
    msg->setFloodingAttackQuantity(
            par("floodingAttackQuantity").doubleValue());

    return msg;
}


