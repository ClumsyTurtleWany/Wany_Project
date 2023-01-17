#pragma once
#include "Define.hpp"

DWORD SyncLoad(std::wstring file)
{
	HANDLE hReadFile = CreateFile(file.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL); // �б� ���� ����
	
	DWORD dwRead = 0;
	LARGE_INTEGER FileSize;
	if (hReadFile != INVALID_HANDLE_VALUE)
	{
		::GetFileSizeEx(hReadFile, &FileSize);
		wchar_t* FileBuffer = new wchar_t[FileSize.LowPart];

		DWORD read;
		BOOL rst = ::ReadFile(hReadFile, FileBuffer, FileSize.QuadPart, &read, NULL);

		if (rst == TRUE)
		{

		}

		int a = 0;
	}
	CloseHandle(hReadFile);

	return 0;
}

DWORD SyncCopy(std::wstring src, std::wstring dst, DWORD dwFileSize)
{
	HANDLE hReadFile = CreateFile(src.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL); // �б� ���� ����
	HANDLE hWriteFile = CreateFile(dst.c_str(), GENERIC_READ, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL); // ������ ����

	DWORD dwRead = 0;
	LARGE_INTEGER FileSize;
	wchar_t* FileBuffer;
	if (hReadFile != INVALID_HANDLE_VALUE)
	{
		::GetFileSizeEx(hReadFile, &FileSize);
		FileBuffer = new wchar_t[FileSize.LowPart];

		BOOL rst = ::ReadFile(hReadFile, FileBuffer, FileSize.QuadPart, &dwRead, NULL);

		if (rst == TRUE)
		{

		}

		int a = 0;
	}

	if (hWriteFile != INVALID_HANDLE_VALUE)
	{
		BOOL rst = ::WriteFile(hWriteFile, FileBuffer, FileSize.QuadPart, &dwRead, NULL);
	}

	CloseHandle(hReadFile);

	return 0;
}

DWORD AsyncLoad(std::wstring file)
{
	HANDLE hReadFile = CreateFile(file.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL); // �б� ���� ����, FILE_FLAG_OVERLAPPED�� �񵿱�� ����� �ִ� ��.

	DWORD dwRead = 0;
	LARGE_INTEGER FileSize;
	bool isPending = false;
	if (hReadFile != INVALID_HANDLE_VALUE)
	{
		::GetFileSizeEx(hReadFile, &FileSize);
		wchar_t* FileBuffer = new wchar_t[FileSize.LowPart];

		OVERLAPPED readOV = { 0, }; // �񵿱�� �о���� ������ ������.
		DWORD read;
		BOOL rst = ::ReadFile(hReadFile, FileBuffer, FileSize.QuadPart, &read, &readOV);

		if (rst == FALSE)
		{
			if (GetLastError() == ERROR_IO_PENDING)
			{
				// �д� ��
				isPending = true;
			}
		}

		if (rst == TRUE)
		{
			// �ε� �Ϸ�
		}

		while (isPending)
		{
			// �񵿱� ������� ����� Ȯ���ϴ� �Լ�. �߰� ��� Ȯ�� �Ұ�.
			rst = ::GetOverlappedResult(hReadFile, &readOV, &dwRead, FALSE); //
			if (rst == TRUE)
			{
				isPending = false;
			}
		}

		int a = 0;
	}
	CloseHandle(hReadFile);

	return 0;
}

DWORD AsyncCopy(std::wstring src, std::wstring dst, DWORD dwFileSize)
{
	HANDLE hReadFile = CreateFile(src.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL); // �б� ���� ����
	HANDLE hWriteFile = CreateFile(dst.c_str(), GENERIC_READ, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL); // ������ ����

	DWORD dwRead = 0;
	LARGE_INTEGER FileSize;
	wchar_t* FileBuffer;
	if (hReadFile != INVALID_HANDLE_VALUE)
	{
		::GetFileSizeEx(hReadFile, &FileSize);
		FileBuffer = new wchar_t[FileSize.LowPart];

		BOOL rst = ::ReadFile(hReadFile, FileBuffer, FileSize.QuadPart, &dwRead, NULL);

		if (rst == TRUE)
		{

		}

		int a = 0;
	}

	if (hWriteFile != INVALID_HANDLE_VALUE)
	{
		BOOL rst = ::WriteFile(hWriteFile, FileBuffer, FileSize.QuadPart, &dwRead, NULL);
	}

	CloseHandle(hReadFile);

	return 0;
}


namespace AsyncFile_IO
{
	typedef struct AsyncFile
	{

	};

	class AsyncFile_IO
	{
	public:
		HANDLE FileHandle;
		wchar_t* Buffer;

	public:
		bool Open(std::wstring filename);
		bool Read();
		bool Wirte();
		bool Close();
	};
}