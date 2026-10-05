#pragma once


class Menu {
public:

    static bool Setup();
    static void Shutdown();
    static void Render();
    static bool IsRunning();
    static void SetWallhackEnabled(bool enabled);
    static bool IsWallhackEnabled();
    static void SetAlwaysCrosshairEnabled(bool enabled);
    static bool IsAlwaysCrosshairEnabled();
    static void SetVisible(bool visible);
    static bool IsVisible();
};
