#include "../include/window.h"
#include <unistd.h>
#include <cstdio>
#include <functional>

/*
TODO Реалозавть для каждого желаемого виджет класс-обертку для удобной рабты над ним
     Для этого составить список необходимых виджетов и примерный внешний вид приложения
*/
static void glfw_error_callback(int error, const char *description) {
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

Window::Window() {
//    this->open_documents.push_back(
//            document(R"(../../App/src/main.cpp)"));
//    this->open_documents.push_back(
//            document(R"(../../App/include/document.h)"));
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        std::cout << "glfw window can not be init" << std::endl;
    this->VersionOfOGL();
    this->window = glfwCreateWindow(1280, 720, u8"Береста", NULL, NULL);
    glfwMakeContextCurrent(this->window);
    glfwSwapInterval(1);
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void) io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.Fonts->Clear();
    io.Fonts->AddFontFromFileTTF("../../App/recources/fonts/UbuntuMono-B.ttf", 14.0f, NULL,
                                 io.Fonts->GetGlyphRangesCyrillic());

    io.Fonts->Build();
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();
    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(this->window, true);
    ImGui_ImplOpenGL3_Init(this->glsl_version);
    while (!glfwWindowShouldClose(window)) {
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
        //ImGui::ShowDemoWindow();

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
        {
            RenderMenuBar();

            ImGui::Begin("Проект", nullptr, ImGuiWindowFlags_NoCollapse);
            RecursivelyDisplayDirectoryNode(this->root_node);
            /*if(ImGui::TreeNode("Start")){

                ImGui::TreePop();
            }*/

            ImGui::End();
            ImGui::Begin("Редактор", nullptr, ImGuiWindowFlags_NoCollapse);
            RenderTextField();
            ImGui::End();

            // For this demo we are using ImVector as a string container.
            // Note that because we need to store a terminating zero character, our size/capacity are 1 more
            // than usually reported by a typical string class.
        }
        // Rendering
        this->Render();
        glfwSwapBuffers(this->window);
    }
}

Window::~Window() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
}

const char *Window::VersionOfOGL() {
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

void Window::Render() {
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


void Window::RenderMenuBar() {
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu(u8"Файл")) {
            if (ImGui::MenuItem(u8"Создать файл")) {}
            if (ImGui::MenuItem(u8"Открыть файл")) {}
            ImGui::Separator();
            if (ImGui::MenuItem(u8"Сохранить")) {}
            if (ImGui::MenuItem(u8"Сохранить как")) {}
            ImGui::Separator();
            if (ImGui::MenuItem(u8"Создать папку")) {}
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu(u8"Инструменты")) {
            if (ImGui::MenuItem(u8"Открыть в кодировке")) {}
            if (ImGui::MenuItem(u8"Сохранить в кодировке")) {}  // Disabled item
            ImGui::Separator();
            if (ImGui::MenuItem(u8"Найти")) {}
            if (ImGui::MenuItem(u8"Заменить")) {}
            if (ImGui::MenuItem(u8"Рефактор")) {}
            ImGui::Separator();
            if (ImGui::BeginMenu(u8"Вид")) {
                if (ImGui::MenuItem(u8"Полный экран")) {}
                if (ImGui::MenuItem(u8"Только файл")) {}
                if (ImGui::BeginMenu(u8"Сплит")) {
                    if (ImGui::MenuItem(u8"2 горизонтально")) {}
                    if (ImGui::MenuItem(u8"2 вертикально")) {}
                    if (ImGui::MenuItem(u8"Сетка 2х2")) {}
                    ImGui::EndMenu();
                }
                ImGui::EndMenu();
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu(u8"Помощь")) {
            if (ImGui::MenuItem(u8"О приложении")) {}
            if (ImGui::MenuItem(u8"Документация")) {}
            if (ImGui::MenuItem(u8"Сайт")) {}
            if (ImGui::MenuItem(u8"Форум")) {}
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

void Window::RenderTextField() {
    /*
    TODO: Необходимо переделать так,
        чтобы последний символ не съедался при редактировании
     */

    ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_Reorderable
                                     | ImGuiTabBarFlags_AutoSelectNewTabs;
    ImGuiInputTextFlags flags = ImGuiInputTextFlags_AllowTabInput;
    ImVector<char *> names;
    ImVector<bool> opened;
    for(auto &doc: open_documents){
        names.push_back(doc.getName());
        opened.push_back(true);
    }
    if (ImGui::BeginTabBar("Редактор", tab_bar_flags)) {
        for (int i = 0; i < open_documents.size(); i++) {
            if (opened[i] && ImGui::BeginTabItem(open_documents[i].getName(), &opened[i] ,ImGuiTabItemFlags_None)) {
                /*if(!opened[i]){
                    open_documents.erase(&open_documents[i]);
                    continue;
                }*/
                RenderInputField(open_documents[i].getText(), true);
                //ImGui::Text("This is the %s tab!", name);
                ImGui::EndTabItem();
            }
        }
        ImGui::EndTabBar();
    }
}

void Window::RenderInputField(ImVector<char> text, bool change) {
    struct Funcs
    {
        static int MyResizeCallback(ImGuiInputTextCallbackData* data)
        {
            if (data->EventFlag == ImGuiInputTextFlags_CallbackResize)
            {
                ImVector<char>* my_str = (ImVector<char>*)data->UserData;
                IM_ASSERT(my_str->begin() == data->Buf);
                my_str->resize(data->BufSize); // NB: On resizing calls, generally data->BufSize == data->BufTextLen + 1
                data->Buf = my_str->begin();
            }
            return 0;
        }
        static bool MyInputTextMultiline(const char* label, ImVector<char>* my_str, const ImVec2& size = ImVec2(0, 0), ImGuiInputTextFlags flags = 0)
        {
            IM_ASSERT((flags & ImGuiInputTextFlags_CallbackResize) == 0);
            return ImGui::InputTextMultiline(label, my_str->begin(), (size_t)my_str->size(), size, flags | ImGuiInputTextFlags_CallbackResize , Funcs::MyResizeCallback, (void*)my_str);
        }
    };
    static ImVector<char> my_str;
    if (my_str.empty() || change)
        my_str = text;
    Funcs::MyInputTextMultiline("##MyStr", &my_str, ImVec2(-FLT_MIN, -FLT_MIN));

}

void Window::RecursivelyDisplayDirectoryNode(const directory_node& parentNode)
{
    ImGui::PushID(&parentNode);
    if (parentNode.IsDirectory)
    {
        if (ImGui::TreeNodeEx(parentNode.FileName.c_str(), ImGuiTreeNodeFlags_SpanFullWidth))
        {
            for (const directory_node& childNode : parentNode.Children)
                RecursivelyDisplayDirectoryNode(childNode);
            ImGui::TreePop();
        }
    }
    else
    {
        if(ImGui::IsItemClicked()){
            open_documents.push_back(document(parentNode.FullPath));
        }
        if (ImGui::TreeNodeEx(parentNode.FileName.c_str(), ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_SpanFullWidth))
        {
            //open_documents.push_back(document(parentNode.FullPath));
        }
    }
    ImGui::PopID();
}
