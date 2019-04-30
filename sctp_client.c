#include "sniffer.h"

#ifdef client
int main() {
    char buf[1024];
    sniffer_client("127.0.0.1", buf);
    return 0;
}
#endif

int sniffer_client(char* ip_char, char* buf) {
    int client_fd = 0;
    const char* server_ip = NULL;
    int server_port = SERVER_PORT;

    server_ip = ip_char;

    if ((client_fd = socket(ADDR_FAMILY, SOCK_TYPE, PROTO)) == -1) {
        perror("socket");
        return 3;
    }

    struct sockaddr_in peer_addr;
    memset(&peer_addr, 0, sizeof(struct sockaddr_in));
    peer_addr.sin_family = ADDR_FAMILY;
    peer_addr.sin_port = htons(server_port);
    if (inet_pton(AF_INET, server_ip, &(peer_addr.sin_addr)) != 1) {
        printf("Error converting IP address (%s) to sockaddr_in structure\n",
               server_ip);
        return 4;
    }

    printf("Connecting...\n");

    if (connect(client_fd, (struct sockaddr*)&peer_addr, sizeof(peer_addr)) ==
        -1) {
        perror("connect");
        return 5;
    }

    printf("OK\n");

    size_t i;
    for (i = 0; i < CLIENT_SEND_COUNT; ++i) {
        printf("Sending message %ld of %d. Result: ", i + 1, CLIENT_SEND_COUNT);

        char buff[1024];
        memcpy(buff, buf, sizeof(buff));
        memset(buff, 0, sizeof(buff));
        snprintf(buff, sizeof(buff) - 1, "DATA %ld", i);

        if (send(client_fd, &buff, strlen(buff), 0) == -1) {
            perror("send");
            return 6;
        }

        memset(buff, 0, sizeof(buff));

        if (recv(client_fd, &buff, sizeof(buff), 0) == -1) {
            perror("recv");
            return 7;
        }

        printf("%s\n", buff);
    }

    printf("Closing...\n");
    if (close(client_fd) == -1) {
        perror("close");
        return 8;
    }

    return 0;
}
