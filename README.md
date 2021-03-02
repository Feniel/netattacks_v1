# netattacks_v1
extended Roberto Magán's framework (https://github.com/robertomagan/neta_v1) with some of the most common attacks against routing.<br>
In addition, defensive measures for the respective attack scenarios are also included.

For the implementation omnetpp-4.3 and inet2.1.0 is used.

Blackhole Attack<br>
An attack similar to the sinkhole attack, but it does not exploit a routing loop, but distributes false information in the network.<br>
Countermeasures: SAODV(Only the RREP Buffer), Fake RREQ

Flooding Attack<br>
The network is flooded with RREQ so that normal operation is no longer possible.<br>
Countermeasures: Policy Based Filtering, Flow Based Filtering


NETA Description
===================
NETwork Attacks (NETA) is a framework devised to simulate attacks in 
heterogeneous networks using OMNeT++. NETA is aimed to be an useful 
tool in the network security field. This tool could make easy to 
demonstrate the effectiveness of defense security techniques or 
solutions against network attacks as well as for comparing the 
capabilities of different defense techniques. NETA is a 
INET 2.1.0 based framework. INET provides realistic implementations 
of structures and protocols on each protocol layers, especially 
in the higher ones: network, transport and application layers. For example, 
INET develops Mobile Ad-hoc NETworks (MANETs) routing protocols as AODV, 
DSR, OLSR, etc., and several TCP implementations as well as several 
applications. Thanks to the versatile and extensible schema of NETA, 
a huge amount attacks could be implemented in each protocol layer.
 
Additionally,  NETA is intended to be a reference base tool for 
the network attacks simulation and implementation with research 
purposes. 

NETA Installation
============
See INSTALL file.

Documentation
==============
All documentation can be found in the doc directory. Also you can found there
the user and description manual. The additional attacks are inserted according to the scheme described there.

The defensive measures are inserted as an attribute of the manetrouting. 
Consequently, they must be set with bools in the simulation configurations.
