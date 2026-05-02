#pragma once
#include <string>
#include <cstdint>


class ProcessManager {
public:
    static bool FindProcess(const std::string& processName, uint32_t& pid);
    static uintptr_t GetModuleBase(uint32_t pid, const std::string& moduleName);
    static bool ReadMemory(uint32_t pid, uintptr_t address, void* buffer, size_t size);
    static bool WriteMemory(uint32_t pid, uintptr_t address, const void* buffer, size_t size);
};
