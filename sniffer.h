#ifndef _SNIFFER_H_
#define _SNIFFER_H_
//#include "common.h"

#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>		//for close()
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/sctp.h>
#include <arpa/inet.h>	//for inet_ntop()

#define SERVER_PORT 36412
#define ADDR_FAMILY AF_INET
#define SOCK_TYPE SOCK_STREAM
#define PROTO IPPROTO_SCTP
#define CLIENT_SEND_COUNT 5
#define SERVER_LISTEN_QUEUE_SIZE 10

typedef struct _client_data {
    int socket_fd;
    struct sockaddr addr;
} client_data_t;

int sniffer_server();
int sniffer_client(char *, char *);
void *handle_connection(void *thread_data);

#endif
