#include <iostream>
#include <string>
#include <windows.h>

#include <tlhelp32.h> // For PROCESSENTRY32

bool InjectDLL(const std::string & processName, const std::string & dllName)
{
	// Find the target process
	DWORD processId = 0;
	HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (snap == INVALID_HANDLE_VALUE)
	{
		std::cerr << "Failed to create snapshot.\n";
		return false;
	}

	PROCESSENTRY32 entry = { sizeof(PROCESSENTRY32) };
	if (Process32First(snap, &entry))
	{
		do
		{
			if (processName == entry.szExeFile)
			{
				processId = entry.th32ProcessID;
				break;
			}
		} while (Process32Next(snap, &entry));
	}
	CloseHandle(snap);

	if (processId == 0)
	{
		std::cerr << "Could not find the target process.\n";
		return false;
	}

	// Open the target process
	HANDLE processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);
	if (!processHandle)
	{
		std::cerr << "Failed to open process.\n";
		return false;
	}

	// Allocate memory in the target process for the DLL path
	void * allocAddress =
		VirtualAllocEx(processHandle, nullptr, dllName.size() + 1, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	if (!allocAddress)
	{
		std::cerr << "Failed to allocate memory in target process.\n";
		CloseHandle(processHandle);
		return false;
	}

	// Write the DLL path into the allocated memory
	if (!WriteProcessMemory(processHandle, allocAddress, dllName.c_str(), dllName.size() + 1, nullptr))
	{
		std::cerr << "Failed to write DLL path to target process.\n";
		VirtualFreeEx(processHandle, allocAddress, 0, MEM_RELEASE);
		CloseHandle(processHandle);
		return false;
	}

	// Load the DLL using LoadLibraryA
	HMODULE kernel32 = GetModuleHandle("kernel32.dll");
	if (!kernel32)
	{
		std::cerr << "Failed to get handle to kernel32.dll.\n";
		VirtualFreeEx(processHandle, allocAddress, 0, MEM_RELEASE);
		CloseHandle(processHandle);
		return false;
	}

	FARPROC loadLibraryAddr = GetProcAddress(kernel32, "LoadLibraryA");
	if (!loadLibraryAddr)
	{
		std::cerr << "Failed to find LoadLibraryA function.\n";
		VirtualFreeEx(processHandle, allocAddress, 0, MEM_RELEASE);
		CloseHandle(processHandle);
		return false;
	}

	// Create a remote thread in the target process
	HANDLE remoteThread = CreateRemoteThread(processHandle, nullptr, 0, (LPTHREAD_START_ROUTINE)loadLibraryAddr,
											 allocAddress, 0, nullptr);
	if (!remoteThread)
	{
		std::cerr << "Failed to create remote thread.\n";
		VirtualFreeEx(processHandle, allocAddress, 0, MEM_RELEASE);
		CloseHandle(processHandle);
		return false;
	}

	// Wait for the remote thread to finish
	WaitForSingleObject(remoteThread, INFINITE);

	// Clean up
	VirtualFreeEx(processHandle, allocAddress, 0, MEM_RELEASE);
	CloseHandle(remoteThread);
	CloseHandle(processHandle);

	return true;
}

int main()
{
	// Get current directory
	char currentDir[MAX_PATH];
	if (!GetCurrentDirectory(MAX_PATH, currentDir))
	{
		std::cerr << "Failed to get current directory.\n";
		return 1;
	}

	// Labtool.dll must be in the same directory as the injector
	std::string dllPath = std::string(currentDir) + "\\Labtool.dll";

	// Inject the DLL
	if (!InjectDLL("BBBR.exe", dllPath))
	{
		std::cerr << "DLL injection failed.\n";
		return 1;
	}

	std::cout << "DLL injection successful.\n";

	return 0;
}
