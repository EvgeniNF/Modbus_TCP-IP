#-------------------------------------------------------------------------------#
#------------------------- Set minimum version cmake ---------------------------#
cmake_minimum_required(VERSION 3.16)
#-------------------------------------------------------------------------------#
#------------------------------- Set cxx standard ------------------------------#
set(CMAKE_CXX_STANDARD 20)
#-------------------------------------------------------------------------------#
#------------------------------- Set project name ------------------------------#
project(modbus
        VERSION 0.1.0
        DESCRIPTION "Protocol Modbus tcp/ip"
        LANGUAGES CXX)
#-------------------------------------------------------------------------------#
#----------------------------- Add compiler options ----------------------------#
add_compile_options(-Wall -Wextra -Wpedantic)
#-------------------------------------------------------------------------------#
#------------------------------ Add subdirectories -----------------------------#
add_subdirectory(src)
#-------------------------------------------------------------------------------#
#-------------------------------- Add unit tests -------------------------------#
if(TEST)
    enable_testing()
    add_subdirectory(tests)
endif()
#-------------------------------------------------------------------------------#
