#include "../include/imgui.h"
#include "../include/imgui_impl_glfw.h"
#include "../include/imgui_impl_opengl3.h"
#include <iostream>
#define GL_SILENCE_DEPRECATION

#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h> // Will drag system OpenGL headers

static void glfw_error_callback(int error, const char* description);

class Window{
private:
    GLFWwindow* window;

public:
    Window();
    Window(GLFWwindow* window);
    void MainLoop();
    ~Window();
};

static void glfw_error_callback(int error, const char* description);
