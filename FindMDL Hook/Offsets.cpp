#include "Offsets.h"

//Initialise Offsets
void Offsets::Initialise()
{
	DataCaches = WaitOnModuleHandle("datacache.dll");
	dwLocalPlayer = 0xD882B;
};

//Offsets
namespace Offsets
{
	DWORD DataCaches;
	DWORD dwLocalPlayer;
}