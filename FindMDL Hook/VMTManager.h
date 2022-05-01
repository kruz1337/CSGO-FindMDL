#pragma once

class VMTManager
{
private:
	DWORD* CustomTable;
	bool	initComplete;
	DWORD* OriginalTable;
	DWORD* Instance;

	int		MethodCount(DWORD* InstancePointer);

public:
	bool	Initialise(DWORD* InstancePointer); // Pass a &class

	DWORD	HookMethod(DWORD NewFunction, int Index);
	void	UnhookMethod(int Index);

	void	RestoreOriginal();
	void	RestoreCustom();

	template<typename T>
	T GetMethod(size_t nIndex)
	{
		return (T)OriginalTable[nIndex];
	}

	DWORD	GetOriginalFunction(int Index);
};

template<typename T>
FORCEINLINE T GetMethod(const void* instance, size_t index)
{
	uintptr_t* vmt = *(uintptr_t**)instance;

	return (T)vmt[index];
}