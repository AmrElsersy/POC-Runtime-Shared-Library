#include <windows.h>
#include <string.h>

// define pointers to functions of exported dll functions
typedef DWORD(*AddFunction)(DWORD x, DWORD y);
typedef DWORD(*MultiplyFunction)(DWORD x);
typedef std::string (*StringFunction)(std::string name);

