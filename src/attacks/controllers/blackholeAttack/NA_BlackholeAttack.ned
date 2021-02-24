package nesg.netattacks.attacks.controllers.blackholeAttack;
import nesg.netattacks.attacks.controllers.NA_Attack;

//
// Blackhole attack controller module. One parameter decides if its a grey or
// blackhole attack
// 


simple NA_BlackholeAttack extends NA_Attack
{
    parameters:
        @class(NA_BlackholeAttack);
        @display("i=misc/cloud3,red,100;is=l");

        attackType = "blackhole";
        //defualt(1) for blackhole attack, else for greyhole attack	       
        double blackholeDropProbability = default(1);
        // Fake sequence number generated.	
        volatile double seqnoAdded = default(uniform(20, 30)); 
        // Fake number of hops.	
        volatile int numHops = default(1);	
}
