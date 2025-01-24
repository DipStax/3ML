function (m3l_create_project_itf proj_name proj_real_name)
    setup_log (${proj_real_name} ${CMAKE_CURRENT_FUNCTION})

    m3l_namespace_list (${proj_name} proj_namespace)
    log (debug "Project namespace: ${proj_namespace}")
    m3l_no_namespace (proj_ns ${proj_namespace})
    log (debug "Project name w/o first namespace: ${proj_ns}")

    set (header_dir "${M3L_ROOT_DIR}/include/M3L/${proj_ns}")
    log (verb "Header files in directory ${header_dir}")

    file (GLOB_RECURSE project_hpp "${header_dir}/**.hpp")
    file (GLOB_RECURSE project_inl "${header_dir}/**.inl")

    list (APPEND project_source ${project_hpp} ${project_inl} ${project_src})
    log (debug "Source file: ${project_source}")

    add_library (${proj_name}
        INTERFACE
            "${project_source}"
    )
    log (info "Created library interface: ${proj_name}")

    pop_log()
endfunction ()

function (m3l_create_project proj_name bin_format)
    string (REPLACE "_" "." proj_real_name ${proj_name})
    setup_log (${proj_real_name} ${CMAKE_CURRENT_FUNCTION})

    set (args ${ARGN})

    if ("${bin_format}" STREQUAL "LIBRARY")
        list (GET args 0 lib_format)
        list (REMOVE_AT args 0 args)

        if ("${lib_format}" STREQUAL "STATIC")
            m3l_create_static_library (${proj_name} ${proj_real_name} ${args})
        elseif ("${lib_format}" STREQUAL "SHARED")
            m3l_create_dynamic_library (${proj_name} ${proj_real_name} ${args})
        else ()
            # error
        endif ()
    elseif ("${bin_format}" STREQUAL "EXECUTABLE")
        list (GET args 0 exe_format)

        if ("${exe_format}" STREQUAL "DEMO")
            list (REMOVE_AT args 0 args)

            m3l_create_exedemo (${proj_name} ${proj_real_name} ${args})
        else ()
            m3l_create_executable (${proj_name} ${proj_real_name} ${args})
        endif ()
    elseif ("${bin_format}" STREQUAL "INTERFACE")
        m3l_create_project_itf (${proj_name} ${proj_real_name} ${args})
    else ()
        # error
    endif ()
    
    pop_log()
endfunction ()

