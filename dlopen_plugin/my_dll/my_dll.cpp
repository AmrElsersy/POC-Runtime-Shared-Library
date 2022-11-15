#include <windows.h>
#include <iostream>

// DLLs also have an entry point known as DllMain It will be executed whenever a Dll file is loaded or unloaded to the running program/thread
BOOL WINAPI DllMain(
    HINSTANCE handleDll,  // handle to DLL module
    DWORD fdwReason,     // reason for calling function
    LPVOID lpReserved )  // reserved
{
    // Perform actions based on the reason for calling.
    switch( fdwReason ) 
    { 
        case DLL_PROCESS_ATTACH:
         // Initialize once for each new process.
            std::cout << "DLL process attatched" << std::endl;
            break;

        case DLL_THREAD_ATTACH:
         // Do thread-specific initialization.
            std::cout << "DLL thread attatched" << std::endl;
            break;

        case DLL_THREAD_DETACH:
         // Do thread-specific cleanup.
            std::cout << "DLL thread deattatched" << std::endl;
            break;

        case DLL_PROCESS_DETACH:
         // Perform any necessary cleanup.
            std::cout << "DLL process deattatched" << std::endl;
            break;
    }   
    // Successful. If this is FALSE, the process will be terminated eventually
    // https://docs.microsoft.com/en-us/windows/win32/dlls/dynamic-link-library-entry-point-function#entry-point-function-return-value
    return TRUE;  
}


EXTERN_C DWORD AddFunction(DWORD x, DWORD y)
{
    return x + y;
}


EXTERN_C DWORD MultiplyFunction(DWORD x)
{
    return x * 100;
}

EXTERN_C std::string StringFunction(std::string name)
{
    std::cout << "Hello StringFunction DLL: " << name << std::endl;
    return "Hello " + name;
}