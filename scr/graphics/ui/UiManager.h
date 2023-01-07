#ifndef ENGINE_02_UIMANAGER_H
#define ENGINE_02_UIMANAGER_H

#include "../Framebuffer.h"
#include "backends/imgui_impl_opengl3.h"
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"

class UiManager {
private:
    ImGuiIO * io;

    bool onSceneUi = true;

    int windowWidth;
    int windowHeight;

    int textureId;
    int textureWidth;
    int textureHeight;
public:
    UiManager() = default;

    void load(GLFWwindow * window, Framebuffer & frameBuffer);

    ImGuiIO * getIo();
    // returns if mouse is over the scene view
    [[nodiscard]] bool getOnSceneUi() const;

    void update();

    void render();
    void gameWindow();

    void terminate();
};


#endif //ENGINE_02_UIMANAGER_H
