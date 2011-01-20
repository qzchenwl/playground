#include <linux/if_tun.h>
#include <stdlib.h>
#include <net/if.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <assert.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <linux/if_ether.h>
#include <linux/in.h>

int tun_create(char *dev, int flags)
{
    struct ifreq ifr;
    int fd, err;

    assert(dev != NULL);

    if ((fd = open("/dev/net/tun", O_RDWR)) < 0)
        return fd;

    memset(&ifr, 0, sizeof(ifr));
    ifr.ifr_flags |= flags;
    if (*dev != '\0')
        strncpy(ifr.ifr_name, dev, IFNAMSIZ);
    if ((err = ioctl(fd, TUNSETIFF, (void*)&ifr)) < 0) {
        close(fd);
        return err;
    }
    strcpy(dev, ifr.ifr_name);
    return fd;
}

int main(int argc, const char *argv[])
{
    int tun, ret;
    char tun_name[IFNAMSIZ];
    unsigned char buf[4096];
    char ip[4];
    int sock;
    int flag = 1;
    if ((sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) < 0) {
        perror("socket()");
        exit(1);
    }
    ret = setsockopt(sock, IPPROTO_IP, IP_HDRINCL, &flag, sizeof(int));
    if (ret == -1) {
        perror("setsockopt()");
        exit(1);
    }

    //tun_name[0] = '\0';
    strncpy(tun_name, "tun123", sizeof("tun123"));
    tun = tun_create(tun_name, IFF_TUN|IFF_NO_PI);
    if (tun < 0) {
        perror("tun_create");
        return 1;
    }
    printf("TUN name is %s\n", tun_name);

    while (1) {
        unsigned char ip[4];

        ret = read(tun, buf, sizeof(buf));
        if (ret < 0)
            break;
        /*
        memcpy(ip, &buf[12], 4);
        memcpy(&buf[12], &buf[16], 4);
        memcpy(&buf[16], ip, 4);
        buf[16] = 8;
        buf[17] = 8;
        buf[18] = 8;
        buf[19] = 8;
        buf[20] = 0;
        */

        *((unsigned short *)&buf[22]) += 8;
        printf("read %d bytes\n", ret);
        /*
        ret = write(tun, buf, ret);
        */
        sendto(sock, buf, ret, 0, NULL, 0);
        printf("write %d bytes\n", ret);
        ret = recvfrom(sock, buf, 4096, 0, NULL, NULL);
        printf("recv %d bytes\n", ret);
    }
    return 0;
}
