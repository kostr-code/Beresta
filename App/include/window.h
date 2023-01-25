#ifndef WINDOW_H
#define WINDOW_H

#include "../include/imgui.h"
#include "../include/imgui_impl_glfw.h"
#include "../include/imgui_impl_opengl3.h"
#include <iostream>
#define GL_SILENCE_DEPRECATION

#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h> // Will drag system OpenGL headers

static void glfw_error_callback(int error, const char *description);

class Window
{
private:
    GLFWwindow *window;
    const char *glsl_version;
    ImVec4 clear_color = ImVec4(0.02f, 0.22f, 0.42f, 1.00f);
    int display_w, display_h;

protected:
    /*! @brief
     * return version of OpenGL
     * GL ES 2.0 + GLSL 100 -> #version 100
     * GL 3.2 + GLSL 150    -> #version 150
     * GL 3.0 + GLSL 130    -> #version 130
    */
    const char *VersionOfOGL();
    /*! @brief
     *  function contained render functions
     *  from glfw3 API
    */
    void Render();
    
public:
    Window();
    Window(GLFWwindow *window);
    void MainLoop();
    ~Window();
};

static void glfw_error_callback(int error, const char *description);

#endif // WINDOW_H