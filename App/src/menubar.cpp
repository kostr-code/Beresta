#include "../include/menubar.h"

void MenuBar(){
    if(ImGui::BeginMainMenuBar()){
        ImGui::EndMainMenuBar();
    }else{
        // TODO: сделать кастомное исключение

    }
}

void MenuBar(const char** titles){
    if(ImGui::BeginMainMenuBar()){
        for(int i = 0; i < 3; i++){
            MenuBarItem(titles[i]);
        }
        ImGui::EndMainMenuBar();
    }else{
        // TODO: сделать кастомное исключение

    }
}

void MenuBarItem(const char* title){
    if(ImGui::BeginMenu(title)){
        ImGui::EndMenu();
    }else{
        // TODO: сделать кастомное исключение
    }
}