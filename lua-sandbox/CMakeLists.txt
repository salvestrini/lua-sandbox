enable_language(CXX)

option(WANT_DEBUG    "Debugging"     ON)
option(WANT_LOGS     "Logs"          ON)

configure_file(config.hh.in config.hh)

include(CheckIncludeFile)
include(CheckSymbolExists)
include(GNUInstallDirs)

set(LUA_VERSION "5.3.0")

#include_directories("${CMAKE_CURRENT_SOURCE_DIR}/lua-${LUA_VERSION}/src")
include_directories("${CMAKE_SOURCE_DIR}/lua-sandbox/lua-${LUA_VERSION}/src")

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_BINARY_DIR})

add_library(luasb SHARED
  lua-${LUA_VERSION}/src/lapi.c
  lua-${LUA_VERSION}/src/lcode.c
  lua-${LUA_VERSION}/src/lctype.c
  lua-${LUA_VERSION}/src/ldebug.c
  lua-${LUA_VERSION}/src/ldo.c
  lua-${LUA_VERSION}/src/ldump.c
  lua-${LUA_VERSION}/src/lfunc.c
  lua-${LUA_VERSION}/src/lgc.c
  lua-${LUA_VERSION}/src/llex.c
  lua-${LUA_VERSION}/src/lmem.c
  lua-${LUA_VERSION}/src/lobject.c
  lua-${LUA_VERSION}/src/lopcodes.c
  lua-${LUA_VERSION}/src/lparser.c
  lua-${LUA_VERSION}/src/lstate.c
  lua-${LUA_VERSION}/src/lstring.c
  lua-${LUA_VERSION}/src/ltable.c
  lua-${LUA_VERSION}/src/ltm.c
  lua-${LUA_VERSION}/src/lundump.c
  lua-${LUA_VERSION}/src/lvm.c
  lua-${LUA_VERSION}/src/lzio.c
  lua-${LUA_VERSION}/src/lauxlib.c
  lua-${LUA_VERSION}/src/lbaselib.c
  lua-${LUA_VERSION}/src/lbitlib.c
  lua-${LUA_VERSION}/src/lcorolib.c
  lua-${LUA_VERSION}/src/ldblib.c
  lua-${LUA_VERSION}/src/liolib.c
  lua-${LUA_VERSION}/src/lmathlib.c
  lua-${LUA_VERSION}/src/loslib.c
  lua-${LUA_VERSION}/src/lstrlib.c
  lua-${LUA_VERSION}/src/ltablib.c
  lua-${LUA_VERSION}/src/lutf8lib.c
  lua-${LUA_VERSION}/src/loadlib.c
  lua-${LUA_VERSION}/src/linit.c

  luasb.cc
  )

install(FILES
  luasb.hh
  DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/lua-sandbox"
  )

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-Wall"   CXX_SUPPORTS_WALL)
CHECK_CXX_COMPILER_FLAG("-Werror" CXX_SUPPORTS_WERROR)
CHECK_CXX_COMPILER_FLAG("-Wundef" CXX_SUPPORTS_WUNDEF)

include(MacroAddCompileFlags)
if("${CXX_SUPPORTS_WALL}")
  MACRO_ADD_COMPILE_FLAGS(luasb "-Wall")
endif()
if("${CXX_SUPPORTS_WERROR}")
  MACRO_ADD_COMPILE_FLAGS(luasb "-Werror")
endif()
if("${CXX_SUPPORTS_WUNDEF}")
  MACRO_ADD_COMPILE_FLAGS(luasb "-Wundef")
endif()

set_source_files_properties(lua.cc PROPERTIES COMPILE_FLAGS -std=c++11)

install(TARGETS luasb DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR})
