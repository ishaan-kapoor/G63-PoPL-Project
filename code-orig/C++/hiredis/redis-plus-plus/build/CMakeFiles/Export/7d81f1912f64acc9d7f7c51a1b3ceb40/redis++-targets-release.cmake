#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "redis++::redis++_static" for configuration "Release"
set_property(TARGET redis++::redis++_static APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(redis++::redis++_static PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libredis++.a"
  )

list(APPEND _cmake_import_check_targets redis++::redis++_static )
list(APPEND _cmake_import_check_files_for_redis++::redis++_static "${_IMPORT_PREFIX}/lib/libredis++.a" )

# Import target "redis++::redis++" for configuration "Release"
set_property(TARGET redis++::redis++ APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(redis++::redis++ PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libredis++.1.3.10.dylib"
  IMPORTED_SONAME_RELEASE "@rpath/libredis++.1.dylib"
  )

list(APPEND _cmake_import_check_targets redis++::redis++ )
list(APPEND _cmake_import_check_files_for_redis++::redis++ "${_IMPORT_PREFIX}/lib/libredis++.1.3.10.dylib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
