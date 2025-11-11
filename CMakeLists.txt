cmake_minimum_required(VERSION 3.14)
project(BookRoom VERSION 1.0.0 LANGUAGES CXX)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

enable_testing()

# 编译选项
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(-g -O0 -Wall -Wextra)
else()
    add_compile_options(-O3 -DNDEBUG)
endif()

# 自动下载和构建 GTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

# 设置为 ON 自动将 GTest 添加到构建
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)

# 自动下载 nlohmann/json - 使用 Git 方式更可靠
FetchContent_Declare(
  nlohmann_json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG        v3.11.2
)

# 同时下载多个依赖
FetchContent_MakeAvailable(googletest nlohmann_json)

# 递归查找所有源文件
file(GLOB_RECURSE SOURCE_FILES 
    "src/*.cpp"
    "src/*.c"
    "src/*.cc"
)

# 递归查找所有头文件（用于显示在 IDE 中）
file(GLOB_RECURSE HEADER_FILES 
    "include/*.hpp"
    "include/*.h"
    "src/*.hpp" 
    "src/*.h"
)

# 创建核心库
add_library(core_lib ${SOURCE_FILES} ${HEADER_FILES})

# 包含头文件路径
target_include_directories(core_lib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# 关键：链接 nlohmann_json 到核心库
target_link_libraries(core_lib
    PUBLIC
        nlohmann_json::nlohmann_json
)

# 添加主程序
add_executable(main_app 
    src/main.cpp
)

# 链接主程序到核心库
target_link_libraries(main_app 
    PRIVATE 
        core_lib
)

# 添加头文件搜索路径
target_include_directories(main_app 
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# 添加测试可执行文件
add_executable(run_tests
    test/test_jsondb.cpp
)

# 链接测试可执行文件
target_link_libraries(run_tests 
    PRIVATE 
        core_lib           # 链接你的核心库
        GTest::gtest       # 使用 GTest 的 CMake 目标
        GTest::gtest_main  # 使用 GTest 的 CMake 目标
)

# 包含头文件路径
target_include_directories(run_tests
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_test(NAME JsonDatabaseTests COMMAND run_tests)


# 添加测试发现
include(GoogleTest)
gtest_discover_tests(run_tests
    EXTRA_ARGS "--gtest_output=xml:${CMAKE_BINARY_DIR}/test_results.xml"
)