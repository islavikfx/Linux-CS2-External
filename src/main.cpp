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
                    std::cout << "[+] CS2 found! Wallhack: 0x" << std::hex << g_patch_addr << std::endl;
                }
            }
        } else {
            g_cs2_pid = 0;
            g_client_base = 0;
            g_patch_addr = 0;
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void ApplyPatch() {
    static bool last_state = false;
    
    while (g_running) {
        bool current = Menu::IsWallhackEnabled();
        
        if (g_cs2_pid != 0 && g_patch_addr != 0 && current != last_state) {
            if (current) {
                uint8_t nop[] = {0x90, 0x90}; // # nop, nop
                uint8_t current_bytes[2];
                
                if (ProcessManager::ReadMemory(g_cs2_pid, g_patch_addr, current_bytes, 2)) {
                    if (current_bytes[0] == 0x31 && current_bytes[1] == 0xC0) {
                        if (ProcessManager::WriteMemory(g_cs2_pid, g_patch_addr, nop, 2)) {
                            std::cout << "[+] Wallhack ON" << std::endl;
                        }
                    }
                }
            } else {
                uint8_t original[] = {0x31, 0xC0}; // # eax, eax
                uint8_t current_bytes[2];
                
                if (ProcessManager::ReadMemory(g_cs2_pid, g_patch_addr, current_bytes, 2)) {
                    if (current_bytes[0] == 0x90 && current_bytes[1] == 0x90) {
                        if (ProcessManager::WriteMemory(g_cs2_pid, g_patch_addr, original, 2)) {
                            std::cout << "[+] Wallhack OFF" << std::endl;
                        }
                    }
                }
            }
            last_state = current;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main() {
    std::cout << "Linux CS2 by @islavikfx" << std::endl;
    
    if (!Menu::Setup()) {
        std::cerr << "Fail!" << std::endl;
        return 1;
    }
    
    std::thread finder(FindCS2);
    std::thread applier(ApplyPatch);
    
    while (Menu::IsRunning()) {
        Menu::Render();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    
    g_running = false;
    finder.join();
    applier.join();
    Menu::Shutdown();
    
    return 0;
}