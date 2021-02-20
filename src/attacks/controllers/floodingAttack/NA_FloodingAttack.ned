package nesg.netattacks.attacks.controllers.floodingAttack;
import nesg.netattacks.attacks.controllers.NA_Attack;

//
// Flooding attack controller module. The floodingGradeIndicator decides
// how many flooding rreq are send
//


simple NA_FloodingAttack extends NA_Attack
{
    parameters:
        @class(NA_FloodingAttack);
        @display("i=misc/cloud3,red,100;is=l");

        attackType = "flooding"; //Should correspond with the tag located in the hackedModules.ned. e.g. @flooding for this attack.
        volatile int floodingGradeIndicator = default(0); //Quantity of false RREQ's sent into the network.
}