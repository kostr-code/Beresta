//
// Created by MKD on 25.05.2023.
//

#include <fstream>
#include <sstream>
#include <filesystem>
#include "../include/document.h"

document::document(const std::string& path) {
    size_t pos;
    if((pos = path.find_last_of('\\')) == -1) {
        pos = path.find_last_of('/') + 1;
    }
    size_t size = path.size();
    this->name = (char*) malloc(size+1);
    for(int i = 0; i < size; i++){
        this->name[i] = path[pos+i];
    }
    this->name[size] = '\0';
    this->text = read_file(path);
    this->edited = false;

}
ImVector<char> document::getText() {
    ImVector<char> out;
    for(int i = 0; i < this->text_size; i++){
        out.push_back(text[i]);
    }
    return out;
}

char* document::getName() const {
    return name;
}

unsigned long document::getSize() const {
    return this->text_size;
}

char* document::read_file(const std::string &path) {
    this->text_size = std::filesystem::file_size(path);
    std::ifstream f(path);
    f.seekg(0, std::ios::end);
    //size_t size = f.tellg();
    char* s = (char*) malloc(this->text_size);
    f.seekg(0);
    f.read(s, this->text_size); // по стандарту можно в C++11, по факту работает и на старых компиляторах
    return s;
}
