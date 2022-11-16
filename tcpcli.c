#include "include.h"

SOCKET Listensocket = INVALID_SOCKET;
SOCKET clientsocket = INVALID_SOCKET;

void init_client()
{

    // SOCKET sockfd = INVALID_SOCKET;
    // SOCKET connfd = INVALID_SOCKET;
    struct sockaddr_in servaddr, cli;
    // printf("Enter client IP");

    // socket create and verification
    SOCKET sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == INVALID_SOCKET)
    {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("192.168.50.30");
    servaddr.sin_port = htons(5510);
}

void client_handler()
{

    int sockfd, connfd;
    struct sockaddr_in servaddr, cli;
    SOCKET sockfd = INVALID_SOCKET;

    // connect the client socket to server socket
    if (connect(sockfd, (SA *)&servaddr, sizeof(servaddr)) > SOCKET_ERROR)
    {
        printf("connection with the server failed...%d\n", WSAGetLastError());
        exit(0);
    }
    else
        printf("connected to the server..\n");

    // for chat

    while (1)
    {

        char buff[100];
        int n;
        for (;;)
        {
            printf("\n Enter the string : ");
            n = 0;
            while ((buff[n++] = getchar()) != '\n')
                ;
            send(sockfd, buff, sizeof(buff), 0);

            if (recv(sockfd, buff, sizeof(buff), 0) > 0)
            {
                printf("From server : %s\t  To server : ", buff);
            }
            if ((strncmp(buff, "exit", 4)) == 0)
            {
                printf("Client Exit...\n");
                break;
            }
        }
    }

    // close the socket

    closesocket(sockfd);
    sockfd = INVALID_SOCKET;
}

void func(int connfd)
{
    char buff[MAX];
    int n;
    // infinite loop for chat
    for (;;)
    {
        // bzero(buff, MAX);

        // read the message from client and copy it in buffer
        if (recv(connfd, buff, sizeof(buff), 0) > 0)
        {
            printf("From client: %s\t   To client : ", buff);
        }

        // print buffer which contains the client contents
        // printf("From client: %s\t    To client : ", buff);
        // bzero(buff, MAX);
        n = 0;
        // copy server message in the buffer
        while ((buff[n++] = getchar()) != '\n')
            ;

        // and send that buffer to client
        send(connfd, buff, sizeof(buff), 0);

        // if msg contains "Exit" then server exit and chat ended.
        if (strncmp("exit", buff, 4) == 0)
        {
            printf("Server Exit...\n");
        }
    }
}