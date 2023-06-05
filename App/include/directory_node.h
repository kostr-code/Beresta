//
// Created by MKD on 05.06.2023.
//

#ifndef BERESTA_DIRECTORY_NODE_H
#define BERESTA_DIRECTORY_NODE_H


#include <string>
#include <vector>
#include <filesystem>

struct directory_node
{
    std::string FullPath;
    std::string FileName;
    std::vector<directory_node> Children;
    bool IsDirectory;
};
void RecursivelyAddDirectoryNodes(directory_node& parentNode, std::filesystem::directory_iterator directoryIterator);
directory_node CreateDirectoryNodeTreeFromPath(const std::filesystem::path& rootPath);



#endif //BERESTA_DIRECTORY_NODE_H
