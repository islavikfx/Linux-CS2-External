#include "ProcessManager.h"
#include <fstream>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <algorithm>
#include <cctype>

bool ProcessManager::FindProcess(const std::string& processName, uint32_t& pid) {
    DIR* dir = opendir("/proc");
    if (!dir) return false;
    
    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        bool isNumber = true;
        for (char* c = entry->d_name; *c; c++) {
            if (!isdigit(*c)) { isNumber = false; break; }
        }
        
        if (!isNumber) continue;
        
        std::string commPath = std::string("/proc/") + entry->d_name + "/comm";
        std::ifstream commFile(commPath);
        if (commFile.is_open()) {
            std::string comm;
            std::getline(commFile, comm);
            comm.erase(std::remove(comm.begin(), comm.end(), '\n'), comm.end());
            
            if (comm == processName) {
                pid = std::stoul(entry->d_name);
                closedir(dir);
                return true;
            }
        }
    }
    closedir(dir);
    return false;
}

uintptr_t ProcessManager::GetModuleBase(uint32_t pid, const std::string& moduleName) {
    std::string mapsPath = "/proc/" + std::to_string(pid) + "/maps";
    std::ifstream mapsFile(mapsPath);
    if (!mapsFile.is_open()) return 0;
    
    std::string line;
    while (std::getline(mapsFile, line)) {
        if (line.find(moduleName) != std::string::npos) {
            size_t dashPos = line.find('-');
            if (dashPos != std::string::npos) {
                return std::stoul(line.substr(0, dashPos), nullptr, 16);
            }
        }
    }
    return 0;
}

bool ProcessManager::ReadMemory(uint32_t pid, uintptr_t address, void* buffer, size_t size) {
    std::string memPath = "/proc/" + std::to_string(pid) + "/mem";
    int memFd = open(memPath.c_str(), O_RDONLY);
    if (memFd == -1) return false;
    
    lseek(memFd, address, SEEK_SET);
    ssize_t bytesRead = read(memFd, buffer, size);
    close(memFd);
    
    return bytesRead == static_cast<ssize_t>(size);
}

bool ProcessManager::WriteMemory(uint32_t pid, uintptr_t address, const void* buffer, size_t size) {
    std::string memPath = "/proc/" + std::to_string(pid) + "/mem";
    int memFd = open(memPath.c_str(), O_RDWR);
    if (memFd == -1) return false;
    
    lseek(memFd, address, SEEK_SET);
    ssize_t bytesWritten = write(memFd, buffer, size);
    close(memFd);
    
    return bytesWritten == static_cast<ssize_t>(size);
}