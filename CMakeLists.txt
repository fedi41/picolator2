# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.2.0)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.2.0-a4)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico2_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(picolator2 C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()


# add compiled files subdirectory
add_subdirectory(lib/Config)
add_subdirectory(lib/Infrared)
add_subdirectory(lib/OLED)
add_subdirectory(lib/Icm20948)
add_subdirectory(lib/LCD)
add_subdirectory(lib/Fonts)
add_subdirectory(lib/GUI)
add_subdirectory(examples)



# add header file directory
include_directories(examples)
include_directories(./lib/Config)
include_directories(./lib/GUI)
include_directories(./lib/Icm20948)
include_directories(./lib/LCD)
include_directories(./lib/Infrared)
include_directories(./lib/OLED)


# Add executable. Default name is the project name, version 0.1

add_executable(picolator2 src/main.c )

pico_set_program_name(picolator2 "picolator2")
pico_set_program_version(picolator2 "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(picolator2 1)
pico_enable_stdio_usb(picolator2 1)

# Add the standard library to the build
target_link_libraries(picolator2
        pico_stdlib)

# Add the standard include files to the build
target_include_directories(picolator2 PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
)

# Add any user requested libraries
target_link_libraries(picolator2 examples LCD OLED Infrared Icm20948 GUI Fonts Config pico_stdlib hardware_spi)

pico_add_extra_outputs(picolator2)

