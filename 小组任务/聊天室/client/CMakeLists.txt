cmake_minimum_required(VERSION 3.0)
project(YourProjectName)

# 添加可执行文件和源代码
add_executable(YourExecutable
    climain.cpp clirun.cpp clit.hpp mainmnue.cpp
    sign.cpp
    Err.cpp
    Massage.cpp
    public.hpp
    User.cpp
)

# 查找并链接 jsoncpp 库
find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONCPP REQUIRED jsoncpp)
target_include_directories(YourExecutable PRIVATE ${JSONCPP_INCLUDE_DIRS})
target_link_libraries(YourExecutable PRIVATE ${JSONCPP_LIBRARIES})

# 查找并链接 hiredis 库
find_package(hiredis REQUIRED)
target_include_directories(YourExecutable PRIVATE ${HIREDIS_INCLUDE_DIRS})
target_link_libraries(YourExecutable PRIVATE ${HIREDIS_LIBRARIES})
