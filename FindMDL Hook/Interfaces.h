#pragma once

//Includes
#include "Offsets.h"
#include "Interfaces.h"
#include "IMDLCache.h"

//Extern Interfaces
namespace Interfaces
{
	void Initialise();

	extern IMDLCache* ModelCache;
};
