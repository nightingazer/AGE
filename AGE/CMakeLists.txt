CMAKE_MINIMUM_REQUIRED(VERSION 3.7)

project(AGE VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED 23)

add_library(age_core STATIC)

target_include_directories(age_core INTERFACE include PUBLIC src vendor/imgui vendor/glm/ vendor/stb_image)

file(GLOB_RECURSE _AGE_CORE_SRCS src/agepch.cpp src/agepch.h  src/Age/*.cpp src/Age/*.h vendor/stb_image/stb_image.cpp vendor/stb_image/stb_image.h)
list(REMOVE_ITEM _AGE_CORE_SRCS ${REMOVE_CMAKE})

file(GLOB _IMGUI_SRCS vendor/imgui/*.cpp vendor/imgui/*.h)

target_sources(age_core PRIVATE ${_AGE_CORE_SRCS} ${_IMGUI_SRCS})
target_precompile_headers(age_core PUBLIC src/agepch.h)

option(AGE_INCLUDE_OPENGL "If ON, OpenGL-specific implementations will be added to the project" ON)
option(AGE_INCLUDE_VULCAN "If ON, Vulcan-specific implementations will be added to the project" OFF)
option(AGE_INCLUDE_DIRECTX "If ON, DirectX-specific implementations will be added to the project" OFF)

set(AGE_RENDER_PLATFORM OPENGL CACHE STRING "Render platform to be used. (OPENGL)")

add_subdirectory(vendor/glm)
add_subdirectory(vendor/spdlog)

target_link_libraries(age_core PUBLIC spdlog glm)

##################################################
#                Figure out OS                   #
##################################################
if (WIN32)
    target_compile_definitions(age_core PUBLIC AGE_OS_WINDOWS)
    message(STATUS "Windows platform")
    set(AGE_OS "WINDOWS")
elseif (UNIX AND NOT APPLE)
    target_compile_definitions(age_core PUBLIC AGE_OS_LINUX)
    message(STATUS "Linux platform")
    set(AGE_OS "LINUX")
endif ()

if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    target_compile_definitions(age_core PUBLIC DEBUG)
    message(STATUS "Debug configuration")
else ()
    target_compile_definitions(age_core PUBLIC NDEBUG)
    message(STATUS "Non-debug configuration")
endif ()

if (${CMAKE_BUILD_TYPE} STREQUAL "Release")
    message(STATUS "Release configuration")
endif ()

##################################################
#           Configure Render Platforms           #
##################################################

# find vulcan
# find directX


########################################
#     WTF!? SHOULD WORK BUT DOESN'T!   #
########################################

#if (DEFINED ENV{WAYLAND_DISPLAY})
#    message(STATUS "Will be using Wayland")
#    set(GLFW_BUILD_WAYLAND ON)
#    set(GLFW_INCLUDE_WAYLAND ON)
#
#    set(GLFW_BUILD_X11 ON)
#    set(GLFW_INCLUDE_X11 ON)
#else ()
#    set(AGE_INCLUDE_WAYLAND OFF)
#endif ()

if (AGE_INCLUDE_OPENGL)
    message(STATUS "Including OpenGl")
    add_subdirectory(vendor/GLFW)

    add_library(age_core_glad STATIC)

    target_link_libraries(age_core PUBLIC glfw ${GLFW_LIBRARIES})

    file(GLOB _IMGUI_BE vendor/imgui/backends/imgui_impl_opengl3* vendor/imgui/backends/imgui_impl_glfw.*)
    file(GLOB _AGE_OPENGL_PLATFORM_SRCS src/Platform/OpenGL/*)
    file(GLOB _AGE_OPENGL_PLATFORM_C_SRCS vendor/GLAD/src/glad.c)

    target_sources(age_core PRIVATE ${_IMGUI_BE} ${_AGE_OPENGL_PLATFORM_SRCS})
    target_sources(age_core_glad PRIVATE ${_AGE_OPENGL_PLATFORM_C_SRCS})

    target_include_directories(age_core PUBLIC vendor/GLFW/include vendor/imgui)
    target_include_directories(age_core_glad PUBLIC vendor/GLAD/include)

    target_compile_definitions(age_core PUBLIC AGE_INCLUDE_OPENGL)

    target_link_libraries(age_core PUBLIC age_core_glad)
endif ()

target_compile_definitions(age_core PUBLIC AGE_RENDER_PLATFORM_${AGE_RENDER_PLATFORM})

#__GLX_VENDOR_LIBRARY_NAME=nvidia;__NV_PRIME_RENDER_OFFLOAD=1


