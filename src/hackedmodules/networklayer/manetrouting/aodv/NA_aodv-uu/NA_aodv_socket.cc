/*****************************************************************************
 *
 * Copyright (C) 2001 Uppsala University and Ericsson AB.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Authors: Erik Nordstr�, <erik.nordstrom@it.uu.se>
 *
 *****************************************************************************/

#define NS_PORT
#define OMNETPP

#include <algorithm>
#include <sys/types.h>

#ifdef NS_PORT
#ifndef OMNETPP
#include "ns/aodv-uu.h"
#else
#include "../NA_aodv_uu_omnet.h"
#endif
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <net/if.h>
#include <netinet/udp.h>
#include "NA_aodv_socket.h"
#include "NA_timer_queue_aodv.h"
#include "NA_aodv_rreq.h"
#include "NA_aodv_rerr.h"
#include "NA_aodv_rrep.h"
#include "NA_params.h"
#include "NA_aodv_hello.h"
#include "NA_aodv_neighbor.h"
#include "NA_debug_aodv.h"
#include "NA_defs_aodv.h"

#endif              /* NS_PORT */

    //SAODV
//        static RREP * rrep;
//        static double last_time_value,last_time = 0;
//       static std::vector<ManetAddress> table;
//        static std::vector<int> count_table;
//        static ManetAddress output_checksum,checksum,aux;
//        static struct in_addr saodv_rrep_orig,rrep_orig;
//        static int max_occurrence = 0;
//        static int vector_position = 99999;
//        static int output_counter = 0;
//        static std::vector<RREP *> message_rrep;
//        static std::vector<int> message_len;
//        static std::vector<struct in_addr> message_src;
//        static std::vector<struct in_addr> message_dst;
//        static std::vector<int> message_ttl;
//        static std::vector<unsigned int> message_ifindex;
    //pbf
//        static std::vector<struct in_addr> pbf_adresses;
//        static std::vector<struct in_addr> pbf_neighbor_blacklist;
//        static std::vector<int> pbf_neighbor_amount;
    //bfb
//        static std::vector<vector <struct in_addr> > fbf_list;
//        static std::vector<struct in_addr> fbf_neighbor_blacklist;
//        static struct in_addr fbf_tmp;
    //debug
//        static std::vector<struct in_addr> checklist;
//        static std::vector<int> amount;

#ifndef NS_PORT
#define SO_RECVBUF_SIZE 256*1024

static char recv_buf[RECV_BUF_SIZE];
static char send_buf[SEND_BUF_SIZE];

extern int wait_on_reboot, hello_qual_threshold, ratelimit;

static void aodv_socket_read(int fd);

/* Seems that some libc (for example ulibc) has a bug in the provided
 * CMSG_NXTHDR() routine... redefining it here */

static struct cmsghdr *__cmsg_nxthdr_fix(void *__ctl, size_t __size,
        struct cmsghdr *__cmsg)
{
    struct cmsghdr *__ptr;

    __ptr = (struct cmsghdr *) (((unsigned char *) __cmsg) +
                                CMSG_ALIGN(__cmsg->cmsg_len));
    if ((unsigned long) ((char *) (__ptr + 1) - (char *) __ctl) > __size)
        return NULL;

    return __ptr;
}

struct cmsghdr *cmsg_nxthdr_fix(struct msghdr *__msg, struct cmsghdr *__cmsg)
{
    return __cmsg_nxthdr_fix(__msg->msg_control, __msg->msg_controllen, __cmsg);
}

#endif              /* NS_PORT */


void NS_CLASS aodv_socket_init()
{
#ifndef NS_PORT
    struct sockaddr_in aodv_addr;
    struct ifreq ifr;
    int i, retval = 0;
    int on = 1;
    int tos = IPTOS_LOWDELAY;
    int bufsize = SO_RECVBUF_SIZE;
    socklen_t optlen = sizeof(bufsize);

    /* Create a UDP socket */

    if (this_host.nif == 0)
    {
        fprintf(stderr, "No interfaces configured\n");
        exit(-1);
    }

    /* Open a socket for every AODV enabled interface */
    for (i = 0; i < MAX_NR_INTERFACES; i++)
    {
        if (!DEV_NR(i).enabled)
            continue;

        /* AODV socket */
        DEV_NR(i).sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
        if (DEV_NR(i).sock < 0)
        {
            perror("");
            exit(-1);
        }
#ifdef CONFIG_GATEWAY
        /* Data packet send socket */
        DEV_NR(i).psock = socket(PF_INET, SOCK_RAW, IPPROTO_RAW);

        if (DEV_NR(i).psock < 0)
        {
            perror("");
            exit(-1);
        }
#endif
        /* Bind the socket to the AODV port number */
        memset(&aodv_addr, 0, sizeof(aodv_addr));
        aodv_addr.sin_family = AF_INET;
        aodv_addr.sin_port = htons(AODV_PORT);
        aodv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

        retval = bind(DEV_NR(i).sock, (struct sockaddr *) &aodv_addr,
                      sizeof(struct sockaddr));

        if (retval < 0)
        {
            perror("Bind failed ");
            exit(-1);
        }
        if (setsockopt(DEV_NR(i).sock, SOL_SOCKET, SO_BROADCAST,
                       &on, sizeof(int)) < 0)
        {
            perror("SO_BROADCAST failed ");
            exit(-1);
        }

        memset(&ifr, 0, sizeof(struct ifreq));
        strcpy(ifr.ifr_name, DEV_NR(i).ifname);

        if (setsockopt(DEV_NR(i).sock, SOL_SOCKET, SO_BINDTODEVICE,
                       &ifr, sizeof(ifr)) < 0)
        {
            fprintf(stderr, "SO_BINDTODEVICE failed for %s", DEV_NR(i).ifname);
            perror(" ");
            exit(-1);
        }

        if (setsockopt(DEV_NR(i).sock, SOL_SOCKET, SO_PRIORITY,
                       &tos, sizeof(int)) < 0)
        {
            perror("Setsockopt SO_PRIORITY failed ");
            exit(-1);
        }

        if (setsockopt(DEV_NR(i).sock, SOL_IP, IP_RECVTTL,
                       &on, sizeof(int)) < 0)
        {
            perror("Setsockopt IP_RECVTTL failed ");
            exit(-1);
        }

        if (setsockopt(DEV_NR(i).sock, SOL_IP, IP_PKTINFO,
                       &on, sizeof(int)) < 0)
        {
            perror("Setsockopt IP_PKTINFO failed ");
            exit(-1);
        }
#ifdef CONFIG_GATEWAY
        if (setsockopt(DEV_NR(i).psock, SOL_SOCKET, SO_BINDTODEVICE,
                       &ifr, sizeof(ifr)) < 0)
        {
            fprintf(stderr, "SO_BINDTODEVICE failed for %s", DEV_NR(i).ifname);
            perror(" ");
            exit(-1);
        }

        bufsize = 4 * 65535;

        if (setsockopt(DEV_NR(i).psock, SOL_SOCKET, SO_SNDBUF,
                       (char *) &bufsize, optlen) < 0)
        {
            DEBUG(LOG_NOTICE, 0, "Could not set send socket buffer size");
        }
        if (getsockopt(DEV_NR(i).psock, SOL_SOCKET, SO_SNDBUF,
                       (char *) &bufsize, &optlen) == 0)
        {
            alog(LOG_NOTICE, 0, __FUNCTION__,
                 "RAW send socket buffer size set to %d", bufsize);
        }
#endif
        /* Set max allowable receive buffer size... */
        for (;; bufsize -= 1024)
        {
            if (setsockopt(DEV_NR(i).sock, SOL_SOCKET, SO_RCVBUF,
                           (char *) &bufsize, optlen) == 0)
            {
                alog(LOG_NOTICE, 0, __FUNCTION__,
                     "Receive buffer size set to %d", bufsize);
                break;
            }
            if (bufsize < RECV_BUF_SIZE)
            {
                alog(LOG_ERR, 0, __FUNCTION__,
                     "Could not set receive buffer size");
                exit(-1);
            }
        }

        retval = attach_callback_func(DEV_NR(i).sock, aodv_socket_read);

        if (retval < 0)
        {
            perror("register input handler failed ");
            exit(-1);
        }
    }
#endif              /* NS_PORT */

    num_rreq = 0;
    num_rerr = 0;
}

//SAODV
void NS_CLASS checkSAODVTable (){
    //collecting rrep right now ?
    if( table.size() > 0 ){
        //trace the time
        if(last_time == 0){
            last_time = simTime().dbl();
        }else{
            last_time_value += simTime().dbl() - last_time;
            last_time = simTime().dbl();
        }
        if(last_time_value > 6){
            ManetAddress output_checksum;
            int max_occurrence, output_counter, index = 0;
            bool outOfBound = true;
            //which gateway was mostly used
            for(int i;i<count_table.size();i++){
                if(max_occurrence<count_table[i]){
                    max_occurrence = count_table[i];
                    index = i;
                }
            }
            //get the first rrep from this gateway out of the collected rreps
            output_checksum = message_src[output_counter].S_addr;
            while(table[index] != output_checksum & outOfBound){
                //out of bound detection
                if(output_counter > message_src.size()){
                    output_counter = 0;
                    outOfBound = false;
                }else{
                    output_counter++;
                    output_checksum = message_src[output_counter].S_addr;
                }
            }
            //send the first rrep from the most used gateway
            RREP * buffer = &message_rrep[output_counter];
            rrep_process(buffer,
                    message_len[output_counter],
                    message_src[output_counter],
                    message_dst[output_counter],
                    message_ttl[output_counter],
                    message_ifindex[output_counter]);
            //init for next rrep process
            last_time = 0.0;
            last_time_value = 0.0;
            table.clear();
            count_table.clear();
            message_rrep.clear();
            message_len.clear();
            message_src.clear();
            message_dst.clear();
            message_ttl.clear();
            message_ifindex.clear();
        }
    }
}

void NS_CLASS aodv_socket_process_packet(AODV_msg * aodv_msg, int len,
        struct in_addr src,
        struct in_addr dst,
        int ttl, unsigned int ifindex)
{

    /* If this was a HELLO message... Process as HELLO. */
#ifndef OMNETPP
    if ((aodv_msg->type == AODV_RREP && ttl == 1 &&
            dst.s_addr == AODV_BROADCAST))
    {
        hello_process((RREP *) aodv_msg, len, ifindex);
        return;
    }
#else
    if ((aodv_msg->type == AODV_RREP && ttl == 0 && // ttl is decremented for ip layer before send to aodv
            dst.s_addr == ManetAddress(IPv4Address(AODV_BROADCAST))))
    {
        hello_process((RREP *) aodv_msg, len, ifindex);
        return;
    }
#endif
    /* Make sure we add/update neighbors */
    neighbor_add(aodv_msg, src, ifindex);

    /* Check what type of msg we received and call the corresponding
       function to handle the msg... */
    switch (aodv_msg->type)
    {

    case AODV_RREQ:
        //std::cout << pbfActive << endl;
        //std::cout << fbfActive << endl;

        if( false ){
            int index = -1;
            for( int i=0; i < checklist.size();i++ ){
                if( checklist[i].S_addr == src.S_addr){
                    index = i;
                }
            }
            if ( index == -1){
                checklist.push_back(src);
                amount.push_back(1);
            }else{
                amount[index] += 1 ;
            }
            for (int j=0; j< amount.size();j++){
                if(output < amount[j]){
                    third = second;
                    second = output;
                    output = amount[j];
                    std::cout << this->info() << " " << output << " | " << second << " | " << third << endl;
                }
            }
        }
        if( pbfActive ){
            int index = -1;
            //is there a entry for src in blacklist ?
            if( find(pbf_neighbor_blacklist.begin(), pbf_neighbor_blacklist.end(), src.S_addr) == pbf_neighbor_blacklist.end() ){
                for( int h=0; h < pbf_adresses.size();h++ ){
                    if( pbf_adresses[h].S_addr == src.S_addr){
                        index = h;
                    }
                }
                // do we already know this src ?
                if( index == -1 ){
                    // create new entry
                    pbf_adresses.push_back(src);
                    pbf_neighbor_amount.push_back(1);
                    rreq_process((RREQ *) aodv_msg, len, src, dst, ttl, ifindex);
                    break;
                }else{
                    // increase amount existing entry
                    pbf_neighbor_amount[index] = pbf_neighbor_amount[index] + 1;
                    // is the threshold exceeded ?
                    if( pbf_neighbor_amount[index] > pbf_threshold ){
                        // add src to blacklist
                        pbf_neighbor_blacklist.push_back(src.S_addr);
                        break;
                    }else{
                        // proceeed
                        rreq_process((RREQ *) aodv_msg, len, src, dst, ttl, ifindex);
                        break;
                    }
                }
            }else{
                break;
            }
        }else if( fbfActive ){
            RREQ * rreq = (RREQ *) aodv_msg;
            int index = -1;
            struct in_addr tmp;
            tmp.S_addr = rreq->dest_addr;
            for( int i=0; i < fbf_list.size();i++ ){
                if (fbf_list[i][0].S_addr == src.S_addr){
                    index = i;
                }
            }
            // contains the blacklist an src entry ?
            if( find(fbf_neighbor_blacklist.begin(), fbf_neighbor_blacklist.end(), src.S_addr) == fbf_neighbor_blacklist.end() ){
                // did we know this src ?
                if( index == -1){
                    // add it to the list
                    vector <struct in_addr> node;
                    node.push_back(src);
                    node.push_back(tmp);
                    fbf_list.push_back(node);
                    rreq_process((RREQ *) aodv_msg, len, src, dst, ttl, ifindex);
                    break;
                }else{
                    // increment
                    fbf_list[index].push_back(tmp);
                    // check if to many org and the threshold exceeded
                    if (fbf_list[index].size()-1 > fbf_threshold){
                        fbf_neighbor_blacklist.push_back(src.S_addr);
                        break;
                    }else{
                        // proceed
                        rreq_process((RREQ *) aodv_msg, len, src, dst, ttl, ifindex);
                        break;
                    }
                }
            }else{
                fbf_list[index].push_back(tmp);
                break;
            }
        }else{
            rreq_process((RREQ *) aodv_msg, len, src, dst, ttl, ifindex);
            break;
        }
        break;
    case AODV_RREP:
        DEBUG(LOG_DEBUG, 0, "Received RREP");

        //SAODV
        if( saodvActive ){
            rrep = (RREP *)aodv_msg;
            //Convert to correct byte order on affected fields
            if (getAp(rrep->orig_addr, aux)){
                saodv_rrep_orig.s_addr = aux;
            }else {
                saodv_rrep_orig.s_addr = rrep->orig_addr;
            }
            //is this rrep for us ?
            saodv_rrep_orig.s_addr = rrep->orig_addr;
            if( addressIsForUs( saodv_rrep_orig.S_addr )){
                //did we got a rrep from this gateway already ? check vector
                vector_position = -1;
                for(int i=0;i<table.size();i++){
                    if( table[i] == src.S_addr ){
                        vector_position = i;
                    }
                }
                if( vector_position == -1 ){
                    //the gateway is new
                    table.push_back(src.S_addr);
                    count_table.push_back(1);
                }else{
                    //we know the gateway
                    count_table[vector_position] = count_table[vector_position] + 1;
                }
                //cast aodv_msg into RREP pointer to save the message pointer
                RREP * tmp = (RREP *) aodv_msg;
                //save rrep for later
                message_rrep.push_back(*tmp);
                message_len.push_back(len);
                message_src.push_back(src);
                message_dst.push_back(dst);
                message_ttl.push_back(ttl);
                message_ifindex.push_back(ifindex);
                break;
            }else{
                rrep_process((RREP *) aodv_msg, len, src, dst, ttl, ifindex);
                break;
            }
        //frreq
        }else if(frreqActive){
            rrep = (RREP *)aodv_msg;
            rrep_orig.s_addr = rrep->getOrig_addr();
            if( addressIsForUs(rrep_orig.S_addr) ){
                //is it a fake rreq ?
                if ( checkFakeRREP(rrep->init_rreq_addr.getIPv4()) ){
                    addBlacklist(rrep->creator);
                }else{
                    //is the creator blacklisted ?
                    if ( creatorBlacklisted(rrep->creator) ){
                        break;
                    }else{
                        rrep_process((RREP *) aodv_msg, len, src, dst, ttl, ifindex);
                        break;
                    }
                }
            }
        }else{
            rrep_process((RREP *) aodv_msg, len, src, dst, ttl, ifindex);
            break;
        }
        //rrep_process((RREP *) aodv_msg, len, src, dst, ttl, ifindex);
        break;
    case AODV_RERR:
        DEBUG(LOG_DEBUG, 0, "Received RERR");
        rerr_process((RERR *) aodv_msg, len, src, dst);
        break;
    case AODV_RREP_ACK:
        DEBUG(LOG_DEBUG, 0, "Received RREP_ACK");
        rrep_ack_process((RREP_ack *) aodv_msg, len, src, dst);
        break;
    default:
        alog(LOG_WARNING, 0, __FUNCTION__,
             "Unknown msg type %u rcvd from %s to %s", aodv_msg->type,
             ip_to_str(src), ip_to_str(dst));
        break;
    }
}

#ifdef NS_PORT
#ifndef OMNETPP
void NS_CLASS recvAODVUUPacket(Packet * p)
{
    int len, i, ttl = 0;
    struct in_addr src, dst;
    struct hdr_cmn *ch = HDR_CMN(p);
    struct hdr_ip *ih = HDR_IP(p);
    hdr_aodvuu *ah = HDR_AODVUU(p);

    src.s_addr = ih->saddr();
    dst.s_addr = ih->daddr();
    len = ch->size() - IP_HDR_LEN;
    ttl = ih->ttl();

    AODV_msg *aodv_msg = (AODV_msg *) recv_buf;

    /* Only handle AODVUU packets */
    assert(ch->ptype() == PT_AODVUU);

    /* Only process incoming packets */
    assert(ch->direction() == hdr_cmn::UP);

    /* Copy message to receive buffer */
    memcpy(recv_buf, ah, RECV_BUF_SIZE);

    /* Deallocate packet, we have the information we need... */
    Packet::free(p);

    /* Ignore messages generated locally */
    for (i = 0; i < MAX_NR_INTERFACES; i++)
        if (this_host.devs[i].enabled &&
                memcmp(&src, &this_host.devs[i].ipaddr,
                       sizeof(struct in_addr)) == 0)
            return;

    aodv_socket_process_packet(aodv_msg, len, src, dst, ttl, NS_IFINDEX);
}
#endif /*no omnet++*/
#else
static void aodv_socket_read(int fd)
{
    struct in_addr src, dst;
    int i, len, ttl = -1;
    AODV_msg *aodv_msg;
    struct dev_info *dev;
    struct msghdr msgh;
    struct cmsghdr *cmsg;
    struct iovec iov;
    char ctrlbuf[CMSG_SPACE(sizeof(int)) +
                 CMSG_SPACE(sizeof(struct in_pktinfo))];
    struct sockaddr_in src_addr;

    iov.iov_base = recv_buf;
    iov.iov_len = RECV_BUF_SIZE;
    msgh.msg_name = &src_addr;
    msgh.msg_namelen = sizeof(src_addr);
    msgh.msg_iov = &iov;
    msgh.msg_iovlen = 1;
    msgh.msg_control = ctrlbuf;
    msgh.msg_controllen = sizeof(ctrlbuf);

    len = recvmsg(fd, &msgh, 0);

    if (len < 0)
    {
        alog(LOG_WARNING, 0, __FUNCTION__, "receive ERROR len=%d!", len);
        return;
    }

    src.s_addr = src_addr.sin_addr.s_addr;

    /* Get the ttl and destination address from the control message */
    for (cmsg = CMSG_FIRSTHDR(&msgh); cmsg != NULL;
            cmsg = CMSG_NXTHDR_FIX(&msgh, cmsg))
    {
        if (cmsg->cmsg_level == SOL_IP)
        {
            switch (cmsg->cmsg_type)
            {
            case IP_TTL:
                ttl = *(CMSG_DATA(cmsg));
                break;
            case IP_PKTINFO:
                dst.s_addr =
                    ((struct in_pktinfo *) CMSG_DATA(cmsg))->ipi_addr.s_addr;
            }
        }
    }

    if (ttl < 0)
    {
        DEBUG(LOG_DEBUG, 0, "No TTL, packet ignored!");
        return;
    }

    /* Ignore messages generated locally */
    for (i = 0; i < MAX_NR_INTERFACES; i++)
        if (this_host.devs[i].enabled &&
                memcmp(&src, &this_host.devs[i].ipaddr,
                       sizeof(struct in_addr)) == 0)
            return;

    aodv_msg = (AODV_msg *) recv_buf;

    dev = devfromsock(fd);

    if (!dev)
    {
        DEBUG(LOG_ERR, 0, "Could not get device info!\n");
        return;
    }

    aodv_socket_process_packet(aodv_msg, len, src, dst, ttl, dev->ifindex);
}
#endif              /* NS_PORT */

void NS_CLASS aodv_socket_send(AODV_msg * aodv_msg, struct in_addr dst,
                               int len, u_int8_t ttl, struct dev_info *dev,double delay)
{

    struct timeval now;
    int retval = 0;
    /* Rate limit stuff: */

#ifdef OMNETPP
    if (ttl<=0)
    {
        delete aodv_msg;
        return;
    }
#endif

#ifndef NS_PORT

    struct sockaddr_in dst_addr;

    if (wait_on_reboot && aodv_msg->type == AODV_RREP)
        return;

    memset(&dst_addr, 0, sizeof(dst_addr));
    dst_addr.sin_family = AF_INET;
    dst_addr.sin_addr = dst;
    dst_addr.sin_port = htons(AODV_PORT);

    /* Set ttl */
    if (setsockopt(dev->sock, SOL_IP, IP_TTL, &ttl, sizeof(ttl)) < 0)
    {
        alog(LOG_WARNING, 0, __FUNCTION__, "ERROR setting ttl!");
        return;
    }
#else

    /*
       NS_PORT: Sending of AODV_msg messages to other AODV-UU routing agents
       by encapsulating them in a Packet.

       Note: This method is _only_ for sending AODV packets to other routing
       agents, _not_ for forwarding "regular" IP packets!
     */

    /* If we are in waiting phase after reboot, don't send any RREPs */
    if (wait_on_reboot && aodv_msg->type == AODV_RREP)
    {
#ifdef OMNETPP
        delete aodv_msg;
#endif
        return;
    }
#ifndef OMNETPP
    /*
       NS_PORT: Don't allocate packet until now. Otherwise packet uid
       (unique ID) space is unnecessarily exhausted at the beginning of
       the simulation, resulting in uid:s starting at values greater than 0.
     */
    Packet *p = allocpkt();
    struct hdr_cmn *ch = HDR_CMN(p);
    struct hdr_ip *ih = HDR_IP(p);
    hdr_aodvuu *ah = HDR_AODVUU(p);

    // Clear AODVUU part of packet
    memset(ah, '\0', ah->size());

    // Copy message contents into packet
    memcpy(ah, aodv_msg, len);

    // Set common header fields
    ch->ptype() = PT_AODVUU;
    ch->direction() = hdr_cmn::DOWN;
    ch->size() = IP_HDR_LEN + len;
    ch->iface() = -2;
    ch->getBitErrorRate() = 0;
    ch->prev_hop_ = (nsaddr_t) dev->ipaddr.s_addr;

    // Set IP header fields
    ih->saddr() = (nsaddr_t) dev->ipaddr.s_addr;
    ih->daddr() = (nsaddr_t) dst.s_addr;
    ih->ttl() = ttl;

    // Note: Port number for routing agents, not AODV port number!
    ih->sport() = RT_PORT;
    ih->dport() = RT_PORT;

    // Fake success
    retval = len;
#endif /*omnet++ */
#endif              /* NS_PORT */

    /* If rate limiting is enabled, check if we are sending either a
       RREQ or a RERR. In that case, drop the outgoing control packet
       if the time since last transmit of that type of packet is less
       than the allowed RATE LIMIT time... */
    if(false){
    //if (ratelimit)
    //{

        gettimeofday(&now, NULL);

        switch (aodv_msg->type)
        {
        case AODV_RREQ:
            if (num_rreq == (RREQ_RATELIMIT - 1))
            {
                if (timeval_diff(&now, &rreq_ratel[0]) < 1000)
                {
                    DEBUG(LOG_DEBUG, 0, "RATELIMIT: Dropping RREQ %ld ms",
                          timeval_diff(&now, &rreq_ratel[0]));
#ifdef OMNETPP
                    delete aodv_msg;
#else
#ifdef NS_PORT
                    Packet::free(p);
#endif
#endif
                    return;
                }
                else
                {
                    memmove(rreq_ratel, &rreq_ratel[1],
                            sizeof(struct timeval) * (num_rreq - 1));
                    memcpy(&rreq_ratel[num_rreq - 1], &now,
                           sizeof(struct timeval));
                }
            }
            else
            {
                memcpy(&rreq_ratel[num_rreq], &now, sizeof(struct timeval));
                num_rreq++;
            }
            break;
        case AODV_RERR:
            if (num_rerr == (RERR_RATELIMIT - 1))
            {
                if (timeval_diff(&now, &rerr_ratel[0]) < 1000)
                {
                    DEBUG(LOG_DEBUG, 0, "RATELIMIT: Dropping RERR %ld ms",
                          timeval_diff(&now, &rerr_ratel[0]));
#ifdef OMNETPP
                    delete aodv_msg;
#else
#ifdef NS_PORT
                    Packet::free(p);
#endif
#endif
                    return;
                }
                else
                {
                    memmove(rerr_ratel, &rerr_ratel[1],
                            sizeof(struct timeval) * (num_rerr - 1));
                    memcpy(&rerr_ratel[num_rerr - 1], &now,
                           sizeof(struct timeval));
                }
            }
            else
            {
                memcpy(&rerr_ratel[num_rerr], &now, sizeof(struct timeval));
                num_rerr++;
            }
            break;
        }
    }

    /* If we broadcast this message we update the time of last broadcast
       to prevent unnecessary broadcasts of HELLO msg's */
    if (dst.s_addr == ManetAddress(IPv4Address(AODV_BROADCAST)))
    {
        gettimeofday(&this_host.bcast_time, NULL);

#ifdef NS_PORT
#ifndef OMNETPP
        ch->addr_type() = NS_AF_NONE;
        sendPacket(p, dst, 0.0);
#else
//       IPv4Address   desAddIp4(dst.s_addr);
//       IPvXAddress destAdd(desAddIp4);
// In the floading proccess the random delay prevent collision for the synchronization between the nodes.
        ManetAddress destAdd;
        aodv_msg->prevFix=this->isStaticNode();

        if (this->isStaticNode())
        {
            if (dynamic_cast<RREP*>(aodv_msg))
            {
                dynamic_cast<RREP*>(aodv_msg)->cost += costStatic;
            }
            else if (dynamic_cast<RREQ*> (aodv_msg))
            {
                dynamic_cast<RREQ*>(aodv_msg)->cost += costStatic;
            }
        }
        else
        {
            if (dynamic_cast<RREP*>(aodv_msg))
            {
                dynamic_cast<RREP*>(aodv_msg)->cost += costMobile;
            }
            else if (dynamic_cast<RREQ*>(aodv_msg))
            {
                dynamic_cast<RREQ*>(aodv_msg)->cost += costMobile;
            }
        }



        if (dst.s_addr == ManetAddress(IPv4Address(AODV_BROADCAST)))
        {
            destAdd = ManetAddress(IPv4Address::ALLONES_ADDRESS);
        }
        else
        {
            destAdd = dst.s_addr;
        }
        if (delay>0)
        {
            if (useIndex)
                sendToIp(aodv_msg, 654, destAdd, 654, ttl, delay, dev->ifindex);
            else
                sendToIp(aodv_msg, 654, destAdd, 654, ttl, delay, dev->ipaddr.s_addr);
        }
        else
        {
            if (useIndex)
                sendToIp(aodv_msg, 654, destAdd, 654, ttl, par ("broadcastDelay").doubleValue(), dev->ifindex);
            else
                sendToIp(aodv_msg, 654, destAdd, 654, ttl, par ("broadcastDelay").doubleValue(), dev->ipaddr.s_addr);
        }
        totalSend++;
//       sendToIp(aodv_msg, 654, destAdd, 654,ttl);
#endif /*omnet++ */
#else
        retval = sendto(dev->sock, send_buf, len, 0,
                        (struct sockaddr *) &dst_addr, sizeof(dst_addr));

        if (retval < 0)
        {
            alog(LOG_WARNING, errno, __FUNCTION__, "Failed send to bc %s",
                 ip_to_str(dst));
            return;
        }
#endif
    }
    else
    {

#ifdef NS_PORT
#ifndef OMNETPP
        ch->addr_type() = NS_AF_INET;
        /* We trust the decision of next hop for all AODV messages... */
        if (dst.s_addr == AODV_BROADCAST)
            sendPacket(p, dst, 0.001 * Random::uniform());
        else
            sendPacket(p, dst, 0.0);
#else
        // IPv4Address   desAddIp4(dst.s_addr);
        // IPvXAddress destAdd(desAddIp4);
        ManetAddress destAdd;
        if (dst.s_addr == ManetAddress(IPv4Address(AODV_BROADCAST)))
        {
            destAdd = ManetAddress(IPv4Address::ALLONES_ADDRESS);
            if (delay>0)
            {
                if (useIndex)
                    sendToIp(aodv_msg, 654, destAdd, 654,ttl,delay,dev->ifindex);
                else
                    sendToIp(aodv_msg, 654, destAdd, 654,ttl,delay,dev->ipaddr.s_addr);
            }
            else
            {
                if (useIndex)
                    sendToIp(aodv_msg, 654, destAdd, 654,ttl,par("broadcastDelay").doubleValue(),dev->ifindex);
                else
                    sendToIp(aodv_msg, 654, destAdd, 654,ttl,par("broadcastDelay").doubleValue(),dev->ipaddr.s_addr);
            }
        }
        else
        {
            destAdd = dst.s_addr;
            if (delay>0)
            {
                if (useIndex)
                    sendToIp(aodv_msg, 654, destAdd, 654,ttl,delay,dev->ifindex);
                else
                    sendToIp(aodv_msg, 654, destAdd, 654,ttl,delay,dev->ipaddr.s_addr);
            }
            else
            {
                if (useIndex)
                    sendToIp(aodv_msg, 654, destAdd, 654,ttl,par("unicastDelay").doubleValue(),dev->ifindex);
                else
                    sendToIp(aodv_msg, 654, destAdd, 654,ttl,par("unicastDelay").doubleValue(),dev->ipaddr.s_addr);
            }
        }
        totalSend++;
#endif
#else
        retval = sendto(dev->sock, send_buf, len, 0,
                        (struct sockaddr *) &dst_addr, sizeof(dst_addr));

        if (retval < 0)
        {
            alog(LOG_WARNING, errno, __FUNCTION__, "Failed send to %s",
                 ip_to_str(dst));
            return;
        }
#endif
    }

    /* Do not print hello msgs... */
    if (!(aodv_msg->type == AODV_RREP && (dst.s_addr == ManetAddress(IPv4Address(AODV_BROADCAST)))))
        DEBUG(LOG_INFO, 0, "AODV msg to %s ttl=%d retval=%u size=%u",
              ip_to_str(dst), ttl, retval, len);

    return;
}




#ifndef OMNETPP
AODV_msg *NS_CLASS aodv_socket_new_msg(void)
{
    memset(send_buf, '\0', SEND_BUF_SIZE);
    return (AODV_msg *) (send_buf);
}

/* Copy an existing AODV message to the send buffer */
AODV_msg *NS_CLASS aodv_socket_queue_msg(AODV_msg * aodv_msg, int size)
{
    memcpy((char *) send_buf, aodv_msg, size);
    return (AODV_msg *) send_buf;
}
#endif

void aodv_socket_cleanup(void)
{
#ifndef NS_PORT
    int i;

    for (i = 0; i < MAX_NR_INTERFACES; i++)
    {
        if (!DEV_NR(i).enabled)
            continue;
        close(DEV_NR(i).sock);
    }
#endif              /* NS_PORT */
}

