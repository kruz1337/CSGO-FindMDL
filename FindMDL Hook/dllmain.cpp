//Includes
#include <Windows.h>
#include "Utilities.h"
#include "Interfaces.h"
#include "Hooks.h"
#include "Offsets.h"

struct values {
    DWORD localPlayer;
    DWORD gameModule;
}value;

void main()
{
    Offsets::Initialise();
    Interfaces::Initialise();
    Hooks::Initialise();

    value.gameModule = (DWORD)GetModuleHandle("client.dll"); //Get "client.dll" module handle
    value.localPlayer = *(DWORD*)(value.gameModule + Offsets::dwLocalPlayer); //Get local player value 

    //Get local player value again if local player value is null
    if (value.localPlayer == NULL)
    {
        while (value.localPlayer == NULL)
        {
            value.localPlayer = *(DWORD*)(value.gameModule + Offsets::dwLocalPlayer);
        }
    }
}

//DLL Main
BOOL APIENTRY DllMain( HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        DisableThreadLibraryCalls(hModule);
        CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)main, NULL, NULL, NULL);
    }
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}