#include "Sprite.h"
#include "..\plugin\kokomando.h"
#include "Kernel.h"
#include "Object.h"

void cMagSprite::SetPos(int texture, float x, float y, int unk)
{
	float scale = (4.0f / 3.0f) / CKernel::GetAspectRatio();
	x *= scale;
	float offset = 0.0f;
	float desired_pos = roundf(((float)CKernel::m_ResolutionX - ((float)CKernel::m_ResolutionY * ((4.0f / 3.0f) / CKernel::GetAspectRatio()))) / 2.0f);
	offset = ((100.0f * desired_pos) / (float)CKernel::m_ResolutionX) / 100.0f;
	offset /= 2.0f;
	x += offset;

	((void(__thiscall*)(cMagSprite*, int, float, float, int))_dll(0x1005A8E0))(this, texture, x, y, unk);
}


void cMagSprite::SetScale(int texture, float x, float y)
{
	float scale = (4.0f / 3.0f) / CKernel::GetAspectRatio();
	x *= scale;

	((void(__thiscall*)(cMagSprite*, int, float, float))_dll(0x1005AA20))(this, texture, x, y);
}
