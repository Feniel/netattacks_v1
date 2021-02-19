package nesg.netattacks.simulations.AttackScenarios.FloodingAttackScenario;

import inet.networklayer.autorouting.ipv4.IPv4NetworkConfigurator;
import inet.nodes.inet.AdhocHost;
import inet.world.radio.ChannelControl;

import nesg.netattacks.nodes.*;


network Flooding_Network
{
    parameters:
        //	added blackholes
        int numFloodNodes;
        int numNodes;
        int numOriginator;
        int numDestination;
    submodules:
        // blackhole submodule configuration
        floodnode[numFloodNodes]: NA_AttackerAdhocHost {
            @display("p=295,219");
        }
        originator[numOriginator]: NA_AdhocHost {
            @display("p=138,270");
        }
        destination[numDestination]: NA_AdhocHost {
            @display("p=138,180");
        }
        node[numNodes]: NA_AdhocHost {
            @display("i=device/pocketpc_s;r=,,#707070;p=296,114");
        }
        channelControl: ChannelControl {
            parameters:
                @display("p=60,50;i=misc/sun");
        }
        configurator: IPv4NetworkConfigurator {
            parameters:
                config = xml("<config><interface hosts='*' address='145.236.x.x' netmask='255.255.0.0'/></config>");
                @display("p=140,50;i=block/cogwheel_s");
        }
    connections allowunconnected:
}
