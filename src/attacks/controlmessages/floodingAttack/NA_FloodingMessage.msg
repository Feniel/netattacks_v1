cplusplus {{
#include "omnetpp.h"
typedef cPar *ParPtr;
}}

class noncobject ParPtr;

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
