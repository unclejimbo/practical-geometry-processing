find_package(Eigen3 REQUIRED)
find_package(libigl REQUIRED)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(use_libigl main.cpp)

target_link_libraries(use_libigl PRIVATE Eigen3::Eigen igl::core igl::common Threads::Threads)

target_compile_features(use_libigl PRIVATE cxx_std_17)

target_compile_options(use_libigl PRIVATE
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>:
        -pipe -fno-plt -march=native
        $<$<CONFIG:Debug>:-O0 -Wall -Wextra>>
    $<$<CXX_COMPILER_ID:MSVC>:
        $<$<CONFIG:Debug>:/Od /W3 /Zi>>
)

target_compile_definitions(use_libigl PRIVATE
    _USE_MATH_DEFINES
    $<$<CXX_COMPILER_ID:MSVC>:NOMINMAX>
)

set_target_properties(use_libigl PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

add_custom_command(TARGET use_libigl POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/data
        $<TARGET_FILE_DIR:use_libigl>/data
)
