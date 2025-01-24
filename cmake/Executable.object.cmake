# function (m3l_link_library_itf proj_name proj_real_name lib_obj)
#     setup_log (${lib_obj} ${CMAKE_CURRENT_FUNCTION})

#     set (args ${ARGN})

#     log (info "Link with configuration: ${args}")
#     target_link_libraries (
#         INTERFACE
#             ${args}
#     )

#     if ("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
#         log (info "Link with Realse configuration")
#         target_link_libraries (
#             INTERFACE
#                 M3L_RELEASE_GLOBAL
#         )
#     elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "debug")
#         log (info "Link with debug configuration")
#         target_link_libraries (
#             INTERFACE
#                 M3L_debug_GLOBAL
#         )
#     else ()
#         # error
#     endif ()
# endfunction ()

# function (m3l_create_exedemo_obj proj_name proj_real_name exe_obj)
#     setup_log (${exe_obj} ${CMAKE_CURRENT_FUNCTION})

#     set (header_dir "${M3L_ROOT_DIR}/demo/M3L.${proj_name}/include/")
#     set (source_dir "${M3L_ROOT_DIR}/demo/M3L.${proj_name}/src")
#     log (verb "Header files in directory ${header_dir}")
#     log (verb "Source files in directory ${source_dir}")

#     file (GLOB_RECURSE project_hpp "${header_dir}/**.hpp")
#     file (GLOB_RECURSE project_inl "${header_dir}/**.inl")
#     file (GLOB_RECURSE project_src "${source_dir}/**.cpp")

#     list (APPEND project_source ${project_hpp} ${project_inl} ${project_src})
#     log (verb "Sources file use: ${project_source}")

#     add_executable (${exe_obj}
#         OBJECT
#             "${project_source}"
#     )
#     log (info "Created object executable ${exe_obj}")
# endfunction ()