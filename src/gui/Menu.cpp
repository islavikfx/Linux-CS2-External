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
static int g_fullWidth = 240;
static int g_fullHeight = 140;
static int g_miniWidth = 80;
static int g_miniHeight = 30;
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
    style.WindowBorderSize = 3.0f;
    style.WindowPadding = ImVec2(15, 15);
    style.ItemSpacing = ImVec2(10, 10);
    style.FramePadding = ImVec2(6, 4);
    
    ImVec4* colors = style.Colors;
    colors[ImGuiCol_WindowBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.92f);
    colors[ImGuiCol_Border] = ImVec4(0.9f, 0.3f, 0.9f, 1.0f);
    colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    colors[ImGuiCol_CheckMark] = ImVec4(1.0f, 0.2f, 0.2f, 1.0f);
    colors[ImGuiCol_FrameBg] = ImVec4(0.2f, 0.2f, 0.2f, 0.8f);
    
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
    
    ImGui::Begin("Main", nullptr, 
                 ImGuiWindowFlags_NoTitleBar | 
                 ImGuiWindowFlags_NoResize | 
                 ImGuiWindowFlags_NoMove | 
                 ImGuiWindowFlags_NoCollapse | 
                 ImGuiWindowFlags_NoSavedSettings);

    ImDrawList* drawList = ImGui::GetWindowDrawList();
    ImVec2 windowPos = ImGui::GetWindowPos();
    float windowWidth = ImGui::GetWindowWidth();
    float windowHeight = ImGui::GetWindowHeight();
    
    if (g_minimized) {
        std::string text = "OPEN";
        float textWidth = ImGui::CalcTextSize(text.c_str()).x;
        
        ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
        ImGui::SetCursorPosY((windowHeight - ImGui::GetTextLineHeight()) * 0.5f);
        ImGui::TextColored(ImVec4(0.9f, 0.3f, 0.9f, 1.0f), "%s", text.c_str());
        
        if (ImGui::IsMouseClicked(0) && 
            ImGui::GetIO().MousePos.x > windowPos.x && 
            ImGui::GetIO().MousePos.x < windowPos.x + windowWidth &&
            ImGui::GetIO().MousePos.y > windowPos.y && 
            ImGui::GetIO().MousePos.y < windowPos.y + windowHeight) {
            g_minimized = false;
            glfwSetWindowSize(g_window, g_fullWidth, g_fullHeight);
        }
        
    } else {
        ImVec2 closePos(windowPos.x + windowWidth - 35, windowPos.y + 5);
        ImVec2 minusPos(windowPos.x + windowWidth - 60, windowPos.y + 5);
        
        bool minusHovered = (ImGui::GetIO().MousePos.x > minusPos.x && 
                             ImGui::GetIO().MousePos.x < minusPos.x + 18 &&
                             ImGui::GetIO().MousePos.y > minusPos.y && 
                             ImGui::GetIO().MousePos.y < minusPos.y + 18);
        
        if (minusHovered) {
            drawList->AddRectFilled(minusPos, ImVec2(minusPos.x + 18, minusPos.y + 18), 
                                    IM_COL32(150, 50, 50, 255), 4);
            if (ImGui::IsMouseClicked(0)) {
                g_minimized = true;
                glfwSetWindowSize(g_window, g_miniWidth, g_miniHeight);
            }
        } else {
            drawList->AddRect(minusPos, ImVec2(minusPos.x + 18, minusPos.y + 18), 
                             IM_COL32(255, 80, 80, 255), 4);
        }
        drawList->AddLine(ImVec2(minusPos.x + 4, minusPos.y + 9), 
                         ImVec2(minusPos.x + 14, minusPos.y + 9), 
                         IM_COL32(255, 80, 80, 255), 2.0f);
        
        bool closeHovered = (ImGui::GetIO().MousePos.x > closePos.x && 
                             ImGui::GetIO().MousePos.x < closePos.x + 18 &&
                             ImGui::GetIO().MousePos.y > closePos.y && 
                             ImGui::GetIO().MousePos.y < closePos.y + 18);
        
        if (closeHovered) {
            drawList->AddRectFilled(closePos, ImVec2(closePos.x + 18, closePos.y + 18), 
                                    IM_COL32(150, 50, 50, 255), 4);
            if (ImGui::IsMouseClicked(0)) {
                g_running = false;
            }
        } else {
            drawList->AddRect(closePos, ImVec2(closePos.x + 18, closePos.y + 18), 
                             IM_COL32(255, 80, 80, 255), 4);
        }
        drawList->AddLine(ImVec2(closePos.x + 4, closePos.y + 4), 
                         ImVec2(closePos.x + 14, closePos.y + 14), 
                         IM_COL32(255, 80, 80, 255), 2.0f);
        drawList->AddLine(ImVec2(closePos.x + 14, closePos.y + 4), 
                         ImVec2(closePos.x + 4, closePos.y + 14), 
                         IM_COL32(255, 80, 80, 255), 2.0f);
        
        ImGui::SetWindowFontScale(0.8f);
        
        std::string title = "Linux CS2 by @islavikfx";
        ImGui::SetCursorPosX(15);
        ImGui::SetCursorPosY(8);
        ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 1.0f), "%s", title.c_str());
        
        ImGui::SetWindowFontScale(1.0f);
        
        ImVec2 lineStart(windowPos.x + 3, windowPos.y + 32);
        ImVec2 lineEnd(windowPos.x + windowWidth - 3, windowPos.y + 32);
        drawList->AddLine(lineStart, lineEnd, IM_COL32(255, 80, 80, 255), 2.0f);
        
        ImGui::SetCursorPosY(45);
        ImGui::SetCursorPosX(20);
        
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(8, 6));
        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 4.0f);
        
        ImGui::Checkbox(" Wallhack", &g_wallhack_enabled);
        
        ImGui::PopStyleVar(2);
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