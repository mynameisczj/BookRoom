cmake_minimum_required(VERSION 3.14)
project(BookRoom VERSION 1.0.0 LANGUAGES CXX)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

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
  # 或者使用 Git（二选一）：
  # GIT_REPOSITORY https://github.com/google/googletest.git
  # GIT_TAG        v1.14.0
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

# 设置为 ON 自动将 GTest 添加到构建
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# 添加主程序
add_executable(main_app 
    src/main.cpp
)

# 添加头文件搜索路径
target_include_directories(main_app 
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# 添加测试可执行文件
add_executable(run_tests
    test/test_main.cpp
)

# 链接 GTest 库
target_link_libraries(run_tests 
    PRIVATE 
        gtest_main
)

# 包含头文件路径
target_include_directories(run_tests
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# 启用测试并注册
enable_testing()
add_test(NAME AllTests COMMAND run_tests)

# 可选：添加测试发现（需要 CMake 3.10+）
include(GoogleTest)
gtest_discover_tests(run_tests
    EXTRA_ARGS "--gtest_output=xml:${CMAKE_BINARY_DIR}/test_results.xml"
)