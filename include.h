
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#define WIN32_LEAN_AND_MEAN

#define DEFAULT_BUFLEN 1024
//#define PORT 3000
#define SA struct sockaddr
#define MAX 80

extern void init_server();
extern void server_handler();

extern void init_client();
extern void client_handler();

void func(int connfd);
