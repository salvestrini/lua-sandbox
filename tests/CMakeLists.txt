include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_BINARY_DIR})

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

link_directories(${CMAKE_BINARY_DIR}/lua-sandbox)

enable_testing()

add_executable(test-01 test-01.cc)

target_link_libraries(test-01 luasb)
target_link_libraries(test-01 dl)

add_test(NAME test-01 COMMAND test-01)