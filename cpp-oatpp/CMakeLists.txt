cmake_minimum_required(VERSION 3.16)

project(cpp_api LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(oatpp 1.4.0 CONFIG REQUIRED)

add_executable(cpp-api src/App.cpp)
target_include_directories(cpp-api PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(cpp-api PRIVATE oatpp::oatpp)

if(UNIX)
  target_link_libraries(cpp-api PRIVATE pthread)
endif()

enable_testing()

add_executable(cpp-api-tests test/Tests.cpp)
target_include_directories(cpp-api-tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_CURRENT_SOURCE_DIR}/test)
target_link_libraries(cpp-api-tests PRIVATE oatpp::oatpp oatpp::oatpp-test)

if(UNIX)
  target_link_libraries(cpp-api-tests PRIVATE pthread)
endif()

add_test(NAME cpp-api-tests COMMAND cpp-api-tests)
