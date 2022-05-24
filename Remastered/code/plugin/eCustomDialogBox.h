#pragma once
#include <Windows.h>
#include <vector>
#include <string>

struct eResolution {
	int X;
	int Y;
	int Bits;
};

class eCustomDialogBox {
private:
	static std::vector<eResolution> resolutions;
	static std::vector<std::string> resName;
	static bool   m_bPatchesActivated;
public:
	static void InitHooks();
	static void GatherResolutions();
	static INT_PTR CALLBACK CustomDialogBox(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
};