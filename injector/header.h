#pragma once
#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <tlhelp32.h>

int g_injectorResponse = -1;

class injector {
    private:
    LPCSTR processName, dllName;
    HANDLE pHandle, tHandle;
    DWORD PID;

    public:
        injector(LPCSTR processName, LPCSTR dllName) : processName(processName), dllName(dllName) {
            PID = GetPID(processName);
            pHandle = PID ? OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID) : NULL;
            std::cout << inject();
            std::cin.ignore();
        }

        DWORD GetPID(LPCSTR pName) {
            HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

            PROCESSENTRY32 pEntry;

            pEntry.dwSize = sizeof(pEntry);

            if (Process32First(snapshot, &pEntry)) {
                do {
                    if (strcmp((const char*)pEntry.szExeFile, pName) == 0) {
                        CloseHandle(snapshot);
                        return pEntry.th32ProcessID;
                    }

                } while (Process32Next(snapshot, &pEntry));
            }

            CloseHandle(snapshot);
            return 0;
        }

        int inject() {
            PID = GetPID(processName);
            if (!PID) return g_injectorResponse = 1;

            pHandle = OpenProcess(PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_CREATE_THREAD, FALSE, PID);
            if (!pHandle) return g_injectorResponse = 2;

            char buff[MAX_PATH];
            GetFullPathNameA(dllName, MAX_PATH, buff, nullptr);
            std::string path(buff);

            LPVOID alloca = VirtualAllocEx(pHandle, NULL, path.length() + 1, MEM_COMMIT, PAGE_READWRITE); 
            if (!alloca) return g_injectorResponse = 3;

            if (!WriteProcessMemory(pHandle, alloca, (void*)(path.c_str()), path.length() + 1, nullptr)) {
                VirtualFreeEx(pHandle, alloca, 0, MEM_RELEASE);
                return g_injectorResponse = 5;
            }

            HANDLE hThread = CreateRemoteThread(pHandle, nullptr, 0, (LPTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA"), alloca, 0, nullptr);
            
            if (!hThread) {
                DWORD err = GetLastError();
                std::cout << "Error creating thread: " << err;
            }
            

            if (!hThread) {
                VirtualFreeEx(pHandle, alloca, 0, MEM_RELEASE);
                return g_injectorResponse = 6;
            }
    
            WaitForSingleObject(hThread, INFINITE);

            return g_injectorResponse;
        }
};