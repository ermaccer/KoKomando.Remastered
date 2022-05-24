#include "ePatches.h"
#include "kokomando.h"
#include "..\kokomando\core.h"
#include "..\kokomando\Kernel.h"
#include "..\kokomando\Sprite.h"
#include "..\kokomando\Object.h"
#include "..\kokomando\Player.h"
WNDPROC wOriginalWndProc = nullptr;
static bool	bWindowInFocus = true;

void ePatches::Init()
{
	Patch(0x49F658, &cMagSprite::SetPos);
	Patch(0x49F654, &cMagSprite::SetScale);
	Patch(0x49F464,&cMagGameObject::SetVisibilityRange);
	Patch(0x49F45C, &cMagGameObject::SetFogRangeNear);
	Patch(0x49F458, &cMagGameObject::SetFogRangeFar);
	InjectHook(_dll(0x100232A6), MainHooks::HookWndProc);
	InjectHook(0x439DE9, GivePointsForCoin);
	Patch<char>(0x4410D4 + 1, 15);
	Patch<int>(0x435E3A + 1, 0x4CAFA8);
}

LRESULT WINAPI MainHooks::HookedWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_KILLFOCUS:
		bWindowInFocus = false;
		break;
	case WM_SETFOCUS:
		bWindowInFocus = true;
		break;
	default:
		break;
	}

	return CallWindowProc(wOriginalWndProc, hWnd, uMsg, wParam, lParam);
}

void MainHooks::HookWndProc()
{
	wOriginalWndProc = (WNDPROC)SetWindowLongPtr(FindWindowA(0,"Kokomando"), GWLP_WNDPROC, (LONG_PTR)HookedWndProc);
}
