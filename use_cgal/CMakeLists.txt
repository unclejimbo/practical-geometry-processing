find_package(Boost REQUIRED)
find_package(CGAL REQUIRED)

set(CGAL_DONT_OVERRIDE_CMAKE_FLAGS TRUE CACHE BOOL
    "Force GGAL to maintain CMAKE_*_FLAGS"
)
set(CGAL_DO_NOT_WARN_ABOUT_CMAKE_BUILD_TYPE TRUE CACHE BOOL
    "Disable CGAL's build type warning"
)

add_executable(use_cgal main.cpp)

# the exported target of prebuilt CGAL doesn't work well
if(${_FOUND_PREBUILT_LIBS})
    target_include_directories(use_cgal PRIVATE ${Boost_INCLUDE_DIRS} ${CGAL_INCLUDE_DIR})
    target_link_libraries(use_cgal PRIVATE ${CGAL_LIBRARIES})
else()
    target_link_libraries(use_cgal PRIVATE CGAL::CGAL)
endif()

target_compile_features(use_cgal PRIVATE cxx_std_17)

target_compile_options(use_cgal PRIVATE
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>:
        -pipe -fno-plt -march=native
        $<$<CONFIG:Debug>:-O0 -Wall -Wextra>>
    $<$<CXX_COMPILER_ID:MSVC>:
        $<$<CONFIG:Debug>:/Od /W3 /Zi>>
)

target_compile_definitions(use_cgal PRIVATE
    _USE_MATH_DEFINES
    $<$<CXX_COMPILER_ID:MSVC>:NOMINMAX>
)

set_target_properties(use_cgal PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

if(${_FOUND_PREBUILT_LIBS})
    set(CGAL_BINDIR ${CGAL_LIBRARY_DIR}/../bin)
    add_custom_command(TARGET use_cgal POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<$<CONFIG:Debug>:${CGAL_BINDIR}/CGAL-vc140-mt-gd-4.14.dll>
            $<$<CONFIG:Release>:${CGAL_BINDIR}/CGAL-vc140-mt-4.14.dll>
            $<$<CONFIG:Debug>:${CGAL_BINDIR}/CGAL_Core-vc140-mt-gd-4.14.dll>
            $<$<CONFIG:Release>:${CGAL_BINDIR}/CGAL_Core-vc140-mt-4.14.dll>
            $<TARGET_FILE_DIR:use_cgal>
    )
endif()
add_custom_command(TARGET use_cgal POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/data
        $<TARGET_FILE_DIR:use_cgal>/data
)
