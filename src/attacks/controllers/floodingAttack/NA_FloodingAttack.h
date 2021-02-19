#ifndef NA_FLOODINGATTACK_H_
#define NA_FLOODINGATTACK_H_

#include "NA_Attack.h"
#include "NA_FloodingMessage_m.h"

/**
 * @brief Flooding attack controller implementation
 *
 * @details this controller generates the control message (flooding message) containing
 * the configuration for the hacked modules of this attack.
 * In this case NA_AODVUU.
 */

class NA_FloodingAttack: public NA_Attack {

protected:

    virtual cMessage *generateAttackMessage(const char* msg);
};

#endif /* NA_FLOODINGATTACK_H_ */
