include_directories(${gtest_SOURCE_DIR}/ include ${gtest_SOURCE_DIR})
include_directories(${thread_pool_SOURCE_DIR}/ include ${thread_pool_SOURCE_DIR})

add_executable(unit_tests
        worker_tests.cpp)

target_link_libraries(unit_tests gtest gtest_main)
target_link_libraries(unit_tests thread_pool)
