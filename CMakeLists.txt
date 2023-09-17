cmake_minimum_required(VERSION 3.10)
project(MyProject)

# 设置编译选项
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

# 添加编译选项，这是可选的
add_compile_options(-Wall -Wextra -Wpedantic)

# 将src目录下的源代码添加到项目中
add_subdirectory(src)

# 将examples目录下的源代码添加到项目中
add_subdirectory(examples)

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/target)
