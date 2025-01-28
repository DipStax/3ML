include (cmake/Utils.cmake)

message ("rebuild: ${CMAKE_BUILD_TYPE} & ${CMAKE_CONFIGURATION_TYPES}")
if (NOT CMAKE_BUILD_TYPE)
    message ("Setting build type to 'debug' as none was specified.")
    set (CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
    set_property (CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS ${CMAKE_CONFIGURATION_TYPES})
endif ()

add_library (M3L_EXPORT_LIBRARY INTERFACE)

target_compile_definitions (M3L_EXPORT_LIBRARY
    INTERFACE
        MMML_EXPORTS
)

add_library (M3L_SHARED_LIBRARY INTERFACE)
add_library (M3L_STATIC_LIBRARY INTERFACE)

target_compile_definitions (M3L_STATIC_LIBRARY
    INTERFACE
        MMML_STATIC
)

add_library (M3L_RELEASE_GLOBAL INTERFACE)
add_library (M3L_DEBUG_GLOBAL INTERFACE)

add_library (M3L_BIN_EXEC INTERFACE)
add_library (M3L_BIN_DEMO INTERFACE)

include (cmake/Executable.cmake)
include (cmake/Executable.object.cmake)
include (cmake/Library.cmake)
include (cmake/Library.object.cmake)
include (cmake/Project.cmake)