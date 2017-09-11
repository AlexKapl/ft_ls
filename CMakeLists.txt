cmake_minimum_required(VERSION 3.6)
project(ft_ls)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c ft_ls.h ls_process.c ls_print.c ls_sort.c ls_utils.c ls_ultims.c)

add_executable(ft_ls ${SOURCE_FILES})
target_link_libraries(ft_ls ${CMAKE_SOURCE_DIR}/libft/libft.a)