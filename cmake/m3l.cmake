include (cmake/Utils.cmake)

if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message ("Setting build type to 'debug' as none was specified.")
    set (CMAKE_BUILD_TYPE debug CACHE STRING "Choose the type of build." FORCE)
    # Set the possible values of build type for cmake-gui
    set_property (CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "debug" "Release")
endif ()

add_library (M3L_EXPORT_LIBRARY INTERFACE)
add_library (M3L_IMPORT_LIBRARY INTERFACE)

add_library (M3L_SHARED_LIBRARY INTERFACE)
add_library (M3L_STATIC_LIBRARY INTERFACE)

add_library (M3L_RELEASE_GLOBAL INTERFACE)
add_library (M3L_debug_GLOBAL INTERFACE)

add_library (M3L_BIN_EXEC INTERFACE)
add_library (M3L_BIN_DEMO INTERFACE)

include (cmake/Executable.cmake)
include (cmake/Executable.object.cmake)
include (cmake/Library.cmake)
include (cmake/Library.object.cmake)
include (cmake/Project.cmake)