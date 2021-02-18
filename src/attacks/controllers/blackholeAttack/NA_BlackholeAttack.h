#ifndef NA_BLACKHOLEATTACK_H_
#define NA_BLACKHOLEATTACK_H_

#include "NA_Attack.h"
#include "NA_BlackholeMessage_m.h"

/**
 * @brief Blackhole attack controller implementation
 *
 * @details this controller generates the control message (blackhole message) containing
 * the configuration for the hacked modules of this attack.
 * In this case NA_IPv4.
 */
class NA_BlackholeAttack: public NA_Attack {

protected:

    //virtual cMessage *generateAttackMessage(const char* name);
    cMessage *generateAttackMessage(const char* name);
};

#endif /* NA_BLACKHOLEATTACK_H_ */
