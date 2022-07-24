#-------------------------------------------------------------------------------#
#--------------------------------- Set test name -------------------------------#
set(TEST_NAME test_modbus)
#-------------------------------------------------------------------------------#
#------------------------------- Find gtest package ----------------------------#
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip)
FetchContent_MakeAvailable(googletest)
#-------------------------------------------------------------------------------#
#-------------------------- Find additional package ----------------------------#
find_package(Boost COMPONENTS REQUIRED system)

include_directories(${PROJECT_SOURCE_DIR}/include)
#-------------------------------------------------------------------------------#
#--------------------------------- Add source files ----------------------------#
set(SOURCE
        Test.main.cpp
        Test.Buffer.cpp
        Test.Master.cpp
        Test.WriteData.cpp)
#-------------------------------------------------------------------------------#
#--------------------------------- Add executable ------------------------------#
add_executable(${TEST_NAME}
        ${SOURCE})
#-------------------------------------------------------------------------------#
#--------------------------------- Link libraries ------------------------------#
target_link_libraries(${TEST_NAME} PRIVATE
        ${BOOST_LIBRARIES}
        gtest
        Modbus)
#-------------------------------------------------------------------------------#
#--------------------------------- Gtest functions -----------------------------#
include(GoogleTest)
gtest_discover_tests(${TEST_NAME})
#-------------------------------------------------------------------------------#
