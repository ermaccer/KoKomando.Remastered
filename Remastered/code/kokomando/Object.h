#pragma once

class cMagGameObject {
public:
	int GetWindowWidth();	
	int GetWindowHeight();
	void SetVisibilityRange(float range);
	void SetFogRangeNear(float range);
	void SetFogRangeFar(float range);


};

int _strnicmp_hook(const char*, const char*, size_t);