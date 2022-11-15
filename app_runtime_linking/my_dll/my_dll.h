#include <windows.h>
#include <string.h>

// https://tbhaxor.com/loading-dlls-using-cpp-in-windows/
// define pointers to functions of exported dll functions
typedef int(*GetElectronAddResult)();

