#pragma once
#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <direct.h>

// �f�o�b�O���O�L�^�N���X
class DebugLog
{
public:

	static void DebugPrint(const char* pFormat, ...) {
#if defined(_DEBUG) || defined(DEBUG)
		va_list argp;
		char buf[256]; // �o�b�t�@�͑傫��
		va_start(argp, pFormat);
		vsprintf_s(buf, 256, pFormat, argp); // �o�b�t�@�ʂƑ�Q���������킹�邱��
		va_end(argp);
		OutputDebugStringA(buf);
		OutputDebugStringA("\n");
#else
		UNREFERENCED_PARAMETER(pFormat);
#endif // _DEBUG || DEBUG
	}

	static void DebugPrintSaveFlie(const char* fileName , const char* pFormat, ...)
	{
#if defined(_DEBUG) || defined(DEBUG)
		DebugPrint(pFormat);

		char cwd[256];
		_getcwd(cwd, 256);
		std::string logPath = cwd;
		logPath += "\\DebugLog";
		struct stat statBuf;
		if (stat(logPath.data(), &statBuf) != 0) 
		{
			_mkdir(logPath.data());
		}
		logPath += "\\";
		logPath += fileName;

		FILE* fp;
		fopen_s(&fp, logPath.data(), "a+");
		if (fp) {
			fprintf(fp, pFormat);
			fprintf(fp, "\n");
			fclose(fp);
		}
		else
		{
			OutputDebugString("!!CAN NOT OPEN FILE!!\n");	
		}
#else
		UNREFERENCED_PARAMETER(fileName);
		UNREFERENCED_PARAMETER(pFormat);
#endif // _DEBUG || DEBUG
	}

private:
	DebugLog() = delete;
	~DebugLog() = delete;
};