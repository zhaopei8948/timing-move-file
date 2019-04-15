#include <windows.h>
#include <iostream>
#include <string>
#include <cstring>
#include <regex>
#include "file_tool.h"
#include "loguru.hpp"


void handleMatchFiles(const char *dir, bool searchSubdirectories, const std::string &pattern,
                      void (*handleCallBack)(const char *path, const char *fileName))
{
    LOG_SCOPE_FUNCTION(INFO);
    HANDLE hFind;
    WIN32_FIND_DATA findData;
    char dirNew[100];
    LOG_F(INFO, "dir is: %s", dir);

    strcpy(dirNew, dir);
    strcat(dirNew, "\\*.*");
    hFind = FindFirstFile(dirNew, &findData);
    if (hFind == INVALID_HANDLE_VALUE) {
        LOG_F(ERROR, "Failed to find first file!");
        return;
    }

    do {
        if (strcmp(findData.cFileName, ".") == 0 || strcmp(findData.cFileName, "..") == 0)
            continue;
        if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            LOG_F(INFO, "%s \t<dir>", findData.cFileName);
            if (searchSubdirectories) {
                strcpy(dirNew, dir);
                strcat(dirNew, "\\");
                strcat(dirNew, findData.cFileName);
                handleMatchFiles(dirNew, true, pattern, handleCallBack);
            }
        } else {
            LOG_F(INFO, "find file is: %s", findData.cFileName);
            handleCallBack(dir, findData.cFileName);
        }
    } while (FindNextFile(hFind, &findData));

    FindClose(hFind);
}
