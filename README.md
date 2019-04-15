# 使用的第三方库

## 使用Google的gflags来进行参数解析
gflags地址：https://github.com/gflags/gflags

## 使用loguru来记录日志
loguru地址: https://github.com/emilk/loguru

## 源码编译
```
git clone https://github.com/zhaopei8948/timing-move-file
cd timing-move-file
md build
cmake -G"MinGW Makefiles" ..\
make

.\tmf --help #查看帮助信息

移动文件后缀名为txt跟ceb3的文件从文件1到文件2, 每隔10秒执行一次
.\tmf --delaySecond=10 --srcDir=C:\share\1 --searchSubdirectories=false --dstDir=C:\share\2 --filePattern="(.*\.txt|.*\.ceb3)"
```
