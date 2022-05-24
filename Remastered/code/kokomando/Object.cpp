#include "Object.h"
#include "..\plugin\kokomando.h"
#include <iostream>
#include "..\plugin\eSettingsManager.h"

int cMagGameObject::GetWindowWidth()
{
	return ((int(__thiscall*)(cMagGameObject*))_dll(0x100268C0))(this);
}
int cMagGameObject::GetWindowHeight()
{
	return ((int(__thiscall*)(cMagGameObject*))_dll(0x100268B0))(this);
}
void cMagGameObject::SetVisibilityRange(float range)
{
	range *= eSettingsManager::m_fDrawDistanceMult;
	((void(__thiscall*)(cMagGameObject*, float))_dll(0x10026CE0))(this, range);
}

void cMagGameObject::SetFogRangeNear(float range)
{
	range *= eSettingsManager::m_fDrawDistanceMult;
	((void(__thiscall*)(cMagGameObject*, float))_dll(0x100679D0))(this, range);
}

void cMagGameObject::SetFogRangeFar(float range)
{
	range *= eSettingsManager::m_fDrawDistanceMult;
	((void(__thiscall*)(cMagGameObject*, float))_dll(0x10068BF0))(this, range);
}
