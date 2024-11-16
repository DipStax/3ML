cmake_minimum_required (VERSION 3.10)

list (APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include (cmake/Module.cmake)

set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY lib)
add_compile_options (/Wall /W3 /EHsc)

project(M3L)

if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message ("Setting build type to 'Debug' as none was specified.")
    set (CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
    # Set the possible values of build type for cmake-gui
    set_property (CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif ()

create_library_module (Container INTERFACE)

create_library_module (Maths INTERFACE)

create_library_module (Tool)
target_link_libraries (Tool
    PRIVATE
        Container
        Maths
)

create_library_module (Core)
target_link_libraries (Core
    PRIVATE
        Tool
)

create_library_module (Event)
target_link_libraries (Event
    PRIVATE
        Core
)

create_library_module (Rendering)
target_link_libraries (Rendering
    PRIVATE
        Core
)

set (DEMO_DIRECTORY "${PROJECT_SOURCE_DIR}/demo")

create_app_module (2DRender ${DEMO_DIRECTORY})
target_link_libraries (2DRender
    PRIVATE
        Rendering
)

create_app_module (3DRender ${DEMO_DIRECTORY})
target_link_libraries (3DRender
    PRIVATE
        Rendering
)

create_app_module (SysEvent ${DEMO_DIRECTORY})
target_link_libraries (SysEvent
    PRIVATE
        Event
)