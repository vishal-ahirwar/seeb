
#Auto Genrated CMake file by aura CLI
#None
cmake_minimum_required(VERSION 3.6...3.31)
project(seeb VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
option(STATIC_LINK "Enable static linking" OFF)

# Apply options only for Release mode
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    message(STATUS "Configuring for Release mode: Enabling optimizations")
    add_compile_options(-O3 -march=native -funroll-loops)
endif()
# Apply static linking if enabled
if(STATIC_LINK)
    message(STATUS "Static linking enabled")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")
endif()

set(COMPANY "None")
string(TIMESTAMP CURRENT_YEAR "%Y")
set(COPYRIGHT "Copyright(c) ${CURRENT_YEAR} ${COMPANY}.")

include_directories(src ${CMAKE_BINARY_DIR})
configure_file(res/config.h.in seebconfig.h)

#@find Warning: Do not remove this line

file(GLOB SOURCES "src/*.cxx")
add_executable(${PROJECT_NAME} ${SOURCES})

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
#@link Warning: Do not remove this line

target_include_directories(${PROJECT_NAME} PUBLIC ${JSON_INCLUDE_DIR})
include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VENDOR ${COMPANY})
include(CPack)