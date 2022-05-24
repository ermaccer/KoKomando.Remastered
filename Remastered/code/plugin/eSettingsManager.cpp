#include "eSettingsManager.h"
#include "..\..\IniReader.h"
float eSettingsManager::m_fDrawDistanceMult;

void eSettingsManager::Init()
{
	CIniReader ini("");

	m_fDrawDistanceMult = ini.ReadFloat("Settings", "m_fDrawDistanceMult", 1.0f);
}
