#
# Try to find CGAL
# Once done this will define
#
# CGAL_FOUND           - system has CGAL
# CGAL_INCLUDE_DIR     - the CGAL include directories
# CGAL_LIBRARIES       - Link these to use CGAL
#

if(NOT CGAL_FOUND)
  # Hardcoded search paths
  set(SEARCH_PATHS
    "C:\\ProgramFiles\\CGAL-4.14"
    "${CGAL_LIBRARY_DIR}"
  )

  find_path(CGAL_INCLUDE_DIR Kernel_traits.h
    PATHS ${SEARCH_PATHS}
    PATH_SUFFIXES include
  )

  find_library(CGAL_LIBRARY_DEBUG
    NAMES CGAL-vc140-mt-gd-4.14.lib
    PATHS ${SEARCH_PATHS}
    PATH_SUFFIXES lib
  )

  find_library(CGAL_LIBRARY_RELEASE
    NAMES CGAL-vc140-mt-4.14.lib
    PATHS ${SEARCH_PATHS}
    PATH_SUFFIXES lib
  )

  find_library(CGAL_CORE_LIBRARY_DEBUG
    NAMES CGAL_Core-vc140-mt-gd-4.14.lib
    PATHS ${SEARCH_PATHS}
    PATH_SUFFIXES lib
  )

  find_library(CGAL_CORE_LIBRARY_RELEASE
    NAMES CGAL_Core-vc140-mt-4.14.lib
    PATHS ${SEARCH_PATHS}
    PATH_SUFFIXES lib
  )

  include(SelectLibraryConfigurations)
  select_library_configurations(CGAL)
  select_library_configurations(CGAL_CORE)

  set(CGAL_LIBRARIES ${CGAL_LIBRARY} ${CGAL_CORE_LIBRARY})

  include(FindPackageHandleStandardArgs)
  find_package_handle_standard_args(
    CGAL DEFAULT_MSG CGAL_LIBRARIES CGAL_INCLUDE_DIR
  )

  if(CGAL_LIBRARY_RELEASE)
    get_filename_component(_CGAL_LIBRARY_DIR ${CGAL_LIBRARY_RELEASE} PATH)
  else()
    get_filename_component(_CGAL_LIBRARY_DIR ${CGAL_LIBRARY_DEBUG} PATH)
  endif()
  set (CGAL_LIBRARY_DIR "${_CGAL_LIBRARY_DIR}" CACHE PATH "The directory where the CGAL libraries can be found.")

  mark_as_advanced(CGAL_LIBRARY_DEBUG CGAL_LIBRARY_RELEASE CGAL_CORE_LIBRARY_DEBUG CGAL_CORE_LIBRARY_RELEASE CGAL_LIBRARY_DIR)

endif()
