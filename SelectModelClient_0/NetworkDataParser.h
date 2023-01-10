#pragma once
#include <functional>
#include <map>

#pragma pack(push, 1) // 1����Ʈ ��ŷ���� �����Ѵ�.
typedef struct PACKET_HEADER
{
	short lenght;
	short type;
};

typedef struct PACKET
{
	PACKET_HEADER ph;
	char msg[2048];
};

//typedef struct PACKET_HEADER
//{
//	short lenght;
//  int   a;
//	short type;
//};
// ���� �̷������� �۾��ϰԵǸ� ���� ū ��Ʈ �������� �Ͽ� 12����Ʈ�� ����ü�� ������.
// #pragma pack(push, �����ͻ�����) �� ���ϴ� ũ������� ��ŷ�ϸ� �� 8����Ʈ�� ���� ������.
#pragma pack(pop)


enum class NetworkCommand
{
	CMD_HOST_REQ_LOGIN = 1,
	CMD_CLIENT_REQ_LOGIN,
	CMD_LOGIN,
	CMD_CHAT,
	CMD_MOVE,
};

class NetworkDataParser
{
public:
	using CallFunction = std::function<void(PACKET& packet)>;
	std::map<std::string, CallFunction> ExecutePacketMap;
};