#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <linux/if_ether.h>
#include <linux/in.h>
#define BUFFER_MAX 2048

int main(int argc, const char *argv[])
{
    int sock, n_read, proto;
    char buffer[BUFFER_MAX];
    char *ethhead, *iphead, *tcphead, *udphead, *icmphead, *p;
    if ((sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_IP))) < 0) {
        perror("socket(AF_PACKET, SOCK_RAW, htons(ETH_P_IP))");
        exit(1);
    }
    while (1) {
        n_read = recvfrom(sock, buffer, BUFFER_MAX, 0, NULL, NULL);
        /*
         * 14 6(dest) + 6(src) + 2(type or len)
         * +
         * 20 ip header
         * +
         * 8 icmp,tcp or udp header
         * =
         * 42
         */
        if (n_read < 42) {
            fprintf(stderr, "Incomplete header, packet corrupt\n");
            continue;
        }
        ethhead = buffer;
        p = ethhead;
        int n = 0xff;
        printf("MAC: %.2X:%02X:%02X:%02X:%02X:%02X ==>"
                    "%.2X:%02X:%02X:%02X:%02X:%02X\n",
                   p[6]&n, p[7]&n, p[8]&n, p[9]&n, p[10]&n, p[11]&n,
                   p[0]&n, p[1]&n, p[2]&n, p[3]&n, p[4]&n, p[5]&n);
        iphead = ethhead + 14;
        p = iphead + 12;
        printf("IP: %d.%d.%d.%d => %d.%d.%d.%d\n",
                p[0]&n, p[1]&n, p[2]&n, p[3]&n,
                p[4]&n, p[5]&n, p[6]&n, p[7]&n);
        proto = (iphead + 9)[0];
        p = iphead + 20;
        printf("Protocol: ");
        switch (proto)
        {
            case IPPROTO_ICMP:
                printf("ICMP\n"); break;
            case IPPROTO_IGMP:
                printf("IGMP\n"); break;
            case IPPROTO_IPIP:
                printf("IPIP\n"); break;
            case IPPROTO_TCP:
            case IPPROTO_UDP:
                printf("%s,", proto == IPPROTO_TCP?"TCP":"UDP");
                printf("src port: %u,", (p[0] << 8)&0xff00 | p[1]&0xff);
                printf("dest port: %u\n", (p[2] << 8)&0xff00 | p[3]&0xff);
                break;

            case IPPROTO_RAW:
                printf("RAW\n"); break;
            default:
                printf("Unknown, please query in include/linux/in.h\n");

        }
    }
    return 0;
}
