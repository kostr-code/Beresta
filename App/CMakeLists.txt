set(PROJECT_NAME App)

project(
    ${PROJECT_NAME}
    VERSION 0.0.2
    DESCRIPTION "App of this project"
)


set(SOURCE_FILES_IMGUI 
        ./src/imgui.cpp 
        ./src/imgui_demo.cpp
        ./src/imgui_draw.cpp
        ./src/imgui_tables.cpp
        ./src/imgui_widgets.cpp
        ./src/imgui_impl_glfw.cpp
        ./src/imgui_impl_opengl3.cpp)

set(SOURCE_FILE_MY
        ./src/main.cpp
        ./src/window.cpp)



add_executable(${PROJECT_NAME} ${SOURCE_FILES_IMGUI} ${SOURCE_FILE_MY})

set(LIBRARIES "glfw")

find_package(OpenGL REQUIRED)

include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${LIBRARIES})