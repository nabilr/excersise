#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>




struct udp_packet_hdr {

    short src_prt ;
    short dest_port;

    short length;
    short cksum;

    char payload[0];

};

int main()
{
    struct udp_packet_hdr  two_pckt[2];

    printf("you machine is %d bit arch   aaaa\n", sizeof(void *) * 8);
    printf("size of udp header %d", sizeof(two_pckt));


    int socket(int domain, int type, int protocol);




    return 0;
}
