#pragma once


class Menu {
public:
    static bool Setup();
    static void Shutdown();
    static void Render();
    static bool IsRunning();
    static void SetWallhackEnabled(bool enabled);
    static bool IsWallhackEnabled();
    static void SetVisible(bool visible);
    static bool IsVisible();
    static void SetCurrentFPS(float fps);
    static float GetCurrentFPS();
};
