#include "CommonIncludes.h"
#include "VMTManager.h"

bool VMTManager::Initialise(DWORD* InstancePointer)
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

int	VMTManager::MethodCount(DWORD* InstancePointer)
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

DWORD VMTManager::HookMethod(DWORD NewFunction, int Index)
{
	if (initComplete)
	{
		CustomTable[Index] = NewFunction;
		return OriginalTable[Index];
	}

	return NULL;
}

void VMTManager::UnhookMethod(int Index)
{
	if (initComplete)
	{
		CustomTable[Index] = OriginalTable[Index];
	}

	return;
}

void VMTManager::RestoreOriginal()
{
	if (initComplete)
	{
		*Instance = (DWORD)OriginalTable;
	}

	return;
}

void VMTManager::RestoreCustom()
{
	if (initComplete)
	{
		*Instance = (DWORD)CustomTable;
	}

	return;
}

DWORD VMTManager::GetOriginalFunction(int Index)
{
	return OriginalTable[Index];
}