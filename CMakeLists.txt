cmake_minimum_required(VERSION 3.10)
project(eco_pow_cpp)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenSSL REQUIRED)
find_package(CURL REQUIRED)

include_directories(${OPENSSL_INCLUDE_DIR})
include_directories(${CURL_INCLUDE_DIRS})
include_directories(src)

# Enable OpenMP if available
find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

add_executable(eco_pow_cpp src/main.cpp src/eco_pow_advanced.cpp)
target_link_libraries(eco_pow_cpp ${OPENSSL_LIBRARIES} ${CURL_LIBRARIES} OpenMP::OpenMP_CXX)
