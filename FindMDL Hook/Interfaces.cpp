//Includes
#include "Interfaces.h"

typedef void* (__cdecl* CreateInterface_t)(const char*, int*);
CreateInterface_t DataCaching = NULL;

//Interfaces
namespace Interfaces
{
	IMDLCache* ModelCache;
};

//Initialise Interfaces
void Interfaces::Initialise()
{
	DataCaching = (CreateInterface_t)GetProcAddress((HMODULE)Offsets::DataCaches, "CreateInterface"); //Getting the process address of the DataCaches offset

	char* pDataCache = (char*)FindTextPattern("datacache.dll", "MDLCache00"); //Getting MDLCache00 memory address on "datacache.dll" module

	ModelCache = (IMDLCache*)DataCaching(pDataCache, NULL);
};