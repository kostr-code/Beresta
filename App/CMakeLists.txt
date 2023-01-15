project(App VERSION 0.1.0)

set(PROJECT_NAME App)

project(
    ${PROJECT_NAME}
    VERSION 0.0.1
    DESCRIPTION "App of this project"
)


set(SOURCE_FILES 
        ./src/main.cpp 
        ./src/imgui.cpp 
        ./src/imgui_demo.cpp
        ./src/imgui_draw.cpp
        ./src/imgui_tables.cpp
        ./src/imgui_widgets.cpp
        ./src/imgui_impl_glfw.cpp
        ./src/imgui_impl_opengl3.cpp)



add_executable(${PROJECT_NAME} ${SOURCE_FILES})

set(LIBRARIES "glfw")

find_package(OpenGL REQUIRED)

include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${LIBRARIES})