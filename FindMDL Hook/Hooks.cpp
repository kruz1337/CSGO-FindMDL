//Includes
#include "Hooks.h"
#include "Interfaces.h"
#include "Utilities.h"

typedef MDLHandle_t(__thiscall* iFindMdl)(void*, char*);
iFindMdl oFindMDL;
MDLHandle_t __fastcall hkFindMDL(void*, void*, char*);

//Hooks
namespace Hooks
{
	VMTManager VMTModelCache;
};

//Hooks Initialise
void Hooks::Initialise()
{
	VMTModelCache.Initialise((DWORD*)Interfaces::ModelCache);  //Initialise ModelCache interfaces with VMTManager
	oFindMDL = (iFindMdl)VMTModelCache.HookMethod((DWORD)&hkFindMDL, 10); //Hooking FindMDL
}

//Custom Models
MDLHandle_t __fastcall hkFindMDL(void* ecx, void* edx, char* FilePath)
{
	if (strstr(FilePath, "knife_default_ct.mdl") || strstr(FilePath, "knife_default_t.mdl"))
	{
		sprintf(FilePath, "models/weapons/v_minecraft_pickaxe.mdl");
	}

	return oFindMDL(ecx, FilePath);
}