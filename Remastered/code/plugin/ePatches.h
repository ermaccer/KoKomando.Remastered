#pragma once
#include "..\kokomando\Kernel.h"
#include <Windows.h>
class ePatches {
public:
	static void Init();

};
namespace MainHooks {
	LRESULT WINAPI HookedWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	void HookWndProc();
}

bool IsWindowFocused();