#include <stdio.h>
#include <stdlib.h>
#include<errno.h>


#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netdb.h>

#include <linux/if_packet.h>
#include <net/ethernet.h>

#include <arpa/inet.h>
#include <netinet/in.h>


//http://www.binarytides.com/packet-sniffer-code-in-c-using-linux-sockets-bsd-part-2/



int main()
{



    int sock_raw = socket( AF_PACKET, SOCK_RAW, htons(ETH_P_ALL)) ;

    if(sock_raw < 0)
    {
        //Print the error with proper message
        perror("Socket Error");
        return 1;
    }





}


