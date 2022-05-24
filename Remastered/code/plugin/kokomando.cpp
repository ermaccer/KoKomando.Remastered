#include "kokomando.h"

int GetBaseAddress() {
	static int addr = reinterpret_cast<int>(GetModuleHandleA("MagnumEngine.dll"));
	return addr;
}

int  _dll(int address) {
	return GetBaseAddress() - 0x10000000 + address;
}

