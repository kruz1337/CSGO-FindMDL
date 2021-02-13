// Includes
#include "Utilities.h"
#include <fstream>
#include <Psapi.h>

//Utilities Memory
DWORD Utilities::Memory::WaitOnModuleHandle(std::string moduleName)
{
	DWORD ModuleHandle = NULL;
	while (!ModuleHandle)
	{
		ModuleHandle = (DWORD)GetModuleHandle(moduleName.c_str());
		if (!ModuleHandle)
			Sleep(50);
	}
	return ModuleHandle;
}
bool bCompare(const BYTE* Data, const BYTE* Mask, const char* szMask)
{
	for (; *szMask; ++szMask, ++Mask, ++Data)
	{
		if (*szMask == 'x' && *Mask != *Data)
		{
			return false;
		}
	}
	return (*szMask) == 0;
}
DWORD Utilities::Memory::FindPattern(std::string moduleName, BYTE* Mask, char* szMask)
{
	DWORD Address = WaitOnModuleHandle(moduleName.c_str());
	MODULEINFO ModInfo; GetModuleInformation(GetCurrentProcess(), (HMODULE)Address, &ModInfo, sizeof(MODULEINFO));
	DWORD Length = ModInfo.SizeOfImage;
	for (DWORD c = 0; c < Length; c += 1)
	{
		if (bCompare((BYTE*)(Address + c), Mask, szMask))
		{
			return (DWORD)(Address + c);
		}
	}
	return 0;
}
DWORD Utilities::Memory::FindTextPattern(std::string moduleName, char* string)
{
	DWORD Address = WaitOnModuleHandle(moduleName.c_str());
	MODULEINFO ModInfo; GetModuleInformation(GetCurrentProcess(), (HMODULE)Address, &ModInfo, sizeof(MODULEINFO));
	DWORD Length = ModInfo.SizeOfImage;

	int len = strlen(string);
	char* szMask = new char[len + 1];
	for (int i = 0; i < len; i++)
	{
		szMask[i] = 'x';
	}
	szMask[len] = '\0';

	for (DWORD c = 0; c < Length; c += 1)
	{
		if (bCompare((BYTE*)(Address + c), (BYTE*)string, szMask))
		{
			return (DWORD)(Address + c);
		}
	}
	return 0;
}

//VMT Manager
bool Utilities::Memory::VMTManager::Initialise(DWORD* InstancePointer)
{
	Instance = InstancePointer;
	OriginalTable = (DWORD*)*InstancePointer;
	int VMTSize = MethodCount(InstancePointer);
	size_t TableBytes = VMTSize * 4;

	CustomTable = (DWORD*)malloc(TableBytes + 8);
	if (!CustomTable) return false;
	memcpy((void*)CustomTable, (void*)OriginalTable, VMTSize * 4);

	*InstancePointer = (DWORD)CustomTable;

	initComplete = true;
	return true;
}
int	Utilities::Memory::VMTManager::MethodCount(DWORD* InstancePointer)
{
	DWORD* VMT = (DWORD*)*InstancePointer;
	int Index = 0;
	int Amount = 0;
	while (!IsBadCodePtr((FARPROC)VMT[Index]))
	{
		if (!IsBadCodePtr((FARPROC)VMT[Index]))
		{
			Amount++;
			Index++;
		}
	}

	return Amount;
}
DWORD Utilities::Memory::VMTManager::HookMethod(DWORD NewFunction, int Index)
{
	if (initComplete)
	{
		CustomTable[Index] = NewFunction;
		return OriginalTable[Index];
	}
	else
		return NULL;
}
void Utilities::Memory::VMTManager::UnhookMethod(int Index)
{
	if (initComplete)
		CustomTable[Index] = OriginalTable[Index];
	return;
}
void Utilities::Memory::VMTManager::RestoreOriginal()
{
	if (initComplete)
	{
		*Instance = (DWORD)OriginalTable;
	}
	return;
}
void Utilities::Memory::VMTManager::RestoreCustom()
{
	if (initComplete)
	{
		*Instance = (DWORD)CustomTable;
	}
	return;
}
DWORD Utilities::Memory::VMTManager::GetOriginalFunction(int Index)
{
	return OriginalTable[Index];
}