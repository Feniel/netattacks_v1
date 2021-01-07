//
// Copyright (C) 2013 by NESG (Network Engineering and Security Group), http://nesg.ugr.es
// Dept. of Signal Theory, Telematics and Communications
// University of Granada
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
// Message interchanged between flooding attack controller and the corresponding hacked
// module NA_IPv4.
//
// @see NA_FloodingAttack, NA_IPv4
//
// @author Tim Falkenhahn
// @date 07/01/2021

message NA_FloodingMessage {
    double floodingAttackQuantity; // Quantity of false RREQ's
}
