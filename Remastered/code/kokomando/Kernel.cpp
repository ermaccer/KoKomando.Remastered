#include "Kernel.h"

int& CKernel::m_ResolutionX = *(int*)0x4CD0E4;
int& CKernel::m_ResolutionY = *(int*)0x4CD0E8;
int& CKernel::m_ResolutionBits = *(int*)0x4CD0EC;

float CKernel::GetAspectRatio()
{
	return (float)CKernel::m_ResolutionX / (float)CKernel::m_ResolutionY;
}
