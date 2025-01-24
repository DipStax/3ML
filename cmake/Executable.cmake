function (m3l_create_executable proj_name proj_real_name)
    setup_log (${proj_real_name} ${CMAKE_CURRENT_FUNCTION})
    
    set (exe_obj "_ses_executable_${proj_name}")
    log (info "Runtime session - execution object name: ${exe_obj}")

    m3l_namespace_list (${proj_name} proj_namespace)
    log (debug "Project namespace: ${proj_namespace}")
    m3l_no_namespace (proj_ns ${proj_namespace})
    log (debug "Project name w/o first namespace: ${proj_ns}")

    find_library (eo_exist exe_obj)
    if (NOT eo_exist)
        log (info "Executable object not found")
        log (info "Generating executable object ${exe_obj}")
        m3l_create_executable_obj (proj_ns proj_real_name exe_obj)
        m3l_link_library_itf (proj_ns proj_real_name exe_obj
            M3L_SHARED_LIBRARY
            M3L_EXPORT_LIBRARY
        )
    endif ()

    add_executable (${proj_name}
        PUBLIC
            $<TARGET_OBJECTS:${exe_obj}>
    )
    log (info "Created new executable: ${proj_name} PUBLIC ${exe_obj}")
    target_link_libraries (${proj_name}
        INTERFACE
            ${exe_obj}
    )
    log (info "Link executable to object executable: ${proj_name} INTERFACE ${exe_obj}")
endfunction ()

function (m3l_create_exedemo proj_name proj_real_name)
    setup_log (${proj_real_name} ${CMAKE_CURRENT_FUNCTION})
    
    set (exedemo_obj "_ses_exedemo_${proj_name}")
    log (info "Runtime session - execution demo object name: ${exedemo_obj}")
    
    m3l_namespace_list (${proj_name} proj_namespace)
    log (debug "Project namespace: ${proj_namespace}")
    m3l_no_namespace (proj_ns ${proj_namespace})
    log (debug "Project name w/o first namespace: ${proj_ns}")

    find_library (edo_exist exedemo_obj)
    if (NOT edo_exist)
        log (info "Executable demo object not found")
        log (info "Generating executable demo object ${exedemo_obj}")
        m3l_create_exedemo_obj (proj_ns proj_real_name exedemo_obj)
        m3l_link_library_itf (proj_ns proj_real_name exedemo_obj
            M3L_RELEASE_GLOBAL
            M3L_BIN_EXEC
        )
    endif ()

    add_executable (${proj_name}
        PUBLIC
            $<TARGET_OBJECTS:${exedemo_obj}>
    )
    target_link_libraries (${proj_name}
        INTERFACE
            ${exedemo_obj}
    )
endfunction ()