function (m3l_create_static_library proj_name proj_real_name)
    setup_log (${proj_real_name} ${CMAKE_CURRENT_FUNCTION})
    
    set (lib_obj "_ses_libobj_${proj_name}")
    set (lib_itf "_ses_libitf_${proj_name}")
    log (info "Runtime session - static library object name: ${lib_obj}")
    
    m3l_namespace_list (${proj_name} proj_namespace)
    log (debug "Project namespace: ${proj_namespace}")
    m3l_no_namespace (proj_ns ${proj_namespace})
    log (debug "Project name w/o first namespace: ${proj_ns}")

    log (info "Static library object not found")
    log (info "Generating library object ${lib_obj}")
    m3l_create_library_obj (${proj_ns} ${proj_real_name} ${lib_obj})

    log (info "Interface library not found")
    log (info "Generating library interface ${lib_itf}")
    m3l_create_library_itf (${lib_itf}
        M3L_STATIC_LIBRARY
    )

    add_library (${proj_name}
        STATIC
            $<TARGET_OBJECTS:${lib_obj}>
    )
    log (info "Created new library: ${proj_name} STATIC ${lib_obj}")
    target_link_libraries (${proj_name}
        INTERFACE
            ${lib_itf}
    )
    log (info "Link library to interface library: ${proj_name} INTERFACE ${lib_itf}")

    get_target_property(obj_cd ${proj_name} COMPILE_DEFINITIONS)
    get_target_property(itf_cd ${proj_name} INTERFACE_COMPILE_DEFINITIONS)
    log (info "library compile definition: ${itf_cd} <> ${obj_cd}")

    pop_log()
endfunction ()

# function (m3l_create_dynamic_library proj_name proj_real_name)
#     setup_log (${proj_real_name} ${CMAKE_CURRENT_FUNCTION})
    
#     set (lib_obj "_ses_libobj_${proj_name}")
#     log (info "Runtime session - execution demo object name: ${lib_obj}")
    
#     m3l_namespace_list (${proj_name} proj_namespace)
#     log (debug "Project namespace: ${proj_namespace}")
#     m3l_no_namespace (proj_ns ${proj_namespace})
#     log (debug "Project name w/o first namespace: ${proj_ns}")

#     find_library (lo_exist ${lib_obj})
#     if (NOT lo_exist)
#         log (info "Static library object not found")
#         log (info "Generating library object ${lib_obj}")
#         m3l_create_library_obj (${proj_ns} ${proj_real_name} ${lib_obj})
#         m3l_link_library_itf (${proj_ns} ${proj_real_name} ${lib_obj}
#             M3L_SHARED_LIBRARY
#             M3L_EXPORT_LIBRARY
#         )
#     endif ()

#     add_library (${proj_name}
#         SHARED
#             $<TARGET_OBJECTS:${lib_obj}>
#     )
#     log (info "Created new library: ${proj_name} SHARED ${lib_obj}")
#     target_link_libraries (${proj_name}
#         INTERFACE
#             ${lib_obj}
#     )
#     log (info "Link library to object library: ${proj_name} INTERFACE ${lib_obj}")
    
#     pop_log()
# endfunction ()