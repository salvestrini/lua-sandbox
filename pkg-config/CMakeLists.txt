include(GNUInstallDirs)
include(MacroSetOption)
luasb_set_option(
  LUASB_BUILD_SHARED_LIBS
  TRUE BOOL
  "TRUE to build shared libraries")

if(LUASB_BUILD_SHARED_LIBS)
  luasb_set_option(
    LUASB_INSTALL_PKGCONFIG_FILES TRUE BOOL
    "TRUE to automatically install pkg-config files")
  if(LUASB_INSTALL_PKGCONFIG_FILES)

      configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/lua-sandbox.pc.in"
        "${CMAKE_CURRENT_BINARY_DIR}/lua-sandbox.pc"
        @ONLY)
      install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/lua-sandbox.pc"
        DESTINATION "${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX}/pkgconfig")

#    foreach(luasb_module IN ITEMS all core fs gfx io net sfx ui)
#      configure_file(
#        "${CMAKE_CURRENT_SOURCE_DIR}/luasb-${luasb_module}.pc.in"
#        "${CMAKE_CURRENT_BINARY_DIR}/luasb-${luasb_module}.pc"
#        @ONLY)
#      install(FILES
#        "${CMAKE_CURRENT_BINARY_DIR}/luasb-${luasb_module}.pc"
#        DESTINATION "${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX}/pkgconfig")
#    endforeach()

  endif()
else()
  if(LUASB_INSTALL_PKGCONFIG_FILES)
    message(WARNING "No pkg-config files are provided for static linking (LUASB_INSTALL_PKGCONFIG_FILES will be ignored).")
  endif()
endif()
