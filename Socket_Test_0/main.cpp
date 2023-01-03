#include "main.h"

//#define SERVER_CODE


#ifndef SERVER_CODE
void main()
{
	WSADATA wsa;

	// 소켓 초기화, 윈도우에 문제 있지 않는 한 실패하는 경우는 거의 없음.
	// MAKEWORD(2, 2): 윈도우 소켓 2.2 버전
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) 
	{
		return;
	}

	// 소켓을 꼭 만들어야 사용 가능하다.
	// AF_INET: IP를 뜻함.
	// SOCKET sockTCP = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); // SOCK_STREAM: TCP.
	// SOCKET sockUDP = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); // SOCK_DGRAM: UDP
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0); // TCP는 STREAM으로 고정이기 때문에 프로토콜에 0을 넣어줘도 된다.
	u_long Mode = TRUE; // TRUE: 논 블록형 함수, FALSE: 블록형 함수. (블록형 함수, 접속하거나 받거나 해야 반환이 됨.)
	ioctlsocket(sock, FIONBIO, &Mode); // 
	
	// Client에서 Host로 연결 할 때
	// 목적지 + 포트 번호가 필요.
	SOCKADDR_IN sa; 
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = inet_addr("192.168.0.12");//inet_pton(0, "192.168.0.12", NULL); // 문자열을 long 값으로 바꿔 줌.
	// htons: Host Short To Network, htonl: Host Long To Network. 
	// 네트워크에서는 빅 엔디안을 사용. 네트워크 사용하지 않는 곳은 다 리틀엔디안 사용함. 교재 p39 참조.
	// Ex) 0x12345678 저장.
	// 빅 엔디안 저장 방식:  0x12, 0x34, 0x56, 0x78 
	// 리틀 엔디안 저장 방식: 0x78, 0x56, 0x34, 0x12
	// 만약 우리가 빅 엔디안으로 바꾸지 않고 10000번 포트에 접속하려고 넣으면, 4135 포트에 접속하게됨.
	// 서버에 접속 할 때는 호스트의 포트가 필요하지만, 호스트에 접속하면 자동으로 TCP헤더가 붙어 클라이언트의 포트번호를 알 수 있다. 
	sa.sin_port = htons(10000); 
	
	int rst = connect(sock, (sockaddr*)&sa, sizeof(sa)); // 연결할 소켓, 목적지 + 포트, 길이.
	if (rst == SOCKET_ERROR)
	{
		return;
	}

	// Data 보내기.
	char SendMsgBuffer[256] = { 0, };
	fgets(SendMsgBuffer, 256, stdin);
	int SendBytes = send(sock, SendMsgBuffer, strlen(SendMsgBuffer), 0);

	// Data 받기
	char RecvMsgBuffer[256] = { 0, };
	recv(sock, RecvMsgBuffer, 256, 0);
	std::cout << "Recv: " << RecvMsgBuffer << std::endl;

	// 만든 소켓 닫기.
	closesocket(sock);

	// 소켓 클리어.
	WSACleanup(); 
}

#else
void main()
{
	WSADATA wsa;

	// 소켓 초기화, 윈도우에 문제 있지 않는 한 실패하는 경우는 거의 없음.
	// MAKEWORD(2, 2): 윈도우 소켓 2.2 버전
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		return;
	}

	// 소켓을 꼭 만들어야 사용 가능하다.
	// AF_INET: IP를 뜻함.
	// SOCKET sockTCP = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); // SOCK_STREAM: TCP.
	// SOCKET sockUDP = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); // SOCK_DGRAM: UDP
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0); // TCP는 STREAM으로 고정이기 때문에 프로토콜에 0을 넣어줘도 된다.

	// Client에서 Host로 연결 할 때
	// 목적지 + 포트 번호가 필요.
	SOCKADDR_IN sa;
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = htonl(INADDR_ANY); //inet_pton(0, "192.168.0.12", NULL); // 문자열을 long 값으로 바꿔 줌.
	// htons: Host Short To Network, htonl: Host Long To Network. 
	// 네트워크에서는 빅 엔디안을 사용. 네트워크 사용하지 않는 곳은 다 리틀엔디안 사용함. 교재 p39 참조.
	// Ex) 0x12345678 저장.
	// 빅 엔디안 저장 방식:  0x12, 0x34, 0x56, 0x78 
	// 리틀 엔디안 저장 방식: 0x78, 0x56, 0x34, 0x12
	// 만약 우리가 빅 엔디안으로 바꾸지 않고 10000번 포트에 접속하려고 넣으면, 4135 포트에 접속하게됨.
	// 서버에 접속 할 때는 호스트의 포트가 필요하지만, 호스트에 접속하면 자동으로 TCP헤더가 붙어 클라이언트의 포트번호를 알 수 있다. 
	sa.sin_port = htons(10000);

	// 서버를 바인딩 해줘야 함.
	int rst = bind(sock, (sockaddr*)&sa, sizeof(sa));
	if (rst == SOCKET_ERROR)
	{
		return;
	}

	// 데이터를 받을 준비가 되었다.
	rst = listen(sock, SOMAXCONN); 
	if (rst == SOCKET_ERROR)
	{
		return;
	}

	// 누군가 접속 하면 반환 된다.
	SOCKADDR_IN ClientAddr;
	int ClientLength = sizeof(ClientAddr);
	SOCKET ClientSocket = accept(sock, (sockaddr*)&ClientAddr, &ClientLength);
	std::cout << "Client Connect - IP: " << inet_ntoa(ClientAddr.sin_addr) << ", Port: " << htons(ClientAddr.sin_port) << std::endl;
	
	// Data 보내기.
	char SendMsgBuffer[256] = { 0, };
	fgets(SendMsgBuffer, 256, stdin);
	int SendBytes = send(sock, SendMsgBuffer, strlen(SendMsgBuffer), 0);

	// Data 받기
	char RecvMsgBuffer[256] = { 0, };
	recv(sock, RecvMsgBuffer, 256, 0); // 블록킹 함수: 조건을 만족해야만, 실행 되는 함수.

	// 만든 소켓 닫기.
	closesocket(sock);

	// 소켓 클리어.
	WSACleanup();
}
#endif