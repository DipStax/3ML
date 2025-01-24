include (cmake/Log.cmake)

function (m3l_namespace_list proj_name dst_name)
    setup_log (${proj_name} ${CMAKE_CURRENT_FUNCTION})

    log (verb "Setting namepsace to property: ${dst_name}")
    string (REPLACE "_" ";" _proj_namespace ${proj_name})
    log (verb "Namespace after replace: ${proj_name} => ${_proj_namespace}")
    list (APPEND dst_list ${_proj_namespace})
    log (verb "Namespace list: ${dst_list}")

    set(${dst_name} ${dst_list} PARENT_SCOPE)
    log (verb "Set: ${dst_name} => ${dst_list}")

    pop_log()
endfunction ()

function (m3l_no_namespace dst_name)
    setup_log (${dst_name} ${CMAKE_CURRENT_FUNCTION})

    set (proj_namespace ${ARGN})
    log (verb "Project namespace: ${proj_namespace}")

    list (REMOVE_AT proj_namespace 0 ${proj_namespace})
    log (verb "After remove: ${proj_namespace}")
    string (JOIN "_" proj_ns ${proj_namespace})

    set(${dst_name} ${proj_ns} PARENT_SCOPE)

    pop_log()
endfunction ()