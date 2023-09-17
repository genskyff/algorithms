# 创建一个库（例如名为data_structure）
add_library(data_structure STATIC
    linear_list.c
)

# 设置库的公共头文件目录
target_include_directories(data_structure PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
