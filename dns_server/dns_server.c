#include "dns.h"

typedef struct dns_param_s {
    int socket;
    struct sockaddr_in addr;
} dns_param_t;


static void dn_refine(char *dn) {
    int i = 0;
    while (dn[i]) {
        if (dn[i] == '\n' || i == MAX_DN - 1){
            dn[i] = 0;
            break;
        }
        i++;
    }
}

static void * dns_callback(void *param) {
    dns_param_t dns;
    char dn[MAX_DN] = {0};
    char addr[MAX_DN] = {0};
    int res;
    int i;
    struct hostent *hent;

    //printf("dns thread start!\n");
    memcpy(&dns, param, sizeof(dns_param_t));
    //res = recv(dns.socket, (void *)dn, MAX_DN - 1, 0);        
    res = readline(dns.socket, dn, MAX_DN);
    if (res <= 0) {
        printf("service stop in recv res=%d\n", res);
        goto exit;
    }

    dn_refine(dn);
    printf("Host name: %s\n", dn);
    
    hent = gethostbyname(dn);
    if (!hent) {
        herror("Fail to translate host name: ");
        goto exit;
    }
        
    for (i = 0; hent->h_addr_list[i] != NULL; i++) {
        sprintf(addr, "%s\n", inet_ntoa(*(struct in_addr *)hent->h_addr_list[i]));
        res = send(dns.socket, (void *)addr, strlen(addr), MSG_DONTWAIT);
        if (res < 0) {
            printf("Blocked result ip addr: %s\n", addr);
            perror("fail to send result to client:");
        }
    }
 
exit:
    close(dns.socket);
    return NULL;
}

int main(int argc, char **argv) {
    int server;
    int client;
    pthread_t thread;
    struct sockaddr_in srv_addr;
    dns_param_t param;
    int res;
    
    server = socket(AF_INET, SOCK_STREAM, 0);
    if (server < 0) {
        perror("Fail to creat socket");
        exit(1);
    }

    srv_addr.sin_family = AF_INET; 
    srv_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    srv_addr.sin_port = htons(SERVER_PORT); 
    memset(srv_addr.sin_zero, 0, sizeof(srv_addr.sin_zero));

    res = bind(server, (struct sockaddr *)&srv_addr, sizeof(struct sockaddr));
    if (res < 0) {
        perror("Failt to bind socket to local host:");
        close(server);
        exit(1);        
    }

    printf("DNS Monitor started...\n");
    listen(server, 10);
    
    while (1) {
        int len = sizeof(param.addr);
        //printf("waiting for connection!\n");
        client = accept(server, (struct sockaddr *) &param.addr, &len);
        if (client < 0) {
            perror("Fail to accept connection: ");
            break;
        }
        //printf("processing a new connection!\n");
        param.socket = client;
        pthread_create(&thread, 0, (void *)&dns_callback, (void *)&param);        
    }

    close(server);
    return 0;
}
