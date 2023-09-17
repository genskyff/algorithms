# 创建一个库（例如名为sorting）
add_library(sorting STATIC
    bubble.c
)

# 设置库的公共头文件目录
target_include_directories(sorting PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
