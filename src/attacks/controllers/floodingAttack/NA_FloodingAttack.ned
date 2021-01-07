//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

import nesg.netattacks.attacks.controllers.NA_Attack;
package nesg.netattacks.attacks.controllers.floodingAttack;

//
// Dropping attack controller module.
// The Parameter floodingAttackQuantity controls the attack behavior
//
// @see NA_Attack, NA_IPv4
//
// @author Tim Falkenhahn
// @date 07/01/2021

simple NA_FloodingAttack extends NA_Attack
{
    parameters:
        @class(NA_FloodingAttack);
        @display("i=misc/cloud3,red,100;is=l");

        attackType = "flooding"; //Should correspond with the tag located in the hackedModules.ned. e.g. @flooding for this attack.
        double floodingAttackQuantity = default(0); //Quantity of false RREQ's sent into the network. Range [0,1].
}