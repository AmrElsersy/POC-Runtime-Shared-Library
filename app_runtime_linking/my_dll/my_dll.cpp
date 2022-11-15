#include <windows.h>
#include <iostream>
#include <bits/stdc++.h>

#define ELECTRON_EXE "C:/IQT/5g-iqt/IQT/Frontend/node_modules/electron/dist/electron.exe"
#define ELECTRON_SPLIT_CHAR '='
#define ELECTRON_DATA_SPLIT_CHAR ','
 
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

#include <stdexcept>
static std::string Exec(std::string p_strCommand)
{
	char buffer[128];
	std::string result = "";
	FILE* pipe = popen(p_strCommand.c_str(), "r");
	if (!pipe) return "";
	try
	{
		while (fgets(buffer, sizeof(buffer), pipe) != NULL)
			result += buffer;
	}
	catch (...)
	{
		pclose(pipe);
		return "";
	}
	pclose(pipe);
	return result;
}

std::vector<std::string> tokenize(std::string const &str, const char delim)
{
    std::vector<std::string> result;

    // construct a stream from the string
    std::stringstream ss(str);
 
    std::string s;
    while (std::getline(ss, s, delim)) {
        if (s.empty()) // skip empty lines
            continue;
        result.push_back(s);
    }
    return result;
}
// split the output of electron to map of key=operation type in electron, and value with electron data
std::map<std::string, std::string> ParseElectronOutput(std::string console_output)
{
    std::map<std::string, std::string> operationToData;
    auto lines = tokenize(console_output, '\n');   
    for (auto line : lines)
    {
        auto split_line = tokenize(line, ELECTRON_SPLIT_CHAR);
        if (split_line.size() == 2)
        {
            operationToData[split_line[0]] = split_line[1];
        }
    }
    return operationToData;
}

// Parse string with data in format n1,n2 to 2 integers and add them
int AddElectronInputData(std::string add_data_str)
{
    auto nums_str = tokenize(add_data_str, ELECTRON_DATA_SPLIT_CHAR);
    if (nums_str.size() == 2)
    {
        int result = 0;
        for(auto num_str : nums_str)
            result += std::stoi(num_str);        
        return result;
    }
    else 
    {
        std::cout << "Invalid format of electron input data: " << add_data_str << std::endl;
        return 0;
    }
}

EXTERN_C int GetElectronAddResult()
{
    auto console_output = Exec(std::string(ELECTRON_EXE) + " " + "C:/IQT/POC/app_runtime_linking/ui/");
    auto operationToDataMap = ParseElectronOutput(console_output);
    std::string addDataKey = "add_data";
    if (operationToDataMap.count(addDataKey))
    {
        int addResult = AddElectronInputData(operationToDataMap[addDataKey]);
        return addResult;
    }
    return 0;
}
