#include "eCustomDialogBox.h"
#include "..\kokomando\Kernel.h"
#include <d3d9.h>
#include "..\kokomando\core.h"
#include "ePatches.h"
#include <algorithm>
#include <windowsx.h>

std::vector<eResolution> eCustomDialogBox::resolutions;
std::vector<std::string> eCustomDialogBox::resName;
bool eCustomDialogBox::m_bPatchesActivated;

void eCustomDialogBox::InitHooks()
{
	m_bPatchesActivated = false;
	GatherResolutions();
	InjectHook(0x45FEB0, CustomDialogBox, PATCH_JUMP);
}

bool mode_compare(eResolution first, eResolution in)
{
	return first.Y == in.Y && first.X == in.X;
}

void eCustomDialogBox::GatherResolutions()
{
	IDirect3D9* dev = Direct3DCreate9(D3D_SDK_VERSION);
	if (dev)
	{
		for (int i = 0; i < dev->GetAdapterModeCount(0, D3DFMT_X8R8G8B8); i++)
		{
			D3DDISPLAYMODE mode;

			dev->EnumAdapterModes(0, D3DFMT_X8R8G8B8, i, &mode);
			eResolution resolution;	
			resolution.X = mode.Width;
			resolution.Y = mode.Height;
			resolution.Bits = 32;

			resolutions.push_back(resolution);

		}
	}
	auto pos = std::unique(resolutions.begin(), resolutions.end(), mode_compare);
	resolutions.erase(pos, resolutions.end());

	for (int i = 0; i < resolutions.size(); i++)
	{
		static char temp[256];
		sprintf_s(temp, "%d x %d", resolutions[i].X, resolutions[i].Y);
		std::string tmp(temp, strlen(temp));
		resName.push_back(tmp);
	}
	dev->Release();
	dev = nullptr;
}



INT_PTR eCustomDialogBox::CustomDialogBox(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	HWND DialogName;
	HWND ResolutionSlider;
	HWND v6;
	LRESULT m_nSelectedResolution;
	LRESULT v8;
	HWND StartButton;
	HWND ExitButton;
	HWND VideoButton;
	HWND FullscreenCheckBox;

	DialogName = hDlg;
	ResolutionSlider = GetDlgItem(hDlg, 1000);
	v6 = GetDlgItem(hDlg, 1015);
	FullscreenCheckBox = GetDlgItem(hDlg, 1019);
	StartButton = GetDlgItem(DialogName, 1);
	ExitButton = GetDlgItem(DialogName, 2);
	VideoButton = GetDlgItem(DialogName, 1020);

	if (message == WM_INITDIALOG)
	{
		DWORD res = 0;

		res = GetPrivateProfileIntA("Settings", "VideoMode", 0, ".\\kokomando.ini");

		if (res > resolutions.size())
			res = 0;

		SetWindowTextA(DialogName, "KoKomando Remastered");
		SetWindowTextA(FullscreenCheckBox, "Fullscreen");
		SetWindowTextA(StartButton, "Start");
		SetWindowTextA(ExitButton, "Exit");
		SetWindowTextA(VideoButton, "Video");
		SendDlgItemMessageA(DialogName, 1019, 0xF1u, 1u, 0);
		SendMessageA(ResolutionSlider, 0x14Bu, 0, 0);
		SendMessageA(v6, 0x14Bu, 0, 0);
		for (int i = 0; i < resolutions.size(); ++i)
		{
			SendMessageA(ResolutionSlider, 0x143u, 0, (LPARAM)resName[i].c_str());
		}

		SendMessageA(ResolutionSlider, 0x14Eu, 1u, 0);
		SendMessageA(v6, 0x143u, 0, (LPARAM)*(int*)0x4CD0F4);
		SendMessageA(v6, 0x143u, 0, (LPARAM)*(int*)0x4CD0F0);
		SendMessageA(v6, 0x14Eu, 1u, 0);
	
		ComboBox_SetCurSel(ResolutionSlider, res);
	}
	else
	{
		if (message != 273 || wParam <= 0 || wParam > 2)
			return 0;



		EndDialog(DialogName, (WORD)wParam == 1);
		*(BYTE*)0x4CD0E0 = IsDlgButtonChecked(DialogName, 1019) == 1;
		m_nSelectedResolution = SendMessageA(ResolutionSlider, 0x147u, 0, 0);
		v8 = m_nSelectedResolution;
		char value[64] = {};
		sprintf_s(value, "%d", m_nSelectedResolution);
		WritePrivateProfileStringA("Settings", "VideoMode", value, ".\\kokomando.ini");
		CKernel::m_ResolutionX = resolutions[m_nSelectedResolution].X;
		CKernel::m_ResolutionY = resolutions[m_nSelectedResolution].Y;

		if (!m_bPatchesActivated)
		{
			ePatches::Init();
			m_bPatchesActivated = true;
		}

		SendMessageA(v6, 0x147u, 0, 0);
		if (!v8)
		{
			CKernel::m_ResolutionBits = 32;
			return 1;
		}
	}
	return 1;
}
