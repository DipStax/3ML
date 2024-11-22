cmake_policy(SET CMP0054 NEW)
cmake_policy(SET CMP0076 NEW)





function (module_add_source module_name module_path access m3l_subdir)
    message ("[Function] | Lib ${module_name} > Macro launch: ${module_name} ${module_path} ${access} ${m3l_subdir}")

    if (${m3l_subdir})
        set (mod_include_path "${module_path}/include/M3L/${module_name}")
        set (mod_src_path "${module_path}/src/${module_name}")
        set (mod_include_dir "${module_path}/include/")
    else ()
        set (mod_include_path "${module_path}/${module_name}/include")
        set (mod_src_path "${module_path}/${module_name}/src")
        list (APPEND mod_include_dir "${module_path}/${module_name}/include/" "${PROJECT_SOURCE_DIR}/include/")
    endif ()
    message ("[Function] Mod ${module_name} > Setup - define mod_include_path: ${mod_include_path}")
    message ("[Function] Mod ${module_name} > Setup - define mod_src_path: ${mod_src_path}")
    message ("[Function] Mod ${module_name} > Setup - define mod_include_dir: ${mod_include_dir}")

#########

    file (GLOB_RECURSE module_hpp "${mod_include_path}/**.hpp")
    file (GLOB_RECURSE module_inl "${mod_include_path}/**.inl")
    message ("Mod ${module_name} > Setup - header directory used: ${mod_include_path}")

    file (GLOB_RECURSE module_fsrc "${mod_src_path}/**.cpp")
    message ("Mod ${module_name} > Setup - source directory used: ${mod_src_path}")

    list (APPEND header_group ${module_hpp} ${module_inl})
    list (APPEND module_src ${module_fsrc} ${header_group})
    message ("Mod ${module_name} > Setup - Source file and header merged")

    target_sources(${module_name}
        ${access}
            "${module_src}"
    )
    message ("Mod ${module_name} > Setup - using as source file: ${module_src}")

    target_include_directories (${module_name}
        ${access}
            ${mod_include_dir}
    )
    message ("Mod ${module_name} > Setup - using as header directory: ${mod_include_dir}")
endfunction ()





function (create_library_module module_name)
    message ("[Function] | Lib ${module_name} > Macro launch: ${module_name}")

    set (dft_build SHARED)
    set (dft_access PRIVATE)
    set (dft_path ${PROJECT_SOURCE_DIR})
    set (dft_export True)

######### parameter handling

    set (args ${ARGN})
    list (LENGTH args extra_count)
    message ("[Function] | Lib ${module_name} > Creating library module: ${module_name}")
    message ("[Function] | Lib ${module_name} > Extra parameter length: ${extra_count} ${args}")

    if ("${extra_count}" GREATER "0")
        list (GET args 0 arg_build)
        message ("[Function] Args | Lib ${module_name} > Setup - Default build changing from ${dft_build} to ${arg_build}")
        set (dft_build ${arg_build})
    endif() 
    if ("${extra_count}" GREATER "1")
        list (GET args 1 arg_path)
        message ("[Function] Args | Lib ${module_name} > Setup - Default path changing from ${dft_path} to ${arg_path}")
        set (dft_path ${arg_path})
    endif ()
    if ("${extra_count}" GREATER "2")
        list (GET args 2 arg_axport)
        message ("[Function] Args | Lib ${module_name} > Setup - Default export changing from ${dft_export} to ${arg_axport}")
        set (dft_export ${arg_axport})
    endif ()
    message ("[Function] | Mod ${module_name} > Setup - define dft_build: ${dft_build}")
    message ("[Function] | Mod ${module_name} > Setup - define dft_access: ${dft_access}")
    message ("[Function] | Mod ${module_name} > Setup - define dft_path: ${dft_path}")
    message ("[Function] | Mod ${module_name} > Setup - define dft_export: ${dft_export}")

######### project creation

    if ("${dft_build}" STREQUAL "INTERFACE")
        message ("Lib ${module_name} > Setup - Creating library with source as INTERFACE")
        add_library (${module_name} INTERFACE)
        message ("Lib ${module_name} > Setup - INTERFACE parameter found, changing access to INTERFACE")
        set (dft_access INTERFACE)
    else ()
        message ("Lib ${module_name} > Setup - Creating library with source as ${dft_build}")
        add_library (${module_name} ${dft_build})
    endif ()
    set_target_properties(${module_name} PROPERTIES LINKER_LANGUAGE CXX)

    module_add_source (${module_name} ${dft_path} ${dft_access} True)

######### Compile definition

    if ("${dft_access}" STREQUAL "PRIVATE")
        message ("Lib ${module_name} > Setup - Changed default access from ${dft_access} to PUBLIC")
        set (dft_access PUBLIC)
    endif ()

    message ("Lib ${module_name} > Setup - build: ${dft_build} export: ${dft_export}")
    if (NOT "${dft_build}" STREQUAL "INTERFACE")
        if ("${dft_build}" STREQUAL "STATIC")
            message ("Lib ${module_name} > Setup - Defining export flag: ${dft_access} - MMML_STATIC")
            target_compile_definitions(${module_name} ${dft_access} MMML_STATIC)
            target_compile_definitions(${module_name} ${dft_access} MMML_EXPORTS)
        elseif ("${dft_export}" STREQUAL "True")
            message ("Lib ${module_name} > Setup - Defining ${dft_access} - MMML_EXPORTS flag from argument")
            target_compile_definitions(${module_name} ${dft_access} MMML_EXPORTS)
        endif()
        target_compile_definitions (${module_name} PRIVATE NOMINMAX)
    else ()
        message ("Lib ${module_name} > Setup - No compile definition required for INTERFACE library")
    endif()
endfunction()






function (create_app_module app_name)
    message ("[Function] | App ${app_name} > Macro launch: ${app_name}")
    set (dft_path ${PROJECT_SOURCE_DIR})

######### parameter handling

    set (args ${ARGN})
    list (LENGTH args extra_count)
    message ("[Function] | App ${app_name} > Creating application module: ${app_name}")
    message ("[Function] | App ${app_name} > Extra parameter length: ${extra_count} ${args}")

    if ("${extra_count}" GREATER "0")
        list (GET args 0 arg_path)
        message ("[Function] Args | App ${app_name} > Setup - Default build changing from ${dft_path} to ${arg_path}")
        set (dft_path ${arg_path})
    endif ()
    message ("[Function] | App ${app_name} > Setup - define dft_path: ${dft_path}")
    
######### project creation

    add_executable (${app_name})
    set_target_properties(${app_name} PROPERTIES LINKER_LANGUAGE CXX)
    message ("App ${app_name} > Setup - Created application ${app_name}")

    module_add_source (${app_name} ${dft_path} PRIVATE False)

######### Compile definition

    target_compile_definitions (${app_name} PRIVATE NOMINMAX)
endfunction ()