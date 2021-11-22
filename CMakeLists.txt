cmake_minimum_required(VERSION 3.16)
project(21f_final_proj_template)

set(CMAKE_CXX_STANDARD 14)

add_executable(21f_final_proj_template main.cpp catch_setup.cpp test.cpp TreeNode.h AVLTree.h SearchEngine.h SearchEngine.cpp myDocument.h DocumentNode.cpp DocumentNode.h WordNode.cpp WordNode.h)
target_link_libraries(21f_final_proj_template stdc++fs)