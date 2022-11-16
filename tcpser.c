#include "include.h"

SOCKET sockfd = INVALID_SOCKET;
SOCKET connfd = INVALID_SOCKET;
struct sockaddr_in servaddr, cli;

void init_server()
{
    int iResult;
    // int sockfd;
    // struct sockaddr_in servaddr, cli;
    //  printf("Enter server IP");

    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == INVALID_SOCKET)
    {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");

    memset(&servaddr, sizeof(servaddr), 0);
    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("192.168.50.30");
    servaddr.sin_port = htons(5510);

    // Binding newly created socket to given IP and verification
    iResult = bind(sockfd, (SA *)&servaddr, sizeof(servaddr));
    if (iResult == SOCKET_ERROR)
    {
        printf("bind failed with error: %d\n", WSAGetLastError());
        exit(0);
    }
    else
        printf("Socket successfully binded..\n");

    // Now server is ready to listen and verification
    if (listen(sockfd, 5) == SOCKET_ERROR)
    {
        printf("Listen failed...\n");
        exit(0);
    }
    else
        printf("Server listening..\n");
}
void server_handler()
{

    int iResult, len1;

    // struct sockaddr_in servaddr,cli;
    // SOCKET sockfd = INVALID_SOCKET;
    // SOCKET confd = INVALID_SOCKET;

    if (connfd == INVALID_SOCKET)
    {
        len1 = sizeof(cli);

        // Accept the data packet from client and verification
        connfd = accept(sockfd, (SA *)&cli, &len1);
        if (connfd == INVALID_SOCKET)
        {
            printf("server accept failed...%d\n", WSAGetLastError());
            exit(0);
        }
        else
            printf("server accept the client...\n");
    }
    else
    {
        // Function for chatting between client and server
        char buff[100];
        int n;
        if (recv(connfd, buff, sizeof(buff), 0) > 0)
        {
            printf("From client: %s\t  To client : ", buff);
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
}