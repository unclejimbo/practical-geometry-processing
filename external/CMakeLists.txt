set(USE_PREBUILT_LIBS ON CACHE BOOL "Use prebuilt libs")

if (${USE_PREBUILT_LIBS})
    if(${MSVC_TOOLSET_VERSION})
        if (${MSVC_TOOLSET_VERSION} GREATER_EQUAL 141)
            set(_FOUND_PREBUILT_LIBS TRUE CACHE BOOL INTERNAL)

            set(_OpenMeshFile ${CMAKE_CURRENT_SOURCE_DIR}/OpenMesh-8.0-msvc2017-x64.zip)
            set(_OpenMeshUrl http://139.162.111.133:8000/f/2d2d03d51b1d4131b692/?dl=1)
            set(_OpenMeshHash 747af1b86c744e66768948965a8835c24a41d0d6ac19d4d68c42b5b77e07697e)
            set(OPENMESH_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/OpenMesh-8.0-msvc2017-x64/include
                CACHE PATH "OpenMesh include directory" FORCE)
            set(OPENMESH_LIBRARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/OpenMesh-8.0-msvc2017-x64/lib
                CACHE PATH "OpenMesh library directory" FORCE)
        endif()

        set(_files ${_OpenMeshFile})
        set(_urls ${_OpenMeshUrl})
        set(_hashes ${_OpenMeshHash})
        message("Use prebuilt libraries.")
    else()
        set(_FOUND_PREBUILT_LIBS FALSE CACHE BOOL INTERNAL)
        message("Prebuilt libraries for your compiler is not supported.")
    endif()

    if (${_FOUND_PREBUILT_LIBS})
        ## download and extract prebuilt dependencies
        list(LENGTH _files _len)
        math(EXPR _stop "${_len} - 1")
        foreach(_i RANGE ${_stop})
            list(GET _files ${_i} _file)
            list(GET _urls ${_i} _url)
            list(GET _hashes ${_i} _hash)
            if(NOT EXISTS ${_file})
                message("Downloading ${_file}...")
                file(DOWNLOAD ${_url} ${_file}
                    EXPECTED_HASH SHA256=${_hash}
                    SHOW_PROGRESS
                )
            endif()
            string(REGEX REPLACE "\\.[^.]*$" "" _path ${_file})
            message(${_path})
            if(NOT EXISTS ${_path})
                message("Extracting ${_file}...")
                execute_process(
                    COMMAND ${CMAKE_COMMAND} -E tar xzf ${_file}
                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                )
            endif()
        endforeach()
    endif()
endif()
