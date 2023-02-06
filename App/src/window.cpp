#include "../include/window.h"
#include <unistd.h>
#include <stdio.h>

/*
TODO Реалозавть для каждого желаемого виджет класс-обертку для удобной рабты над ним
     Для этого составить список необходимых виджетов и примерный внешний вид приложения
*/
static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

Window::Window(){
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        std::cout << "glfw window can not be init" << std::endl;
    this->VersionOfOGL();
    this->window = glfwCreateWindow(1280, 720, u8"Береста", NULL, NULL);
    glfwMakeContextCurrent(this->window);
    glfwSwapInterval(1);
        IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.Fonts->Clear();
    io.Fonts->AddFontFromFileTTF("../../App/recources/fonts/UbuntuMono-B.ttf", 14.0f, NULL, io.Fonts->GetGlyphRangesCyrillic());

    io.Fonts->Build();
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(this->window, true);
    ImGui_ImplOpenGL3_Init(this->glsl_version); 
    while (!glfwWindowShouldClose(window))
    {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
        {
            if (ImGui::BeginMainMenuBar()){
                if (ImGui::BeginMenu(u8"Файл")){
                    if(ImGui::MenuItem(u8"Создать файл")) {}
                    if(ImGui::MenuItem(u8"Открыть файл")) {}
                    ImGui::Separator();
                    if(ImGui::MenuItem(u8"Сохранить")) {}
                    if(ImGui::MenuItem(u8"Сохранить как")) {}
                    ImGui::Separator();
                    if(ImGui::MenuItem(u8"Создать папку")) {}
                    ImGui::EndMenu();
                }
                if (ImGui::BeginMenu(u8"Инструменты")){
                    if (ImGui::MenuItem(u8"Открыть в кодировке")) {}
                    if (ImGui::MenuItem(u8"Сохранить в кодировке")) {}  // Disabled item
                    ImGui::Separator();
                    if (ImGui::MenuItem(u8"Найти")) {}
                    if (ImGui::MenuItem(u8"Заменить")) {}
                    if (ImGui::MenuItem(u8"Рефактор")) {}
                    ImGui::Separator();
                    if (ImGui::BeginMenu(u8"Вид")) {
                        if(ImGui::MenuItem(u8"Полный экран")) {}
                        if(ImGui::MenuItem(u8"Только файл")) {}
                        if(ImGui::BeginMenu(u8"Сплит")) {
                            if(ImGui::MenuItem(u8"2 горизонтально")) {}
                            if(ImGui::MenuItem(u8"2 вертикально")) {}
                            if(ImGui::MenuItem(u8"Сетка 2х2")) {}
                            ImGui::EndMenu();
                        }
                        ImGui::EndMenu();
                    }
                    ImGui::EndMenu();
                }
                if (ImGui::BeginMenu(u8"Помощь")){
                    if (ImGui::MenuItem(u8"О приложении")) {}
                    if (ImGui::MenuItem(u8"Документация")) {}
                    if (ImGui::MenuItem(u8"Сайт")) {}
                    if (ImGui::MenuItem(u8"Форум")) {}
                    ImGui::EndMenu();
                    }
                ImGui::EndMainMenuBar();
            }    
            
        }
        // Rendering
        this->Render();
        glfwSwapBuffers(this->window);
    }
}

Window::~Window(){
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
}

const char* Window::VersionOfOGL(){
    #if defined(IMGUI_IMPL_OPENGL_ES2)
    // GL ES 2.0 + GLSL 100
        this->glsl_version = "#version 100";
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
        glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
    #elif defined(__APPLE__)
    // GL 3.2 + GLSL 150
        this->glsl_version = "#version 150";
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
    #else
    // GL 3.0 + GLSL 130
        this->glsl_version = "#version 130";
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
    #endif
    return glsl_version;
}

void Window::Render(){
    ImGui::Render();
    glfwGetFramebufferSize(this->window, &this->display_w, &this->display_h);
    glViewport(0, 0, this->display_w, this->display_h);
    glClearColor(
        this->clear_color.x * this->clear_color.w, 
        this->clear_color.y * this->clear_color.w, 
        this->clear_color.z * this->clear_color.w, 
        this->clear_color.w
        );
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
