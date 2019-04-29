#include "sniffer.h"

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

    for (int i = 0; i < CLIENT_SEND_COUNT; ++i) {
        printf("Sending message %d of %d. Result: ", i + 1, CLIENT_SEND_COUNT);

        memset(buf, 0, sizeof(buf));
        snprintf(buf, sizeof(buf) - 1, "DATA %d", i);

        if (send(client_fd, &buf, strlen(buf), 0) == -1) {
            perror("send");
            return 6;
        }

        memset(buf, 0, sizeof(buf));

        if (recv(client_fd, &buf, sizeof(buf), 0) == -1) {
            perror("recv");
            return 7;
        }

        printf("%s\n", buf);
    }

    printf("Closing...\n");
    if (close(client_fd) == -1) {
        perror("close");
        return 8;
    }

    return 0;
}
