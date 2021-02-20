cplusplus {{
#include "omnetpp.h"
typedef cPar *ParPtr;
}}

class noncobject ParPtr;

//
// Message send between flooding attack controller and the hacked module
// 

message NA_FloodingMessage {
    int floodingGradeIndicator;
}
