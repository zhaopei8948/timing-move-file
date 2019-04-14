cmake_minimum_required (VERSION 2.8)
project (tmf)
set(SOURCE main.cpp)


include_directories(SYSTEM include)
find_library(LIBGFLAGS libgflags_nothreads_static.a lib)


add_executable(${PROJECT_NAME} ${SOURCE})
target_link_libraries(${PROJECT_NAME} ${LIBGFLAGS} shlwapi.lib)
