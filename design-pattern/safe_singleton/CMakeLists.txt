# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)

# 项目信息
project (safe_singleton)

# 库文件目录
link_directories(/usr/local/Cellar/boost/1.66.0/lib)

# 添加头文件
include_directories(.)

# 指定生成目标
add_executable(safe_singleton main.cpp)

# 添加链接库
target_link_libraries(safe_singleton pthread boost_thread-mt boost_system)

# 调试选项
# set(CMAKE_BUILD_TYPE "Debug")
# set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
# set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O2 -Wall")
