#include <iostream>
#include <thread>
#include <chrono>
#include "memory/ProcessManager.h"
#include "gui/Menu.h"
#include "sdk/Offsets.h"


static bool g_running = true;
static uint32_t g_cs2_pid = 0;
static uintptr_t g_client_base = 0;
static uintptr_t g_patch_addr = 0;


bool ValidateOffset() {
    if (g_cs2_pid == 0 || g_patch_addr == 0) return false;
    
    uint8_t bytes[2];
    if (!ProcessManager::ReadMemory(g_cs2_pid, g_patch_addr, bytes, 2)) {
        return false;
    }
    
    if (bytes[0] == 0x31 && bytes[1] == 0xc0) {
        return true;
    }
    
    std::cout << "[+] Offset not matching (0x18da4f2)."
    << " Maybe CS2 Updated. Check for new file at GitHub project page or try to restart game." << std::endl;
    return false;
}


bool InitializeCS2() {
    if (!ProcessManager::FindProcess("cs2", g_cs2_pid)) {
        std::cerr << "[+] Aborted! CS2 Not found. Start CS2 before inject." << std::endl;
        return false;
    }
    
    g_client_base = ProcessManager::GetModuleBase(g_cs2_pid, "libclient.so");
    if (g_client_base == 0) {
        std::cerr << "[+] Aborted! Cannot find libclient.so base." << std::endl;
        return false;
    }
    
    g_patch_addr = g_client_base + Offsets::xray;
    std::cout << "[+] CS2 found. PID: " << g_cs2_pid << "." << std::endl;
    
    if (!ValidateOffset()) {
        return false;
    }
    
    return true;
}


void FindCS2() {
    while (g_running) {
        uint32_t pid = 0;
        if (ProcessManager::FindProcess("cs2", pid)) {
            if (pid != g_cs2_pid) {
                g_cs2_pid = pid;
                uintptr_t base = ProcessManager::GetModuleBase(pid, "libclient.so");
                if (base != 0) {
                    g_client_base = base;
                    g_patch_addr = base + Offsets::xray;
                    std::cout << "[+] CS2 reconnected." 
                              << std::hex << g_patch_addr << std::endl;
                }
            }
        } else {

            if (g_cs2_pid != 0) {
                std::cout << "[+] CS2 closed, waiting..." << std::endl;
                Menu::SetWallhackEnabled(false);
            }
            g_cs2_pid = 0;
            g_client_base = 0;
            g_patch_addr = 0;
        }
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}


void ApplyPatch() {
    static bool last_state = false;
    
    while (g_running) {
        bool current = Menu::IsWallhackEnabled();
        
        if (g_cs2_pid != 0 && g_patch_addr != 0 && current != last_state) {
            if (current) {
                uint8_t nop[] = {0x90, 0x90};
                uint8_t current_bytes[2];
                
                if (ProcessManager::ReadMemory(g_cs2_pid, g_patch_addr, current_bytes, 2)) {
                    if (current_bytes[0] == 0x31 && current_bytes[1] == 0xc0) {
                        if (ProcessManager::WriteMemory(g_cs2_pid, g_patch_addr, nop, 2)) {
                            std::cout << "[+] Wallhack ON." << std::endl;
                        }
                    }
                }
            } else {

                uint8_t original[] = {0x31, 0xc0};
                uint8_t current_bytes[2];
                
                if (ProcessManager::ReadMemory(g_cs2_pid, g_patch_addr, current_bytes, 2)) {
                    if (current_bytes[0] == 0x90 && current_bytes[1] == 0x90) {
                        if (ProcessManager::WriteMemory(g_cs2_pid, g_patch_addr, original, 2)) {
                            std::cout << "[+] Wallhack OFF." << std::endl;
                        }
                    }
                }
            }
            last_state = current;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}


int main() {
    std::cout << "// Linux CS2 by @islavikfx.\n";
    
    if (!InitializeCS2()) {
        return 1;
    }
    
    if (!Menu::Setup()) {
        std::cerr << "[+] Failed to init." << std::endl;
        return 1;
    }
    
    std::thread finder(FindCS2);
    std::thread applier(ApplyPatch);
    
    auto lastTime = std::chrono::high_resolution_clock::now();
    int frameCount = 0;
    float currentFPS = 0.0f;
    
    while (Menu::IsRunning()) {
        Menu::Render();
        
        frameCount++;
        auto currentTime = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
            currentTime - lastTime).count();
        
        if (elapsed >= 1000) {
            currentFPS = frameCount * 1000.0f / elapsed;
            frameCount = 0;
            lastTime = currentTime;
            Menu::SetCurrentFPS(currentFPS);
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
    
    g_running = false;
    finder.join();
    applier.join();
    Menu::Shutdown();
    
    return 0;
}
