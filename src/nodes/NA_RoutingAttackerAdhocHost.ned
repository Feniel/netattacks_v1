//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

//
// Copyright (C) 2013 and modified by NESG (Network Engineering and Security Group), http://nesg.ugr.es,
// - Gabriel Maciá Fernández (gmacia@ugr.es)
// - Leovigildo Sánchez Casado (sancale@ugr.es)
// - Rafael A. Rodríguez Gómez (rodgom@ugr.es)
// - Roberto Magán Carrión (rmagan@ugr.es)
// - Pedro García Teodoro (pgteodor@ugr.es)
// - José Camacho Páez (josecamacho@ugr.es)
// - Jesús E. Díaz Verdejo (jedv@ugr.es)
//

package nesg.netattacks.nodes;


import nesg.netattacks.attacks.controllers.blackholeAttack.NA_BlackholeAttack;
import nesg.netattacks.nodes.NA_WirelessHost;
import inet.networklayer.IManetRouting;
import nesg.netattacks.attacks.controllers.NA_Attack;


//
// Attacker wireless ad hoc host. Modificated from WirelessHost module. 
// Redefined from INET framework and used as attacker host.
//
// To implement an attack you must include the corresponding attack controller module in the attacker host.
//
// This attack could be include N attacks controllers to implement several simultaneous attacks.
// The current attack controllers included are:
// - NA_DroppingAttack (dropping attack controller)
// - NA_DelayAttack (dropping attack controller)
// - NA_SinkholeAttack (dropping attack controller)
//
// @see AdhocHost, WirelessHost, NA_DroppingAttack, NA_DelayAttack, NA_SinkholeAttack
//
// @author Gabriel Maciá Fernández, gmacia@ugr.es
// @date 01/22/2013
module NA_RoutingAttackerAdhocHost extends NA_WirelessHost
{
    parameters:
        @display("i=device/cellphone,red;bgb=803,448;i2=status/lightning");
        wlan[*].mgmtType = default("Ieee80211MgmtAdhoc");  // use adhoc management
        string routingProtocol @enum("AODVUU","DYMOUM","DYMO","DSRUU","OLSR","OLSR_ETX","DSDV_2","Batman") = default("AODVUU");
        IPForward = default(true);

    submodules:
        manetrouting: <routingProtocol> like IManetRouting if routingProtocol != "" {
            @display("p=522,307");
        }
        na_BlackholeAttack: NA_BlackholeAttack {
            @display("p=704,53");
        }
    connections:
        networkLayer.manetOut --> manetrouting.from_ip if routingProtocol != "";
        networkLayer.manetIn <-- manetrouting.to_ip if routingProtocol != "";

}
