#pragma once

//Includes
#include "Utilities.h"
#include "VMTManager.h"

//Extern Hooks
namespace Hooks
{
	void Initialise();

	extern VMTManager VMTModelCache;
};