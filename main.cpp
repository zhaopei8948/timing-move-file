#include <windows.h>
#include <iostream>
#include <ctime>
#include <cstring>
#include <regex>
#include <gflags/gflags.h>
#include "file_tool.h"
#include "loguru.hpp"

static bool ValidateFilePattern(const char *flagName, const std::string &value)
{
    if (value.size() > 0)
        return true;
    return false;
}

static bool ValidateDelaySecond(const char *flagName, int32_t value)
{
    if (value > 0)
        return true;
    return false;
}

static bool ValidateDelayMinute(const char *fiagName, int32_t value)
{
    if (value >=0)
        return true;
    return false;
}

DEFINE_string(srcDir, "", "source director");
DEFINE_string(filePattern, "", "file pattern");
DEFINE_bool(searchSubdirectories, false, "search subdirectories");
DEFINE_string(dstDir, "", "destination director");
DEFINE_int32(delaySecond, 0, "delay seconds execute task");
DEFINE_int32(delayMinute, 0, "delay minutes execute task");

DEFINE_validator(filePattern, &ValidateFilePattern);
DEFINE_validator(delaySecond, &ValidateDelaySecond);
DEFINE_validator(delayMinute, &ValidateDelayMinute);

void handleFile(const char *path, const char *fileName)
{
    char filePath[200];
    char dstFilePath[200];
    strcpy(filePath, path);
    strcat(filePath, "\\");
    strcat(filePath, fileName);

    strcpy(dstFilePath, FLAGS_dstDir.c_str());
    strcat(dstFilePath, "\\");
    strcat(dstFilePath, fileName);
    LOG_F(INFO, "path: %s fileName: %s", path, fileName);
    LOG_F(INFO, "file absolute path is: %s", filePath);
    LOG_F(INFO, "dst file absolute path: %s ", dstFilePath);
    LOG_F(INFO, "filePattern: %s ", FLAGS_filePattern.c_str());

    std::regex fileRegex(FLAGS_filePattern);
    std::string targetFile = fileName;

    if (!std::regex_search(targetFile, fileRegex)) {
        LOG_F(ERROR, "%s not match %s, exit", fileName, FLAGS_filePattern.c_str());
        return;
    }

    if (MoveFile(filePath, dstFilePath)) {
        LOG_F(INFO, "move file %s success!", filePath);
    } else {
        LOG_F(INFO, "move file %s fail!", filePath);
    }
}

void Timeproc(HWND hwnd, UINT message, UINT idTimer, DWORD dwTime)
{
    LOG_SCOPE_FUNCTION(INFO);
    char mbstr[100];
    char dir[100];
    std::time_t now = std::time(nullptr);

    std::strftime(mbstr, sizeof(mbstr), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
    LOG_F(INFO, "now is %s time reaching ...", mbstr);
    strcpy(dir, FLAGS_srcDir.c_str());
    handleMatchFiles(dir, FLAGS_searchSubdirectories, "*", &handleFile);
}

int main(int argc, char *argv[])
{
    loguru::init(argc, argv);
    loguru::add_file("tmf.log", loguru::Append, loguru::Verbosity_MAX);
    LOG_SCOPE_FUNCTION(INFO);
    LOG_F(INFO, "Hello log file!");
    gflags::SetVersionString("1.0");
    gflags::SetUsageMessage("Usage: .\\tmf [option]");
    gflags::ParseCommandLineFlags(&argc, &argv, true);

    LOG_F(INFO, "srcDir is: %s", FLAGS_srcDir.c_str());
    LOG_F(INFO, "filePattern is: %s", FLAGS_filePattern.c_str());
    LOG_F(INFO, "dstDir is: %s", FLAGS_dstDir.c_str());
    LOG_F(INFO, "delaySecond is: %d", FLAGS_delaySecond);
    LOG_F(INFO, "delayMinute is: %d", FLAGS_delayMinute);

    BOOL bRet;
    MSG msg{0};
    UINT uElapse = FLAGS_delaySecond * 1000;
    uElapse += FLAGS_delayMinute * 60 * 1000;

    UINT timerid = SetTimer(nullptr, 0, uElapse, (TIMERPROC)Timeproc);

    while ((bRet= GetMessage(&msg, nullptr, 0, 0)) != 0) {
        if (bRet == -1) {
            
        } else {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    gflags::ShutDownCommandLineFlags();
    return 0;
}
