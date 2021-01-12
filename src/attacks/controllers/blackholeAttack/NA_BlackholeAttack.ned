package nesg.netattacks.attacks.controllers.blackholeAttack;
import nesg.netattacks.attacks.controllers.NA_Attack;

//
// Blackhole attack controller simple module. Three parameter controls the attack behavior:
// the attack probability, if the route requested is knowed by the attacker or not and the
// the sequence number generated.
//
// @see NA_Attack, NA_AODVUU
//
// @author Tim Falkenhahn
// @date 11/01/2021

simple NA_BlackholeAttack extends NA_Attack
{
    parameters:
        @class(NA_BlackholeAttack);
        @display("i=misc/cloud3,red,100;is=l");

        attackType = "blackhole";  //Should correspond with the tag located in the hackedModules.ned. e.g. @blackhole for this attack.       
        bool dropOnlyWhenRouteInTable = default(false); //TRUE: Send fake answers to RREQ messages only when requested routes are really in routing table of blackhole node.
														//FALSE: Send fake answers for any RREQ messages arriving at the blackhole node.

        volatile double seqnoAdded = default(uniform(20, 30)); 	// Fake sequence number generated.
        volatile int numHops = default(1);						// Fake number of hops.
}
