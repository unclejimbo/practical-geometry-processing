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

            set(_BoostFile ${CMAKE_CURRENT_SOURCE_DIR}/boost-1.70.0-msvc2017-x64.zip)
            set(_BoostUrl http://139.162.111.133:8000/f/648fc05941d0409498e8/?dl=1)
            set(_BoostHash cd8915715e98b34afdf5192ef7899d2bc254aee2cdb915a0aa097a57918067f2)
            set(BOOST_INCLUDEDIR ${CMAKE_CURRENT_SOURCE_DIR}/boost-1.70.0-msvc2017-x64
                CACHE PATH "Boost include directory" FORCE)


            set(_CGALFile ${CMAKE_CURRENT_SOURCE_DIR}/CGAL-4.14-msvc2017-x64.zip)
            set(_CGALUrl http://139.162.111.133:8000/f/239f92285f63449a98fb/?dl=1)
            set(_CGALHash b27b4975858d9587b520e204a033906b03b9851497ef706b91a6ad47ed658645)
            set(CGAL_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/CGAL-4.14-msvc2017-x64/include
                CACHE PATH "CGAL include directory" FORCE)
            set(CGAL_LIBRARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/CGAL-4.14-msvc2017-x64/lib
                CACHE PATH "CGAL debug lib" FORCE)

            set(_EigenFile ${CMAKE_CURRENT_SOURCE_DIR}/Eigen-3.3.5-msvc2017-x64.zip)
            set(_EigenUrl http://139.162.111.133:8000/f/c0144b3e7d3141e0bfa3/?dl=1)
            set(_EigenHash 7ba520fc4fba537e3fb6628f2f44b8dc49baf9fca017e172be398e9cc98d74b9)
            set(Eigen3_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Eigen-3.3.5-msvc2017-x64/share/eigen3/cmake
                CACHE PATH "Eigen3 directory" FORCE)

            set(_libiglFile ${CMAKE_CURRENT_SOURCE_DIR}/libigl-2.1.0-msvc2017-x64.zip)
            set(_libiglUrl http://139.162.111.133:8000/f/db8f732b3bea4cf19983/?dl=1)
            set(_libiglHash 1aa9dbb15496b213cfd878d882a8bdc76ab89a963e3fdaec76a3cfccd3b4f7a0)
            set(_libigl_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libigl-2.1.0-msvc2017-x64/share/libigl/cmake
                CACHE PATH "libigl directory" FORCE)
        endif()

        set(_files ${_OpenMeshFile} ${_BoostFile} ${_CGALFile} ${_EigenFile} ${_libiglFile})
        set(_urls ${_OpenMeshUrl} ${_BoostUrl} ${_CGALUrl} ${_EigenUrl} ${_libiglUrl})
        set(_hashes ${_OpenMeshHash} ${_BoostHash} ${_CGALHash} ${_EigenHash} ${_libiglHash})
        message("Use prebuilt libraries.")
    else()
        set(_FOUND_PREBUILT_LIBS FALSE CACHE INTERNAL "Prebuilt libraries are found")
        set(CMAKE_FIND_PACKAGE_PREFER_CONFIG TRUE PARENT_SCOPE)
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
