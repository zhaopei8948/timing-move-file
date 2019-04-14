#include <Windows.h>
#include <iostream>
#include <ctime>
#include <gflags/gflags.h>

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
DEFINE_string(dstDir, "", "destination director");
DEFINE_int32(delaySecond, 0, "delay seconds execute task");
DEFINE_int32(delayMinute, 0, "delay minutes execute task");

DEFINE_validator(filePattern, &ValidateFilePattern);
DEFINE_validator(delaySecond, &ValidateDelaySecond);
DEFINE_validator(delayMinute, &ValidateDelayMinute);

void Timeproc(HWND hwnd, UINT message, UINT idTimer, DWORD dwTime)
{
    char mbstr[100];
    std::time_t now = std::time(nullptr);

    std::strftime(mbstr, sizeof(mbstr), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
    std::cout << "now is : " << mbstr << " ";
    std::cout << "time reaching ... " << FLAGS_filePattern
              << " " << FLAGS_delaySecond << std::endl;
}

int main(int argc, char *argv[])
{
    gflags::SetVersionString("1.0");
    gflags::SetUsageMessage("Usage: .\\tmf [option]");
    gflags::ParseCommandLineFlags(&argc, &argv, true);

    std::cout << "srcDir is: " << FLAGS_srcDir << std::endl;
    std::cout << "filePattern is: " << FLAGS_filePattern << std::endl;
    std::cout << "dstDir is: " << FLAGS_dstDir << std::endl;
    std::cout << "delaySecond is: " << FLAGS_delaySecond << std::endl;
    std::cout << "delayMinute is: " << FLAGS_delayMinute << std::endl;

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
