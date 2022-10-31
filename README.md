# CHATBOX.C
TCP CLIENT SERVER COMMUNICATION


#include "include.h"

int main()
{

    WSADATA wsaData;
    SOCKET ConnectSocket = INVALID_SOCKET;

    const char *sendbuf = "this is a test";
    char recvbuf[DEFAULT_BUFLEN];
    int iResult;
    int recvbuflen = DEFAULT_BUFLEN;

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0)
    {
        printf("WSAStartup failed with error: %d\n", iResult);
        return 1;
    }
    init_server();
    //init_client();
    while (1)
    {
        //client_handler();
        server_handler();
    }
}
