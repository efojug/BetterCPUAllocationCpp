#include <iostream>
#include <windows.h>

int main(int argc, char *argv[]) {
	DWORD targetProcessId;
	std::cin >> targetProcessId;
	HANDLE hProcess = OpenProcess(PROCESS_SET_INFORMATION, FALSE, targetProcessId);
	if (hProcess == NULL) {
		std::cout << "OpenProcess Failed! Target ProcessId is NULL." << std::endl;
		return false;
	}
	DWORD_PTR processAffinityMask;
	DWORD_PTR systemAffinityMask;

	if (!GetProcessAffinityMask(hProcess, &processAffinityMask, &systemAffinityMask)) {
		std::cout << "hProcess:" << hProcess << std::endl << "processAffinityMask:" << &processAffinityMask << std::endl << "systemAffinityMask:" << &systemAffinityMask << std::endl;
		std::cerr << "GetProcessAffinityMask Failed!" << std::endl;
		CloseHandle(hProcess);
		return false;
	}

	DWORD_PTR newAffinityMask = 0x01;
	if (!SetProcessAffinityMask(hProcess, newAffinityMask)) {
		std::cerr << "SetProcessAffinityMask Failed!" << std::endl;
		CloseHandle(hProcess);
		return false;
	}
	std::cout << "SetProcess(" << targetProcessId << ")CPU Affinity Success!" << std::endl;
	CloseHandle(hProcess);
	return true;
}