# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})


file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/testfiles/test_1.txt
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
 
# Link runTests with what we want to test and the GTest and pthread library
add_executable(runTests tridiagonal_test.cpp)
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)







#include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
#add_subdirectory(googletest-main)


#add_executable(tridiagonal_test tridiagonal_test.cpp) 
#add_test(NAME tridiagonal_test COMMAND tridiagonal_test.cpp)
#target_link_libraries(tridiagonal_test SLAE gtest gtest_main) 