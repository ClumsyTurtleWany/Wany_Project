#include "main.h"

#define SERVER_CODE
#ifndef SERVER_CODE
int main()
{
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        return 0;
    }

    //SOCKET sock1 = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    //SOCKET sock2 = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    // ����� ���� <-> �ͺ���� ����
    SOCKET sock3 = socket(AF_INET, SOCK_STREAM, 0);



    short sData = 10000;
    short tData = 0x2710;
    short fData = 0x1027;

    // client
    SOCKADDR_IN sa;//������+��Ʈ
    sa.sin_family = AF_INET;
    //error C4996: 'inet_addr': Use inet_pton() or InetPton() instead or define _WINSOCK_DEPRECATED_NO_WARNINGS to disable deprecated API warnings
    sa.sin_addr.s_addr = inet_addr("192.168.0.12");
    sa.sin_port = htons(10000);
    int iRet = connect(sock3, (sockaddr*)&sa, sizeof(sa));
    if (iRet == SOCKET_ERROR)
    {
        int iError = WSAGetLastError();
        printf("%d ", iError);
        return 1;
    }

    u_long iMode = TRUE;
    ioctlsocket(sock3, FIONBIO, &iMode);
    //char szSendMsg[256] = "kgca";// { 0, };
    //printf("%s", "send---->");
    while (1)
    {
        //***********����� �Լ��� ���� ****************/
        //Sleep(100);
        char szSendMsg[256] = { 0, };
        printf("%s", "send---->");
        fgets(szSendMsg, 256, stdin);

        int iSendBytes = send(sock3, szSendMsg, strlen(szSendMsg), 0);
        if (iSendBytes == SOCKET_ERROR)
        {
            if (WSAGetLastError() != WSAEWOULDBLOCK)
            {
                //WSAEWOULDBLOCK �ƴ϶�� ����!
                closesocket(sock3);
                return 1;
            }
            continue;
        }

        char szRecvMsg[256] = { 0, };
        int iRecvBytes = recv(sock3, szRecvMsg, 256, 0);
        if (iRecvBytes == SOCKET_ERROR)
        {
            if (WSAGetLastError() != WSAEWOULDBLOCK)
            {
                //WSAEWOULDBLOCK �ƴ϶�� ����!
                closesocket(sock3);
                return 1;
            }
            continue;
        }
        printf("Recv---->%s\n", szRecvMsg);
    }

    closesocket(sock3);
    WSACleanup();
    std::cout << "Hello World!\n";
}
#else
int main()
{
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        return 0;
    }

    //SOCKET sock1 = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    //SOCKET sock2 = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    SOCKET sock3 = socket(AF_INET, SOCK_STREAM, 0);
    short sData = 10000;
    short tData = 0x2710;
    short fData = 0x1027;

    // client
    SOCKADDR_IN sa;//������+��Ʈ
    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = htonl(INADDR_ANY);
    sa.sin_port = htons(10000);
    int iRet = bind(sock3, (sockaddr*)&sa, sizeof(sa));
    if (iRet == SOCKET_ERROR)
    {
        return 1;
    }
    iRet = listen(sock3, SOMAXCONN);
    if (iRet == SOCKET_ERROR)
    {
        return 1;
    }

    // ���ӵǸ� ��ȯ�ȴ�.
    SOCKADDR_IN clientaddr;
    int length = sizeof(clientaddr);
    SOCKET clientSock = accept(sock3, (sockaddr*)&clientaddr, &length);
    if (clientSock == SOCKET_ERROR)
    {
        closesocket(sock3);
        WSACleanup();
        return 1;
    }
    printf("Ŭ���̾�Ʈ ���� : IP:%s, PORT:%d\n",
        inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

    u_long iMode = TRUE;
    ioctlsocket(clientSock, FIONBIO, &iMode);

    while (1)
    {
        char szRecvMsg[256] = { 0, };
        int iRecvBytes = recv(clientSock, szRecvMsg, 256, 0);
        if (iRecvBytes == 0)
        {
            printf("Ŭ���̾�Ʈ ���� ���� : IP:%s, PORT:%d\n",
                inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));
            closesocket(clientSock);
            break;
        }
        if (iRecvBytes == SOCKET_ERROR)
        {
            if (WSAGetLastError() != WSAEWOULDBLOCK)
            {
                //WSAEWOULDBLOCK �ƴ϶�� ����!
                closesocket(sock3);
                return 1;
            }
        }
        else
        {
            printf("%s\n", szRecvMsg);
        }

        if (iRecvBytes > 0)
        {
            int iSendBytes = send(clientSock, szRecvMsg, strlen(szRecvMsg), 0);
            if (iSendBytes == SOCKET_ERROR)
            {
                if (WSAGetLastError() != WSAEWOULDBLOCK)
                {
                    //WSAEWOULDBLOCK �ƴ϶�� ����!
                    closesocket(clientSock);
                    break;
                }
            }
        }
    }
    closesocket(clientSock);

    WSACleanup();
    std::cout << "Hello World!\n";
}
#endif
