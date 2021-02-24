cplusplus {{
#include "omnetpp.h"
typedef cPar *ParPtr;
}}

class noncobject ParPtr;

//
// Message send between blackhole attack controller and the hacked module
//

message NA_BlackholeMessage {
    double blackholeDropProbability; 	
    ParPtr seqnoAdded; 					
    int numHops;						
}
