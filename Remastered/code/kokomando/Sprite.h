#pragma once

struct sprite {
	int textureID;
	char pad[24];
	float X;
	float Y;
	char _pad[44];
	int  sizeX;
	int  sizeY;
	float unk_float;
	char __pad[4];
	char textureName[256];
};


class cMagSprite {
private:
	char pad[3816];
	sprite* arraySpr;
public:
	void SetPos(int texture, float x, float y, int unk);
	void SetScale(int texture, float x, float y);
};