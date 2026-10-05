#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include <cstdlib>
#include <cstring>
#include "memory/ProcessManager.h"
#include "gui/Menu.h"
#include "sdk/Offsets.h"


static std::atomic<bool> g_running{true};
static uint32_t  g_cs2_pid     = 0;
static uintptr_t g_client_base = 0;
static uintptr_t g_xray_addr   = 0;
static uintptr_t g_cross_addr  = 0;


bool ValidateOffset() {
    if (g_cs2_pid == 0 || g_xray_addr == 0 || g_cross_addr == 0) return false;

    uint8_t xray_bytes[Patchs::xray_len];

    if (!ProcessManager::ReadMemory(g_cs2_pid, g_xray_addr, xray_bytes, Patchs::xray_len)) {
        std::cerr << "[-] Cannot read xray offset." << std::endl;
        return false;
    }

    if (std::memcmp(xray_bytes, Patchs::xray_off, Patchs::xray_len) != 0) {
        std::cout << "[~] Offsets not matching - last update at 5 October 2026." << " Maybe CS2 Updated. Check for update at GitHub page or try to restart game." << std::endl;
        return false;
    }

    return true;
}


bool InitializeCS2() {
    if (!ProcessManager::FindProcess("cs2", g_cs2_pid)) {
        std::cerr << "[-] CS2 not found. Start CS2 before inject." << std::endl;
        return false;
    }

    g_client_base = ProcessManager::GetModuleBase(g_cs2_pid, "libclient.so");
    if (g_client_base == 0) {
        std::cerr << "[-] Cannot find libclient.so base." << std::endl;
        return false;
    }

    g_xray_addr  = g_client_base + Offsets::xray;
    g_cross_addr = g_client_base + Offsets::cross;

    std::cout << "[+] CS2 found. PID: " << g_cs2_pid << "." << std::endl;

    if (!ValidateOffset()) {
        return false;
    }

    return true;
}


void FindCS2() {
    while (g_running) {
        uint32_t pid = 0;
        if (!ProcessManager::FindProcess("cs2", pid)) {
            std::cout << "[+] CS2 closed. Exiting." << std::endl;
            std::exit(0);
        }

        if (pid != g_cs2_pid) {
            g_cs2_pid = pid;
            uintptr_t base = ProcessManager::GetModuleBase(pid, "libclient.so");
            if (base != 0) {
                g_client_base = base;
                g_xray_addr = base + Offsets::xray;
                g_cross_addr = base + Offsets::cross;
            }
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}


void ApplyXray() {
    static bool last_state = false;

    while (g_running) {
        bool current = Menu::IsWallhackEnabled();

        if (g_cs2_pid != 0 && g_xray_addr != 0 && current != last_state) {
            if (current) {
                uint8_t current_bytes[Patchs::xray_len];
                if (ProcessManager::ReadMemory(g_cs2_pid, g_xray_addr, current_bytes, Patchs::xray_len)) {
                    if (std::memcmp(current_bytes, Patchs::xray_off, Patchs::xray_len) == 0) {
                        if (ProcessManager::WriteMemory(g_cs2_pid, g_xray_addr, Patchs::xray_set, Patchs::xray_len)) {
                            std::cout << "[+] Wallhack ON." << std::endl;
                        }
                    }
                }

            } else {
                uint8_t current_bytes[Patchs::xray_len];
                if (ProcessManager::ReadMemory(g_cs2_pid, g_xray_addr, current_bytes, Patchs::xray_len)) {
                    if (std::memcmp(current_bytes, Patchs::xray_set, Patchs::xray_len) == 0) {
                        if (ProcessManager::WriteMemory(g_cs2_pid, g_xray_addr, Patchs::xray_off, Patchs::xray_len)) {
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


void ApplyCrosshair() {
    static bool last_state = false;

    while (g_running) {
        bool current = Menu::IsAlwaysCrosshairEnabled();

        if (g_cs2_pid != 0 && g_cross_addr != 0 && current != last_state) {
            if (current) {
                uint8_t current_bytes[Patchs::cross_len];
                if (ProcessManager::ReadMemory(g_cs2_pid, g_cross_addr, current_bytes, Patchs::cross_len)) {
                    if (std::memcmp(current_bytes, Patchs::cross_off, Patchs::cross_len) == 0) {
                        if (ProcessManager::WriteMemory(g_cs2_pid, g_cross_addr, Patchs::cross_set, Patchs::cross_len)) {
                            std::cout << "[+] Always crosshair ON." << std::endl;
                        }
                    }
                }

            } else {
                uint8_t current_bytes[Patchs::cross_len];
                if (ProcessManager::ReadMemory(g_cs2_pid, g_cross_addr, current_bytes, Patchs::cross_len)) {
                    if (std::memcmp(current_bytes, Patchs::cross_set, Patchs::cross_len) == 0) {
                        if (ProcessManager::WriteMemory(g_cs2_pid, g_cross_addr, Patchs::cross_off, Patchs::cross_len)) {
                            std::cout << "[+] Always crosshair OFF." << std::endl;
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
        std::cerr << "[-] Failed to init." << std::endl;
        return 1;
    }

    std::thread finder(FindCS2);
    std::thread xray_applier(ApplyXray);
    std::thread cross_applier(ApplyCrosshair);

    while (Menu::IsRunning()) {
        Menu::Render();
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }

    g_running = false;

    if (g_cs2_pid != 0) {
        if (g_xray_addr != 0 && Menu::IsWallhackEnabled()) {
            ProcessManager::WriteMemory(g_cs2_pid, g_xray_addr, Patchs::xray_off, Patchs::xray_len);
        }
        if (g_cross_addr != 0 && Menu::IsAlwaysCrosshairEnabled()) {
            ProcessManager::WriteMemory(g_cs2_pid, g_cross_addr, Patchs::cross_off, Patchs::cross_len);
        }
    }

    finder.detach();
    xray_applier.detach();
    cross_applier.detach();

    Menu::Shutdown();

    return 0;
}
