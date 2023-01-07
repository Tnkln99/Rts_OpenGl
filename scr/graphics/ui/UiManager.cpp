#include "UiManager.h"
#include "GLFW/glfw3.h"

void UiManager::load(GLFWwindow *window, Framebuffer & frameBuffer) {
    textureId = frameBuffer.getTexture();
    textureHeight = frameBuffer.getTextureHeight();
    textureWidth = frameBuffer.getTextureWidth();


    glfwGetWindowSize(window, &windowWidth, &windowHeight);
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO & io = ImGui::GetIO();

    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigWindowsMoveFromTitleBarOnly = true;

    this->io = &io;

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 450 core");
    // Setup Dear ImGui style
    ImGui::StyleColorsClassic();
}

ImGuiIO *UiManager::getIo() {
    return io;
}

bool UiManager::getOnSceneUi() const {
    return onSceneUi;
}

void UiManager::update() {
    // feed inputs to dear imgui, start new frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void UiManager::render() {
    //ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

    //gameWindow();

    //ImGui::ShowDemoWindow();


    // Render dear imgui into screen
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UiManager::gameWindow() {
    ImGui::Begin("Scene Window");

    //std::cout<<ImGui::GetCursorScreenPos().x<<" "<<ImGui::GetCursorScreenPos().y<<std::endl;

    onSceneUi = ImGui::IsWindowHovered();

    ImGui::GetWindowDrawList()->AddImage(
            (void*)textureId, ImVec2(ImGui::GetCursorScreenPos()),
            ImVec2(ImGui::GetCursorScreenPos().x + textureWidth, ImGui::GetCursorScreenPos().y + textureHeight), ImVec2(0, 1), ImVec2(1, 0)
    );

    ImGui::End();
}

void UiManager::terminate() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
