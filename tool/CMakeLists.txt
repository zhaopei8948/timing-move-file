aux_source_directory(. TOOL_SOURCES)

# 添加头文件信息目录
include_directories(${PROJECT_SOURCE_DIR}/loguru)

# 生成静态库
add_library(tool ${TOOL_SOURCES})
