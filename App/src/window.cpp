#include "../include/window.h"

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
    this->window = glfwCreateWindow(1280, 720, "Beresta", NULL, NULL);
    glfwMakeContextCurrent(this->window);
    glfwSwapInterval(1);
        IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
 
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(this->window, true);
    ImGui_ImplOpenGL3_Init(this->glsl_version); 
    
}

Window::Window(GLFWwindow* window){
    this->window = window;
}

void Window::MainLoop(){
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
                if (ImGui::BeginMenu("File")){
                    ImGui::EndMenu();
                }
                if (ImGui::BeginMenu("Edit")){
                    if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
                    if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
                    ImGui::Separator();
                    if (ImGui::MenuItem("Cut", "CTRL+X")) {}
                    if (ImGui::MenuItem("Copy", "CTRL+C")) {}
                    if (ImGui::MenuItem("Paste", "CTRL+V")) {}
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
