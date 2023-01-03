#include "main.h"

//#define SERVER_CODE


#ifndef SERVER_CODE
void main()
{
	WSADATA wsa;

	// ���� �ʱ�ȭ, �����쿡 ���� ���� �ʴ� �� �����ϴ� ���� ���� ����.
	// MAKEWORD(2, 2): ������ ���� 2.2 ����
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) 
	{
		return;
	}

	// ������ �� ������ ��� �����ϴ�.
	// AF_INET: IP�� ����.
	// SOCKET sockTCP = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); // SOCK_STREAM: TCP.
	// SOCKET sockUDP = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); // SOCK_DGRAM: UDP
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0); // TCP�� STREAM���� �����̱� ������ �������ݿ� 0�� �־��൵ �ȴ�.
	u_long Mode = TRUE; // TRUE: �� ����� �Լ�, FALSE: ����� �Լ�. (����� �Լ�, �����ϰų� �ްų� �ؾ� ��ȯ�� ��.)
	ioctlsocket(sock, FIONBIO, &Mode); // 
	
	// Client���� Host�� ���� �� ��
	// ������ + ��Ʈ ��ȣ�� �ʿ�.
	SOCKADDR_IN sa; 
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = inet_addr("192.168.0.12");//inet_pton(0, "192.168.0.12", NULL); // ���ڿ��� long ������ �ٲ� ��.
	// htons: Host Short To Network, htonl: Host Long To Network. 
	// ��Ʈ��ũ������ �� ������� ���. ��Ʈ��ũ ������� �ʴ� ���� �� ��Ʋ����� �����. ���� p39 ����.
	// Ex) 0x12345678 ����.
	// �� ����� ���� ���:  0x12, 0x34, 0x56, 0x78 
	// ��Ʋ ����� ���� ���: 0x78, 0x56, 0x34, 0x12
	// ���� �츮�� �� ��������� �ٲ��� �ʰ� 10000�� ��Ʈ�� �����Ϸ��� ������, 4135 ��Ʈ�� �����ϰԵ�.
	// ������ ���� �� ���� ȣ��Ʈ�� ��Ʈ�� �ʿ�������, ȣ��Ʈ�� �����ϸ� �ڵ����� TCP����� �پ� Ŭ���̾�Ʈ�� ��Ʈ��ȣ�� �� �� �ִ�. 
	sa.sin_port = htons(10000); 
	
	int rst = connect(sock, (sockaddr*)&sa, sizeof(sa)); // ������ ����, ������ + ��Ʈ, ����.
	if (rst == SOCKET_ERROR)
	{
		return;
	}

	// Data ������.
	char SendMsgBuffer[256] = { 0, };
	fgets(SendMsgBuffer, 256, stdin);
	int SendBytes = send(sock, SendMsgBuffer, strlen(SendMsgBuffer), 0);

	// Data �ޱ�
	char RecvMsgBuffer[256] = { 0, };
	recv(sock, RecvMsgBuffer, 256, 0);
	std::cout << "Recv: " << RecvMsgBuffer << std::endl;

	// ���� ���� �ݱ�.
	closesocket(sock);

	// ���� Ŭ����.
	WSACleanup(); 
}

#else
void main()
{
	WSADATA wsa;

	// ���� �ʱ�ȭ, �����쿡 ���� ���� �ʴ� �� �����ϴ� ���� ���� ����.
	// MAKEWORD(2, 2): ������ ���� 2.2 ����
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		return;
	}

	// ������ �� ������ ��� �����ϴ�.
	// AF_INET: IP�� ����.
	// SOCKET sockTCP = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); // SOCK_STREAM: TCP.
	// SOCKET sockUDP = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); // SOCK_DGRAM: UDP
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0); // TCP�� STREAM���� �����̱� ������ �������ݿ� 0�� �־��൵ �ȴ�.

	// Client���� Host�� ���� �� ��
	// ������ + ��Ʈ ��ȣ�� �ʿ�.
	SOCKADDR_IN sa;
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = htonl(INADDR_ANY); //inet_pton(0, "192.168.0.12", NULL); // ���ڿ��� long ������ �ٲ� ��.
	// htons: Host Short To Network, htonl: Host Long To Network. 
	// ��Ʈ��ũ������ �� ������� ���. ��Ʈ��ũ ������� �ʴ� ���� �� ��Ʋ����� �����. ���� p39 ����.
	// Ex) 0x12345678 ����.
	// �� ����� ���� ���:  0x12, 0x34, 0x56, 0x78 
	// ��Ʋ ����� ���� ���: 0x78, 0x56, 0x34, 0x12
	// ���� �츮�� �� ��������� �ٲ��� �ʰ� 10000�� ��Ʈ�� �����Ϸ��� ������, 4135 ��Ʈ�� �����ϰԵ�.
	// ������ ���� �� ���� ȣ��Ʈ�� ��Ʈ�� �ʿ�������, ȣ��Ʈ�� �����ϸ� �ڵ����� TCP����� �پ� Ŭ���̾�Ʈ�� ��Ʈ��ȣ�� �� �� �ִ�. 
	sa.sin_port = htons(10000);

	// ������ ���ε� ����� ��.
	int rst = bind(sock, (sockaddr*)&sa, sizeof(sa));
	if (rst == SOCKET_ERROR)
	{
		return;
	}

	// �����͸� ���� �غ� �Ǿ���.
	rst = listen(sock, SOMAXCONN); 
	if (rst == SOCKET_ERROR)
	{
		return;
	}

	// ������ ���� �ϸ� ��ȯ �ȴ�.
	SOCKADDR_IN ClientAddr;
	int ClientLength = sizeof(ClientAddr);
	SOCKET ClientSocket = accept(sock, (sockaddr*)&ClientAddr, &ClientLength);
	std::cout << "Client Connect - IP: " << inet_ntoa(ClientAddr.sin_addr) << ", Port: " << htons(ClientAddr.sin_port) << std::endl;
	
	// Data ������.
	char SendMsgBuffer[256] = { 0, };
	fgets(SendMsgBuffer, 256, stdin);
	int SendBytes = send(sock, SendMsgBuffer, strlen(SendMsgBuffer), 0);

	// Data �ޱ�
	char RecvMsgBuffer[256] = { 0, };
	recv(sock, RecvMsgBuffer, 256, 0); // ���ŷ �Լ�: ������ �����ؾ߸�, ���� �Ǵ� �Լ�.

	// ���� ���� �ݱ�.
	closesocket(sock);

	// ���� Ŭ����.
	WSACleanup();
}
#endif