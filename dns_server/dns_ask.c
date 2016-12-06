#include "dns.h"

int main(int argc, char **argv) {
    int fd;
    int res;
    char ip[MAX_DN] = {0};
    struct sockaddr_in addr;

    if (argc != 2 || argv[1] == NULL) {
        printf("Please input the host name.\n");
        exit(1);
    }

    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        perror("Fail to create socket:");
        exit(1);
    }

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    addr.sin_port = htons(SERVER_PORT);
    memset(addr.sin_zero, 0, sizeof(addr.sin_zero));

    res = connect(fd, (struct sockaddr *)&addr, sizeof(struct sockaddr));
    if (res != 0) {
        perror("Fail to connnect dns server:");
        close(fd);
        exit(1);
    }
    //printf("DNS Server is connected, ask ip addr for host<%s>\n", argv[1]);

    res = send(fd, argv[1], strlen(argv[1]), 0);
    if (res < 0) {
        perror("Fail to send host name:");
        close(fd);
        exit(1);
    }
    send(fd, "\n", 1, 0);

    res = readline(fd, ip, MAX_DN);
    if (res < 0) {        
        printf("Fail to get response from dns server\n");
    }
    else {
        printf("DNSed IP Address: %s\n", ip);
    }

    close(fd);
    return 0;
}

