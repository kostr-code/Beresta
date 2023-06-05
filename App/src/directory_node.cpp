//
// Created by MKD on 05.06.2023.
//

#include "../include/directory_node.h"

void RecursivelyAddDirectoryNodes(directory_node& parentNode, std::filesystem::directory_iterator directoryIterator)
{
    for (const std::filesystem::directory_entry& entry : directoryIterator)
    {
        directory_node& childNode = parentNode.Children.emplace_back();
        childNode.FullPath = entry.path().u8string();
        childNode.FileName = entry.path().filename().u8string();
        if (childNode.IsDirectory = entry.is_directory(); childNode.IsDirectory)
            RecursivelyAddDirectoryNodes(childNode, std::filesystem::directory_iterator(entry));
    }

    auto moveDirectoriesToFront = [](const directory_node& a, const directory_node& b) { return (a.IsDirectory > b.IsDirectory); };
    std::sort(parentNode.Children.begin(), parentNode.Children.end(), moveDirectoriesToFront);
}

directory_node CreateDirectoryNodeTreeFromPath(const std::filesystem::path& rootPath)
{
    directory_node rootNode;
    rootNode.FullPath = rootPath.u8string();
    rootNode.FileName = rootPath.filename().u8string();
    if (rootNode.IsDirectory = std::filesystem::is_directory(rootPath); rootNode.IsDirectory)
        RecursivelyAddDirectoryNodes(rootNode, std::filesystem::directory_iterator(rootPath));

    return rootNode;
}