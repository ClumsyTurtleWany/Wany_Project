#pragma once

#pragma pack(push, 1) // 1바이트 팩킹으로 전송한다.
typedef struct PACKET_HEADER
{
	short lenght;
	short type;
};

//typedef struct PACKET_HEADER
//{
//	short lenght;
//  int   a;
//	short type;
//};
// 원래 이런식으로 작업하게되면 가장 큰 인트 기준으로 하여 12바이트의 구조체가 생성됨.
// #pragma pack(push, 데이터사이즈) 로 원하는 크기단위로 팩킹하면 딱 8바이트로 생성 가능함.

#pragma pack(pop)
