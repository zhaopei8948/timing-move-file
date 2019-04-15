#ifndef FILE_TOOL_H
#define FILE_TOOL_H
#include <string>


void handleMatchFiles(const char *dir, bool searchSubdirectories, const std::string &pattern,
                      void (*handleCallBack)(const char *path, const char *fileName));
#endif
