#include <windows.h>
#include <bits/stdc++.h>

#include "my_dll/my_dll.h"

int main()
{
    std::string dllLibPath = "my_dll/build/libelectron_runtime_dll.dll";
    HINSTANCE dllHandle = LoadLibrary(dllLibPath.c_str());
    if (NULL == dllHandle)
    {
        std::cout << "Cannot load dll handle of " << dllLibPath << std::endl;
        exit(0);
    }

    GetElectronAddResult get_electron_result_func = (GetElectronAddResult)GetProcAddress(dllHandle, "GetElectronAddResult");
    int result = get_electron_result_func();
    std::cout << "main thread: result = " << result << std::endl;

    FreeLibrary(dllHandle);
    return 0;
}