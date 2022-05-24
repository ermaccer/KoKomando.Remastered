#include "Player.h"

void __fastcall GivePointsToPlayer(int player, int points)
{
	((void(__thiscall*)(int,int))(0x411D00))(player, points);
}

void __fastcall GivePointsForCoin(int player)
{
	GivePointsToPlayer(player, 1);
}
