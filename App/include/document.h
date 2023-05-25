//
// Created by MKD on 25.05.2023.
//

#include <string>
#include "../include/imgui.h"
#include "../include/imgui_impl_glfw.h"
#include "../include/imgui_impl_opengl3.h"

#ifndef BERESTA_DOCUMENT_H
#define BERESTA_DOCUMENT_H



class document {
private:
    char* name;
    char* text;
    unsigned long text_size{};
    bool edited;

protected:
    char* read_file(const std::string &path);

public:
    explicit document(const std::string& path);
    ImVector<char> getText();
    [[nodiscard]] unsigned long getSize() const;
    [[nodiscard]] char* getName() const;
    void saveFile(ImVector<char> text);


};


#endif //BERESTA_DOCUMENT_H
