cmake_minimum_required (VERSION 2.8)

# 添加c++11支持
# add_compile_options(-std=c++11)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Werror -Wall -Wextra -pedantic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
# 项目名称
project(tmf)
# 查找当关目录下所有源文件
aux_source_directory(. SOURCE)
# 添加tool子目录
add_subdirectory(tool)
add_subdirectory(loguru)

# 添加头文件信息目录
include_directories(${PROJECT_SOURCE_DIR}/include
  ${PROJECT_SOURCE_DIR}/tool
  ${PROJECT_SOURCE_DIR}/loguru
)
# 查找gflags库
find_library(LIBGFLAGS libgflags_nothreads_static.a lib)

# 生成目录
add_executable(${PROJECT_NAME} ${SOURCE})
# 添加链接库
target_link_libraries(${PROJECT_NAME}
  loguru
  tool
  ${LIBGFLAGS}
  shlwapi.lib
)
