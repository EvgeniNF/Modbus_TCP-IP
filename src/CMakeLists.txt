#-------------------------------------------------------------------------------#
#------------------------------ Set library name -------------------------------#
set(LIB_NAME Modbus)
#-------------------------------------------------------------------------------#
#------------------------------- Print message ---------------------------------#
message("-- LIB_NAME = ${LIB_NAME}")
message("-- SOURCE_DIR = ${CMAKE_CURRENT_SOURCE_DIR}")
message("-- BINARY_DIR = ${CMAKE_CURRENT_BINARY_DIR}")
#-------------------------------------------------------------------------------#
#----------------------------- Set cxx standard --------------------------------#
set(CMAKE_CXX_STANDARD 20)
#-------------------------------------------------------------------------------#
#-------------------------- Find additional package ----------------------------#
find_package(Boost COMPONENTS REQUIRED system)
#-------------------------------------------------------------------------------#
#------------------------------- Set include path ------------------------------#
set(LIB_PATH ${PROJECT_SOURCE_DIR}/include)
#-------------------------------------------------------------------------------#
#-------------------------------- Set HEADER files -----------------------------#
set(HEADERS
        ${LIB_PATH}/Buffer.hpp
        ${LIB_PATH}/functions.hpp
        ${LIB_PATH}/Connection.hpp
        ${LIB_PATH}/modbus/Master.hpp
        ${LIB_PATH}/error_codes.hpp
        ${LIB_PATH}/modbus/Result.hpp
        ${LIB_PATH}/ReadBuffer.hpp
        ${LIB_PATH}/WriteBuffer.hpp)
#-------------------------------------------------------------------------------#
#-------------------------------- Set SOURCE files -----------------------------#
set(SOURCES
        Master.cpp
        Buffer.cpp
        ReadBuffer.cpp
        WriteBuffer.cpp)
#-------------------------------------------------------------------------------#
#---------------------------------- Add library --------------------------------#
add_library(${LIB_NAME} SHARED
        ${HEADERS}
        ${SOURCES})
#-------------------------------------------------------------------------------#
#---------------------------- Target definitions -------------------------------#
target_link_libraries(${LIB_NAME} PRIVATE
        ${BOOST_LIBRARIES})

target_include_directories(${LIB_NAME} PRIVATE
        ${LIB_PATH})

target_include_directories(${LIB_NAME} PUBLIC
        ${LIB_PATH}/modbus)
#-------------------------------------------------------------------------------#
#---------------------------- Install properties -------------------------------#
install(DIRECTORY ${LIB_PATH}/modbus
        DESTINATION include)

install(TARGETS ${LIB_NAME}
        EXPORT export_${LIB_NAME}
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)
#-------------------------------------------------------------------------------#
