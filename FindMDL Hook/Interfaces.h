#pragma once

//Includes
#include "CommonIncludes.h"
#include "IMDLCache.h"
#include "offsets.h"
#include "Interfaces.h"

//Extern Interfaces
namespace Interfaces
{
	void Initialise();

	extern IMDLCache* ModelCache;
};
