#include <windows.h>
#include <bits/stdc++.h>

#include "my_dll/my_dll.h"

int main()
{
    std::string dllLibPath = "C:/IQT/POC/dlopen_plugin/my_dll/build/libDLL_SHARED_LIBRARY.dll";
    HINSTANCE dllHandle = LoadLibrary(dllLibPath.c_str());
    if (NULL == dllHandle)
    {
        std::cout << "Cannot load dll handle of " << dllLibPath << std::endl;
        exit(0);
    }

    AddFunction add_func_ptr = (AddFunction)GetProcAddress(dllHandle, "AddFunction");
    MultiplyFunction multiply_func_ptr = (MultiplyFunction)GetProcAddress(dllHandle, "MultiplyFunction");
    StringFunction str_func_ptr = (StringFunction)GetProcAddress(dllHandle, "StringFunction");

    std::cout << "## add_func result = " << add_func_ptr(10, 20) << std::endl;
    std::cout << "## multiply_func_ptr result = " << multiply_func_ptr(15) << std::endl;
    str_func_ptr("Sersy");


    return 0;
}