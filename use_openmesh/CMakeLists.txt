find_package(OpenMesh REQUIRED)

add_executable(use_openmesh main.cpp)

target_include_directories(use_openmesh PRIVATE
    ${OPENMESH_INCLUDE_DIR}
)

target_link_libraries(use_openmesh PRIVATE
    ${OPENMESH_LIBRARIES}
)

target_compile_features(use_openmesh PRIVATE cxx_std_17)

target_compile_options(use_openmesh PRIVATE
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>:
        -pipe -fno-plt -march=native
        $<$<CONFIG:Debug>:-O0 -Wall -Wextra>>
    $<$<CXX_COMPILER_ID:MSVC>:
        $<$<CONFIG:Debug>:/Od /W3 /Zi>>
)

set_target_properties(use_openmesh PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

if(${_FOUND_PREBUILT_LIBS})
    set(OM_BINDIR ${OPENMESH_LIBRARY_DIR}/../bin)
    add_custom_command(TARGET use_openmesh POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<$<CONFIG:Debug>:${OM_BINDIR}/OpenMeshCored.dll>
            $<$<CONFIG:Release>:${OM_BINDIR}/OpenMeshCore.dll>
            $<$<CONFIG:Debug>:${OM_BINDIR}/OpenMeshToolsd.dll>
            $<$<CONFIG:Release>:${OM_BINDIR}/OpenMeshTools.dll>
            $<TARGET_FILE_DIR:use_openmesh>
    )
endif()
add_custom_command(TARGET use_openmesh POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/data
        $<TARGET_FILE_DIR:use_openmesh>/data
)
