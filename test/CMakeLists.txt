# 创建一个可执行文件（例如名为example_linear_list）
add_executable(example_linear_list d_linear_list.c)

# 链接到data_structure库
target_link_libraries(example_linear_list PRIVATE data_structure)

# 创建另一个可执行文件（例如名为example_bubble）
add_executable(example_bubble s_bubble.c)

# 链接到sorting库
target_link_libraries(example_bubble PRIVATE sorting)
