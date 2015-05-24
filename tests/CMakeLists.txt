include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_BINARY_DIR})

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

link_directories(${CMAKE_BINARY_DIR}/lua-sandbox)

add_executable(test test.cc)

target_link_libraries(test luasb)
