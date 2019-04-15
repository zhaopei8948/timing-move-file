aux_source_directory(. LOGURU_SOURCES)

# 生成静态库
add_library(loguru ${LOGURU_SOURCES})
