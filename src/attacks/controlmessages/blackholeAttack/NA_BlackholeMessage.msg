cplusplus {{
#include "omnetpp.h"
typedef cPar *ParPtr;
}}

class noncobject ParPtr;

//
// Message interchanged between blackhole attack controller and the corresponding hacked
// module NA_IPv4.
//
// @see NA_BlackholeAttack, NA_IPv4
//
// @author Tim Falkenhahn
// @date 07/01/2021

message NA_BlackholeMessage {
    bool dropOnlyWhenRouteInTable; 	
    ParPtr seqnoAdded; 					
    int numHops;						
}
