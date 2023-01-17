#pragma once
#include "Define.hpp"

DWORD SyncLoad(std::wstring file)
{
	HANDLE hReadFile = CreateFile(file.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL); // 읽기 전용 파일
	
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
	HANDLE hReadFile = CreateFile(src.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL); // 읽기 전용 파일
	HANDLE hWriteFile = CreateFile(dst.c_str(), GENERIC_READ, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL); // 무조건 생성

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
	HANDLE hReadFile = CreateFile(file.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL); // 읽기 전용 파일, FILE_FLAG_OVERLAPPED이 비동기로 만들어 주는 것.

	DWORD dwRead = 0;
	LARGE_INTEGER FileSize;
	bool isPending = false;
	if (hReadFile != INVALID_HANDLE_VALUE)
	{
		::GetFileSizeEx(hReadFile, &FileSize);
		wchar_t* FileBuffer = new wchar_t[FileSize.LowPart];

		OVERLAPPED readOV = { 0, }; // 비동기로 읽어오는 정보를 저장함.
		DWORD read;
		BOOL rst = ::ReadFile(hReadFile, FileBuffer, FileSize.QuadPart, &read, &readOV);

		if (rst == FALSE)
		{
			if (GetLastError() == ERROR_IO_PENDING)
			{
				// 읽는 중
				isPending = true;
			}
		}

		if (rst == TRUE)
		{
			// 로딩 완료
		}

		while (isPending)
		{
			// 비동기 입출력의 결과를 확인하는 함수. 중간 결과 확인 불가.
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
	HANDLE hReadFile = CreateFile(src.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL); // 읽기 전용 파일
	HANDLE hWriteFile = CreateFile(dst.c_str(), GENERIC_READ, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL); // 무조건 생성

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