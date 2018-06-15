// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"

#include<stdlib.h>
#include <stdio.h>
#include <process.h>

void Thread(LPVOID lpParam)
{
	char buf[50] = { 0 };
	HWND h = FindWindow("OpusApp", NULL);
	if (h == NULL)
	{
		MessageBox(0, "没有打开word！！", "error", 0);
	}

	while (1)
	{
		int i=SetWindowPos(h, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		if (NULL == i)
		{
			sprintf(buf, "%d", GetLastError());
			MessageBox(0, buf, "error", 0);
		}
		Sleep(20);
	}
}

BOOL frist = false;
BOOL APIENTRY DllMain(HANDLE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
	)
{
	DWORD ThreadID;

	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		if (!frist)
		{
			DWORD a;
			int h = _beginthread(Thread, 0, NULL);
			if (h == -1)
			{
				MessageBox(0, "创造线程失败，重新打开程序", "e", 0);
			}
			frist = true;
		}

	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

