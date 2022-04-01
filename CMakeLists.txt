# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)
set(CMAKE_CXX_STANDARD 17)

# 项目信息
project (REPTILE)
# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(./src DIR_SRCS)
# 指定生成目标
add_executable(main ${DIR_SRCS})
# 添加链接库
target_link_libraries(main curl pthread)
