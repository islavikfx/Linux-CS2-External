#include "Menu.h"
#include "../imgui/imgui.h"
#include "../imgui/backends/imgui_impl_glfw.h"
#include "../imgui/backends/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <string>


static bool g_running = true;
static bool g_minimized = false;
static bool g_wallhack_enabled = false;
static GLFWwindow* g_window = nullptr;
static int g_fullWidth = 300;
static int g_fullHeight = 150;
static int g_miniWidth = 60;
static int g_miniHeight = 60;
static int g_windowPosX = 100;
static int g_windowPosY = 100;
static bool g_dragging = false;
static ImVec2 g_dragOffset;


bool Menu::Setup() {
    if (!glfwInit()) return false;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
    glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);
    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    
    g_window = glfwCreateWindow(g_fullWidth, g_fullHeight, "@islavikfx", nullptr, nullptr);
    if (!g_window) {
        glfwTerminate();
        return false;
    }

    glfwSetWindowPos(g_window, g_windowPosX, g_windowPosY);
    glfwMakeContextCurrent(g_window);
    glfwSwapInterval(1);

    glfwSetMouseButtonCallback(g_window, [](GLFWwindow* win, int button, int action, int) {
        if (button == GLFW_MOUSE_BUTTON_LEFT) {
            if (action == GLFW_PRESS) {
                double xpos, ypos;
                glfwGetCursorPos(win, &xpos, &ypos);
                g_dragging = true;
                g_dragOffset = ImVec2(xpos, ypos);
            } else if (action == GLFW_RELEASE) {
                g_dragging = false;
            }
        }
    });

    glfwSetCursorPosCallback(g_window, [](GLFWwindow* win, double xpos, double ypos) {
        if (g_dragging) {
            int currentX, currentY;
            glfwGetWindowPos(win, &currentX, &currentY);
            int newX = currentX + (xpos - g_dragOffset.x);
            int newY = currentY + (ypos - g_dragOffset.y);
            glfwSetWindowPos(win, newX, newY);
            g_windowPosX = newX;
            g_windowPosY = newY;
        }
    });

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->AddFontDefault();
    ImGui::StyleColorsDark();
    ImGuiStyle& style = ImGui::GetStyle();
    
    style.WindowRounding = 12.0f;
    style.WindowBorderSize = 2.5f;
    style.WindowPadding = ImVec2(22, 18);
    style.FramePadding = ImVec2(6, 5);
    style.ItemSpacing = ImVec2(0, 5);
    style.ItemInnerSpacing = ImVec2(5, 4);
    style.Alpha = 0.95f;
    style.FrameRounding = 8.0f;
    style.GrabRounding = 8.0f;
    style.ScrollbarSize = 0.0f;
    
    ImVec4* colors = style.Colors;
    colors[ImGuiCol_WindowBg] = ImVec4(0.03f, 0.03f, 0.03f, 0.96f);
    colors[ImGuiCol_Border] = ImVec4(0.85f, 0.12f, 0.12f, 1.0f);
    colors[ImGuiCol_CheckMark] = ImVec4(0.95f, 0.28f, 0.55f, 1.0f);
    colors[ImGuiCol_FrameBg] = ImVec4(0.07f, 0.07f, 0.07f, 0.85f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.09f, 0.09f, 0.09f, 0.90f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.07f, 0.07f, 0.07f, 0.85f);
    colors[ImGuiCol_Text] = ImVec4(0.88f, 0.88f, 0.88f, 1.0f);
    
    ImGui_ImplGlfw_InitForOpenGL(g_window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    return true;
}


void Menu::Shutdown() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    
    if (g_window) {
        glfwDestroyWindow(g_window);
        g_window = nullptr;
    }
    
    glfwTerminate();
}


void Menu::Render() {
    glfwPollEvents();
    
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    int currentWidth, currentHeight;
    glfwGetWindowSize(g_window, &currentWidth, &currentHeight);
    
    ImGui::SetNextWindowSize(ImVec2(currentWidth, currentHeight), ImGuiCond_Always);
    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
    
    ImGui::Begin("Main", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | 
    ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | 
    ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoScrollbar);

    ImDrawList* drawList = ImGui::GetWindowDrawList();
    ImVec2 windowPos = ImGui::GetWindowPos();
    float windowWidth = ImGui::GetWindowWidth();
    float windowHeight = ImGui::GetWindowHeight();
    
    if (g_minimized) {
        ImVec2 center(windowPos.x + windowWidth / 2, windowPos.y + windowHeight / 2);
        
        drawList->AddTriangleFilled(
            ImVec2(center.x, center.y - 15),
            ImVec2(center.x - 12, center.y + 12),
            ImVec2(center.x + 12, center.y + 12),
            IM_COL32(255, 50, 50, 255)
        );
        
        if (ImGui::IsMouseClicked(0) && 
            ImGui::GetIO().MousePos.x > windowPos.x && 
            ImGui::GetIO().MousePos.x < windowPos.x + windowWidth &&
            ImGui::GetIO().MousePos.y > windowPos.y && 
            ImGui::GetIO().MousePos.y < windowPos.y + windowHeight) {
            g_minimized = false;
            glfwSetWindowSize(g_window, g_fullWidth, g_fullHeight);
        }
    } else {
        ImVec2 closePos(windowPos.x + windowWidth - 40, windowPos.y + 8);
        bool closeHovered = (ImGui::GetIO().MousePos.x > closePos.x && 
        ImGui::GetIO().MousePos.x < closePos.x + 24 &&
        ImGui::GetIO().MousePos.y > closePos.y && 
        ImGui::GetIO().MousePos.y < closePos.y + 24);
        
        if (closeHovered) {
            drawList->AddRectFilled(closePos, ImVec2(closePos.x + 24, closePos.y + 24), IM_COL32(190, 35, 75, 255), 5.0f);
            if (ImGui::IsMouseClicked(0)) {
                g_running = false;
            }
        } else {
            drawList->AddRectFilled(closePos, ImVec2(closePos.x + 24, closePos.y + 24), IM_COL32(35, 6, 12, 255), 5.0f);
        }
        drawList->AddRect(closePos, ImVec2(closePos.x + 24, closePos.y + 24), IM_COL32(255, 65, 135, 255), 5.0f);
        drawList->AddLine(ImVec2(closePos.x + 6, closePos.y + 6), 
        ImVec2(closePos.x + 18, closePos.y + 18), IM_COL32(255, 65, 135, 255), 2.5f);
        drawList->AddLine(ImVec2(closePos.x + 18, closePos.y + 6), 
        ImVec2(closePos.x + 6, closePos.y + 18), IM_COL32(255, 65, 135, 255), 2.5f);
        
        ImVec2 minPos(windowPos.x + windowWidth - 72, windowPos.y + 8);
        bool minHovered = (ImGui::GetIO().MousePos.x > minPos.x && 
        ImGui::GetIO().MousePos.x < minPos.x + 24 &&
        ImGui::GetIO().MousePos.y > minPos.y && 
        ImGui::GetIO().MousePos.y < minPos.y + 24);
        
        if (minHovered) {
            drawList->AddRectFilled(minPos, ImVec2(minPos.x + 24, minPos.y + 24), IM_COL32(190, 35, 75, 255), 5.0f);
            if (ImGui::IsMouseClicked(0)) {
                g_minimized = true;
                glfwSetWindowSize(g_window, g_miniWidth, g_miniHeight);
            }
        } else {
            drawList->AddRectFilled(minPos, ImVec2(minPos.x + 24, minPos.y + 24), IM_COL32(35, 6, 12, 255), 5.0f);
        }
        drawList->AddRect(minPos, ImVec2(minPos.x + 24, minPos.y + 24), IM_COL32(255, 65, 135, 255), 5.0f);
        drawList->AddTriangleFilled(ImVec2(minPos.x + 12, minPos.y + 18),
        ImVec2(minPos.x + 5, minPos.y + 7),
        ImVec2(minPos.x + 19, minPos.y + 7), IM_COL32(255, 65, 135, 255)
        );
        
        ImGui::SetCursorPos(ImVec2(18, 12));
        ImGui::SetWindowFontScale(0.75f);
        ImGui::TextColored(ImVec4(1.0f, 0.2f, 0.6f, 1.0f), "Linux Shitical-Strike 2 External");
        ImGui::SetWindowFontScale(1.0f);
        
        drawList->AddLine(ImVec2(windowPos.x + 18, windowPos.y + 38), 
        ImVec2(windowPos.x + windowWidth - 18, windowPos.y + 38), IM_COL32(190, 35, 35, 80), 2.0f);
        
        ImGui::SetCursorPos(ImVec2(26, 55));
        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 8.0f);
        
        bool wallhack = g_wallhack_enabled;
        if (ImGui::Checkbox(" Wallhack (X-Ray)", &wallhack)) {
            g_wallhack_enabled = wallhack;
        }
        ImGui::PopStyleVar();
        
        ImGui::SetCursorPos(ImVec2(18, windowHeight - 30));
        ImGui::TextColored(ImVec4(0.35f, 0.35f, 0.35f, 0.60f), "Made by iSlavik ");
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(0.2f, 0.9f, 0.2f, 1.0f), "(@islavikfx)");
    }

    ImGui::End();

    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(g_window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    glfwSwapBuffers(g_window);
}


bool Menu::IsRunning() {
    return g_running && !glfwWindowShouldClose(g_window);
}


void Menu::SetWallhackEnabled(bool enabled) {
    g_wallhack_enabled = enabled;
}


bool Menu::IsWallhackEnabled() {
    return g_wallhack_enabled;
}


void Menu::SetVisible(bool visible) {
    if (visible) {
        glfwSetWindowSize(g_window, g_fullWidth, g_fullHeight);
        g_minimized = false;
    } else {
        glfwSetWindowSize(g_window, g_miniWidth, g_miniHeight);
        g_minimized = true;
    }
}


bool Menu::IsVisible() {
    return !g_minimized;
}