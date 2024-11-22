include (cmake/Log.cmake)

function (create_module_interface module_name module_real_name root_dir)
    setup_log (${module_real_name} ${CMAKE_CURRENT_FUNCTION})

    add_library (${module_name} INTERFACE)
    log (info "Created INTERFACE module")
    set_target_properties(${module_name} PROPERTIES LINKER_LANGUAGE CXX)
    
    set (header_dir "${root_dir}/include/M3L/${module_real_name}")
    file (GLOB_RECURSE module_hpp "${header_dir}/**.hpp")
    file (GLOB_RECURSE module_inl "${header_dir}/**.inl")
    list (APPEND module_source ${module_hpp} ${module_inl})
    log (debug "Query header file in directory ${header_dir}")
    log (verbose "Source file: ${module_source}")

    target_sources (${module_name}
        INTERFACE
            ${module_source}
    )
    target_include_directories (${module_name}
        INTERFACE
            ${header_dir}
    )
    log (info "Add include directory: ${header_dir}")
endfunction()


function (create_module_standalone module_name module_real_name root_dir)
    set (module_name "${module_name}_SA")
    setup_log (${module_name} ${CMAKE_CURRENT_FUNCTION})

    add_library (${module_name} STATIC)
    log (info "Created STATIC module")
    set_target_properties (${module_name} PROPERTIES LINKER_LANGUAGE CXX)

    set (header_dir "${root_dir}/include/M3L/${module_real_name}")
    set (source_dir "${root_dir}/src/${module_real_name}")
    file (GLOB_RECURSE module_hpp "${header_dir}/**.hpp")
    file (GLOB_RECURSE module_inl "${header_dir}/**.inl")
    file (GLOB_RECURSE module_src "${source_dir}/**.cpp")

    list (APPEND module_source ${module_hpp} ${module_inl} ${module_src})
    log (debug "Query header file in directory ${header_dir}")
    log (debug "Query source file in directory ${source_dir}")
    log (verbose "Source file: ${module_source}")

    target_sources(${module_name}
        PRIVATE
            "${module_source}"
    )
    target_include_directories (${module_name}
        PUBLIC
            ${header_dir}
    )
    log (info "Add include directory: ${header_dir}")

    target_compile_definitions (${module_name} PRIVATE MMML_STATIC)
endfunction ()

function (create_module_shared module_name module_real_name root_dir)
    create_module_standalone (${module_name} ${module_real_name} ${root_dir})
    set (module_name_sa "${module_name}_SA")

    setup_log (${module_name} ${CMAKE_CURRENT_FUNCTION})

    add_library(${module_name} SHARED)
    log (info "Created SHARED module")
    set_target_properties(${module_name} PROPERTIES LINKER_LANGUAGE CXX)

    target_link_libraries (${module_name}
        STATIC
            ${module_name_sa}
    )
    log (info "Linked static submodule: ${module_name_sa}")
    
    target_compile_definitions (${module_name} PRIVATE MMML_EXPORTS)
    log (info "MMML_EXPORTS defined")
endfunction ()

function (create_module_executable module_name module_real_name root_dir)
    add_executable (${module_name})
    set_target_properties(${module_name} PROPERTIES LINKER_LANGUAGE CXX)

endfunction ()

function (create_module module_name build root_dir)
    setup_log (${module_name} ${CMAKE_CURRENT_FUNCTION})

    string (REPLACE "_" "." module_real_name ${module_name})

    log (info "Creating module...")
    log (debug "Name: ${module_name}")
    log (debug "Real name: ${module_real_name}")
    log (debug "Root dir: ${root_dir}")

    if ("${build}" STREQUAL "interface")
        create_module_interface (${module_name} ${module_real_name} ${root_dir})
    elseif ("${build}" STREQUAL "standalone")
        create_module_standalone (${module_name} ${module_real_name} ${root_dir})
    elseif ("${build}" STREQUAL "shared")
        create_module_shared (${module_name} ${module_real_name} ${root_dir})
    elseif ("${build}" STREQUAL "executable")
        create_module_executable (${module_name} ${module_real_name} ${root_dir})
    endif ()
endfunction ()


function (link_module module_name access)
    setup_log (${module_name} ${CMAKE_CURRENT_FUNCTION})
    set (module_name_sa "${module_name}_SA")

    set (args ${ARGN})
    list (LENGTH args extra_count)
    log (verbose "Linking ${extra_count} module(s)")
    math(EXPR extra_count ${extra_count}-1)





    
    
    if ("${access}" STREQUAL "interface")
        set(access PRIVATE)
        log (debug "Set link access to INTERFACE")
    elseif ("${access}" STREQUAL "standalone")
        set(access PRIVATE)
        log (debug "Set link access to STATIC")

    elseif ("${access}" STREQUAL "shared")
        set(access PUBLIC)
        log (debug "Set link access to PUBLIC")
    endif ()


    set (target_module ${module_name})
    
    if (TARGET ${module_name})
        get_target_property(target_type ${module_name} TYPE)

        if(target_type STREQUAL "SHARED_LIBRARY")
            log (debug "From shared module look for standalone: ${target_module}_SA")
            set (target_module "${target_module}_SA")
        elseif (NOT target_type STREQUAL "STATIC_LIBRARY")
            log (error "Unsupported target type: ${target_type}")
        endif()
    elseif (TARGET ${module_name_sa})
        set (target_module "${target_module}_SA")
    elseif (NOT TARGET ${module_name_sa})
        log (error "Standalone module not found: ${module_name} - ${module_name_sa}")
    endif ()




    log (info "Linking ${target_module} ${access} ${args}")
    target_link_libraries(${target_module}
        ${access}
            ${args}
    )
    # foreach (index RANGE ${extra_count})
    #     list (GET args ${index} target_module)
    #     log (verbose "${index} Linking ${target_module} module with access ${access}")
    #     target_link_libraries(${module_name}
    #         "${access}" "${target_module}"
    #     )
    # endforeach()
    
endfunction()
