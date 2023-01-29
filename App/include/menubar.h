#ifndef MENUBAR_H
#define MENUBAR_H

#include "../include/imgui.h"
#include "../include/imgui_impl_glfw.h"
#include "../include/imgui_impl_opengl3.h"
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h> // Will drag system OpenGL headers

void MenuBarItem(const char* title);
void MenuBar();
void MenuBar(const char** titles);

#endif //MENUBAR_H