#ifndef PACKET_H_INCLUDED
#define PACKET_H_INCLUDED


struct udp_packet_hdr
{

    short src_prt ;
    short dest_port;

    short length;
    short cksum;

    char payload[0];
};

#endif // PACKET_H_INCLUDED
