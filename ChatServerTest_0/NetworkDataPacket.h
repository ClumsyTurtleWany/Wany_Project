#pragma once

#pragma pack(push, 1) // 1����Ʈ ��ŷ���� �����Ѵ�.
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
// ���� �̷������� �۾��ϰԵǸ� ���� ū ��Ʈ �������� �Ͽ� 12����Ʈ�� ����ü�� ������.
// #pragma pack(push, �����ͻ�����) �� ���ϴ� ũ������� ��ŷ�ϸ� �� 8����Ʈ�� ���� ������.

#pragma pack(pop)
