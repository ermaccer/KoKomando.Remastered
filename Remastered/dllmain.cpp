// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "code/plugin/eCustomDialogBox.h"
#include "code/plugin/eSettingsManager.h"

void Init()
{
	eSettingsManager::Init();
	eCustomDialogBox::InitHooks();
}

extern "C"
{
	__declspec(dllexport) void InitializeASI()
	{
		Init();
	}
}