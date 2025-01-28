cmake_minimum_required (VERSION 3.10)

list (APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set (CMAKE_SHARED_LINKER_FLAGS "-Wl,--export-all-symbols")

# set (CMAKE_MESSAGE_LOG_LEVEL debug)

set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY lib)
set (CMAKE_GENERATOR_PLATFORM x64)

add_compile_options (/Wall /W3 /EHsc)

project(M3L)

set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")

add_compile_definitions (NOMINMAX)

set (M3L_ROOT_DIR "${PROJECT_SOURCE_DIR}")

include (cmake/m3l.cmake)

# m3l_create_project (M3L_Container INTERFACE)
# m3l_create_project (M3L_Event INTERFACE)
# m3l_create_project (M3L_Maths INTERFACE)

# add_library (M3L_itfgroup INTERFACE)

# target_link_libraries (M3L_itfgroup
#     INTERFACE
#         M3L_Container
#         M3L_Event
#         M3L_Maths
# )

m3l_create_project (M3L_Tool LIBRARY STATIC)

# m3l_create_project (M3L_Core LIBRARY SHARED)

# target_link_libraries (M3L_Core
#     INTERFACE
#         M3L_itfgroup
# )

# m3l_create_project (M3L_Rendering LIBRARY SHARED)

# target_link_libraries (M3L_Rendering
#     PUBLIC
#         M3L_Core
# )

# m3l_create_project (M3L_2DRender DEMO)

# target_link_libraries (M3L_2DRender
#     SHARED
#         M3L_2DRender
# )