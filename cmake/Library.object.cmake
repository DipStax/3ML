function (m3l_create_library_itf lib_itf)
    setup_log (${lib_itf} ${CMAKE_CURRENT_FUNCTION})

    set (args ${ARGN})
    
    log (info "Creating interface library: ${lib_itf}")
    add_library (${lib_itf} INTERFACE)
    log (info "Link with configuration: ${args}")
    target_link_libraries (${lib_itf}
        INTERFACE
            M3L_STATIC_LIBRARY
    )
    get_target_property(obj_cd M3L_STATIC_LIBRARY COMPILE_DEFINITIONS)
    get_target_property(itf_cd M3L_STATIC_LIBRARY INTERFACE_COMPILE_DEFINITIONS)
    log (info "library compile definition: M3L_STATIC_LIBRARY ${itf_cd} <> ${obj_cd}")
    get_target_property(obj_cd ${lib_itf} COMPILE_DEFINITIONS)
    get_target_property(itf_cd ${lib_itf} INTERFACE_COMPILE_DEFINITIONS)
    log (info "library compile definition: ${itf_cd} <> ${obj_cd}")

    if ("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
        log (debug "Link with Release configuration")
        target_link_libraries (${lib_itf}
            INTERFACE
                M3L_RELEASE_GLOBAL
        )
    elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
        log (debug "Link with Debug configuration")
        target_link_libraries (${lib_itf}
            INTERFACE
                M3L_DEBUG_GLOBAL
        )
    else ()
        log (error "Build type not supported: ${CMAKE_BUILD_TYPE}")
    endif ()

    target_include_directories(${lib_itf}
        INTERFACE
            ${PROJECT_SOURCE_DIR}/include
    )
    log (info "Interface use include directory: ${PROJECT_SOURCE_DIR}/include")


    pop_log()
endfunction ()

function (m3l_create_library_obj proj_name proj_real_name lib_obj)
    setup_log (${lib_obj} ${CMAKE_CURRENT_FUNCTION})

    set (header_dir "${M3L_ROOT_DIR}/include/M3L/${proj_name}")
    set (source_dir "${M3L_ROOT_DIR}/src/${proj_real_name}")
    log (verb "Header files in directory ${header_dir}")
    log (verb "Source files in directory ${source_dir}")

    file (GLOB_RECURSE project_hpp "${header_dir}/**.hpp")
    file (GLOB_RECURSE project_inl "${header_dir}/**.inl")
    file (GLOB_RECURSE project_src "${source_dir}/**.cpp")
    
    list (APPEND project_source ${project_hpp} ${project_inl} ${project_src})
    log (verb "Source file: ${project_source}")

    add_library (${lib_obj}
        OBJECT
            "${project_source}"
    )

    pop_log()
endfunction ()