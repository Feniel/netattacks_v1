//
// Copyright (C) 2013, NESG (Network Engineering and Security Group), http://nesg.ugr.es,
// - Gabriel Maciá Fernández (gmacia@ugr.es)
// - Leovigildo Sánchez Casado (sancale@ugr.es)
// - Rafael A. Rodríguez Gómez (rodgom@ugr.es)
// - Roberto Magán Carrión (rmagan@ugr.es)
// - Pedro García Teodoro (pgteodor@ugr.es)
// - José Camacho Páez (josecamacho@ugr.es)
// - Jesús E. Díaz Verdejo (jedv@ugr.es)
//
// This file is part of NETA.
//
//    NETA is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    NETA is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with NETA.  If not, see <http://www.gnu.org/licenses/>.
//

#include "NA_IPv4.h"
#include <iostream>
#include <string.h>
#include "IPv4Datagram.h"

using std::cout;

simsignal_t NA_IPv4::dropSignal = SIMSIGNAL_NULL;
simsignal_t NA_IPv4::rcvdPktSignal = SIMSIGNAL_NULL;
simsignal_t NA_IPv4::delaySignal = SIMSIGNAL_NULL;
simsignal_t NA_IPv4::blackSignal = SIMSIGNAL_NULL;

Define_Module(NA_IPv4);

void NA_IPv4::initialize() {

    // Dropping attack initialization
    numDrops = 0;
    dropSignal = registerSignal("droppings");
    droppingAttackProbability = 0;
    droppingAttackIsActive = false;

    // Delay attack initialization
    delayAttackIsActive = false;
    delayAttackProbability = 0;
    numDelays = 0;
    delaySignal = registerSignal("delayed");
    totalDelayTime = 0;
    delayAttackValue = NULL;

    // Blackhole attack initialization
    numDrops = 0;
    blackSignal = registerSignal("blacked");
    blackholeAttackIsActive = false;
    blackholeDropProbability = 1;

    // Number of data packet received
    numRecvPacket = 0;
    rcvdPktSignal = registerSignal("rcvdPkt");

    IPv4::initialize();
}

void NA_IPv4::handleMessageFromAttackController(cMessage *msg) {

    // It is necessary to call Enter_Method for doing context switching (4.10 of User Manual)
    Enter_Method("NA_IPv4: handle message from attack controller");

    LOG << "NA_IPv4: Received message: " << msg->getFullName() << "\n";


    /*-------------------------- DROPPING ATTACK -------------------------*/
    if (not strcmp(msg->getFullName(), "droppingActivate")) {
        NA_DroppingMessage *dmsg;
        dmsg = check_and_cast<NA_DroppingMessage *>(msg);
        LOG << "--> Activating module NA_IPv4 for Dropping Attack...\n";
        LOG << "    Dropping Attack Probability received: "
                << dmsg->getDroppingAttackProbability() << "\n";
        //Now dropping attack is activated in this module
        droppingAttackIsActive = true;
        droppingAttackProbability = dmsg->getDroppingAttackProbability();
        //delete (msg);

    } else if (not strcmp(msg->getFullName(), "droppingDeactivate")) {
        NA_DroppingMessage *dmsg;
        dmsg = check_and_cast<NA_DroppingMessage *>(msg);
        LOG << "Deactivating module NA_IPv4 for Dropping Attack...\n";
        //Now dropping attack is deactivated
        droppingAttackIsActive = false;
        //delete (msg);
    }
    /*-------------------------- DELAY ATTACK -------------------------*/
    else if (not strcmp(msg->getFullName(), "delayActivate")) {
        NA_DelayMessage *dmsg;
        dmsg = check_and_cast<NA_DelayMessage *>(msg);
        LOG << "--> Activating module NA_IPv4 for Delay Attack...\n";
        LOG << "    Delay Attack Probability received: "
                << dmsg->getDelayAttackProbability() << "\n";
        LOG << "    Delay Attack Value received: "
                << dmsg->getDelayAttackValue() << "\n";
        delayAttackIsActive = true;
        delayAttackProbability = dmsg->getDelayAttackProbability();
        delayAttackValue = dmsg->getDelayAttackValue();
        delete (msg);

    } else if (not strcmp(msg->getFullName(), "delayDeactivate")) {
        NA_DelayMessage *dmsg;
        dmsg = check_and_cast<NA_DelayMessage *>(msg);
        LOG << "Deactivating module NA_IPv4 for Delay Attack...\n";
        delayAttackIsActive = false;
        delayAttackValue = NULL;
        delete (msg);
    }
    /*-------------------------- Blackhole ATTACK -------------------------*/
    else if (not strcmp(msg->getFullName(), "blackholeActivate")) {
        NA_BlackholeMessage *dmsg;
        dmsg = check_and_cast<NA_BlackholeMessage *>(msg);
        LOG << "--> Activating module NA_IPv4 for Blackhole Attack...\n";
        LOG << "    Blackhole Drop Probability is: "
                << dmsg->getBlackholeDropProbability() << "\n";
        //Now blackhole attack is activated in this module
        blackholeAttackIsActive = true;
        blackholeDropProbability = dmsg->getBlackholeDropProbability();
        delete (msg);
        // for debugging
        cout << simTime() << ": Blackhole IPV4 aktivated " << endl;

    } else if (not strcmp(msg->getFullName(), "blackholeDeactivate")) {
        NA_BlackholeMessage *dmsg;
        dmsg = check_and_cast<NA_BlackholeMessage *>(msg);
        LOG << "Deactivating module NA_IPv4 for Blackhole Attack...\n";
        //Now blackhole attack is deactivated
        blackholeAttackIsActive = false;
        delete (msg);
        // for debugging
        cout << simTime() << ": Blackhole IPV4 deaktivated " << endl;
    }

    else {
        LOG
                << "ERROR: Message unknown in NA_IPv4::handleMessageFromAttackController. Msg: "
                << msg->getFullName() << "\n";
    }
}

void NA_IPv4::handlePacketFromNetwork(IPv4Datagram *datagram,
        InterfaceEntry *fromIE) {

    ASSERT(datagram);

    // Count the number of total data packet received, for statistics.
    if (!strncmp(datagram->getName(), PING_DATA, 4)
            || !strncmp(datagram->getName(), UDP_DATA, 3)
            || !strncmp(datagram->getName(), TCP_DATA, 3)) {
        numRecvPacket++; // The number of packets is updated
        emit(rcvdPktSignal, numRecvPacket); // Sending of the signal indicating that we have received a new data packet.
    }

    if (blackholeAttackIsActive) {
            LOG << "Received packet after black hole attack is activated ... " << "\n";
            //cout << simTime() << ": Aktive Blackhole Received packet " << endl;
            //checks if the package is ping, udp or tcp
            if (!strncmp(datagram->getName(), PING_DATA, 4)
                || !strncmp(datagram->getName(), UDP_DATA, 3)
                || !strncmp(datagram->getName(), TCP_DATA, 3)) {
                    LOG << "Is a valid packet for dropping ..." << "\n";
                    //cout << simTime() << ": packet is valid for dropping " << endl;
                    if (uniform(0, 1) < blackholeDropProbability) {
                        numDrops++; // The number dropped packages is updated
                        emit(blackSignal, numDrops); // Sending a signal indicating a drop
                        LOG << "Discarding packet: " << datagram->getName() << ": "
                            << numDrops << " dropping times." << endl;
                        //cout << simTime() << ": Discarding packet: "
                        //     << datagram->getName() << endl;
                        delete datagram; //the package destructor is called
                    }
                    else {
                       IPv4::handlePacketFromNetwork(datagram, fromIE);
                    }
            }
            else { //Packet is not a ping, udp or tcp
                IPv4::handlePacketFromNetwork(datagram, fromIE);
            }
    }

    //Packet is a ping/UDP/TCP (data packet)
    else if (droppingAttackIsActive) {
        LOG << "Received packet after activating dropping attack ... " << "\n";
        if (!strncmp(datagram->getName(), PING_DATA, 4)
                || !strncmp(datagram->getName(), UDP_DATA, 3)
                || !strncmp(datagram->getName(), TCP_DATA, 3)) {
            LOG << "Is a valid packet for dropping ..." << "\n";
            if (uniform(0, 1) < droppingAttackProbability) {
                numDrops++; // The number of droppings is updated
                emit(dropSignal, numDrops); // Sending of the signal indicating a drop
                LOG << "Discarding packet: " << datagram->getName() << ": "
                        << numDrops << " dropping times." << endl;
                cout << simTime() << ": Discarding packet: "
                        << datagram->getName() << endl;
                delete datagram; //Deletes the datagram thus calling its destructor
            } else {
                IPv4::handlePacketFromNetwork(datagram, fromIE);
            }
        } else { //Packet is not a data packet --> normal behavior
            IPv4::handlePacketFromNetwork(datagram, fromIE);

        }

    } else { // --> Normal behavior.
        IPv4::handlePacketFromNetwork(datagram, fromIE);
    }
}

simtime_t NA_IPv4::startService(cPacket *msg) {

    // The value for the variable "delay" is obtained in QueueBase::initialize from the .ned parameter "procDelay".
    // Here, the delay attack add a new delay.

    double delayAttack = 0;

    if (delayAttackIsActive) {
        if (delayAttackValue != NULL) {
            if (!strncmp(msg->getName(), PING_DATA, 4)
                    || !strncmp(msg->getName(), UDP_DATA, 3)
                    || !strncmp(msg->getName(), TCP_DATA, 3)) {
                if (uniform(0, 1) < delayAttackProbability) {
                    delayAttack = delayAttackValue->doubleValue();
                    if (delayAttack < 0)
                        delayAttack = 0; //Avoid negative delays from a random distribution
                    numDelays++; // The number of packets delayed is updated
                    emit(delaySignal, numDelays); // Sending of the signal indicating a drop
                    LOG << "(NA_IPv4) Applied delay of: " << delayAttack
                            << "s. Packet name: " << msg->getFullName() << endl;
                    //cout << simTime() << ": (NA_IPv4) Applied delay of: " << delayAttack << "s. Packet name: " << msg->getFullName() << "\n";
                }
            }
        }
    }
    return delayAttack + delay;
}

