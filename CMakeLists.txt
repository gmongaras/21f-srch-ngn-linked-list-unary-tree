cmake_minimum_required(VERSION 3.16)
project(21f_final_proj_template)

set(CMAKE_CXX_STANDARD 14)

add_executable(21f_final_proj_template main.cpp catch_setup.cpp test.cpp TreeNode.h AVLTree.h myDocument.h DocumentNode.cpp DocumentNode.h WordNode.cpp WordNode.h HashNode.h HashMap.h HashFunction.h Index.h Index.cpp QueryProcessor.cpp QueryProcessor.h porter2_stemmer/porter2_stemmer.cpp porter2_stemmer/porter2_stemmer.h DocumentProcessor.cpp murmur3/MurmurHash3.cpp murmur3/MurmurHash3.h UserInterface.cpp UserInterface.h tokStr.h tokStr.cpp)
target_link_libraries(21f_final_proj_template stdc++fs)