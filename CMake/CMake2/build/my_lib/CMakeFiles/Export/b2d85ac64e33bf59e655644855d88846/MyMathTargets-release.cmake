#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "MyMath::MyMath" for configuration "Release"
set_property(TARGET MyMath::MyMath APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(MyMath::MyMath PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/MyMath.lib"
  )

list(APPEND _cmake_import_check_targets MyMath::MyMath )
list(APPEND _cmake_import_check_files_for_MyMath::MyMath "${_IMPORT_PREFIX}/lib/MyMath.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
