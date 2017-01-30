#include <stdio.h>
#include <stdlib.h>
#include<errno.h>
#include <unistd.h>



#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netdb.h>


#include <netinet/ether.h>
#include<netinet/ip.h>


#include <netdb.h>  // getprotobynumber


#include <arpa/inet.h>
#include <netinet/in.h>


//http://www.binarytides.com/packet-sniffer-code-in-c-using-linux-sockets-bsd-part-2/


#define BUFFER_SIZE 1000

void print_ethernet_hdr(struct ethhdr *eth)
{

    printf("Destination Address : %.2X-%.2X-%.2X-%.2X-%.2X-%.2X \n", eth->h_dest[0] , eth->h_dest[1] , eth->h_dest[2] , eth->h_dest[3] , eth->h_dest[4] , eth->h_dest[5] );
    printf("Source Address      : %.2X-%.2X-%.2X-%.2X-%.2X-%.2X \n", eth->h_source[0] , eth->h_source[1] , eth->h_source[2] , eth->h_source[3] , eth->h_source[4] , eth->h_source[5] );
}

void print_ip_header(struct iphdr *iph)
{
        struct sockaddr_in source,dest;
        //http://alas.matf.bg.ac.rs/manuals/lspe/snode=61.html
        //struct protoent *getprotobynumber(int proto);
        struct protoent *pent;
        pent = getprotobynumber(iph->protocol);
        if(pent == NULL)
        {
            printf("protocol by number %d\n", iph->protocol);
            return;

        } else {

            printf("protocol by name %s\n", pent->p_name);
        }

        memset(&source, 0, sizeof(source));
        source.sin_addr.s_addr = iph->saddr;

        memset(&dest, 0, sizeof(dest));
        dest.sin_addr.s_addr = iph->daddr;
        printf("Source IP        : %x\n",source.sin_addr.s_addr);
        printf("Destination IP   : %x\n",dest.sin_addr.s_addr);

        //Done forget add required header fro inet_ntoa
        printf("Source IP        : %s\n",inet_ntoa(source.sin_addr));
        printf("Destination IP   : %s\n",inet_ntoa(dest.sin_addr));
        printf("\n\n\n");



}

int main()
{

    char buffer[BUFFER_SIZE];
    int len = 0;

    struct ethhdr *eth = (struct ethhdr *)buffer;
    struct iphdr *iph = (struct iphdr *)(buffer + sizeof(struct ethhdr));
    //http://man7.org/linux/man-pages/man7/packet.7.html

    int sock_raw = socket( AF_PACKET, SOCK_RAW, htons(ETH_P_ALL)) ;

    if(sock_raw < 0)
    {
        //Print the error with proper message
        perror("Socket Error");
        return 1;
    }

    while(1)
    {
        len = read(sock_raw, buffer, BUFFER_SIZE);

        print_ethernet_hdr(eth);
        print_ip_header(iph);




    }




}



