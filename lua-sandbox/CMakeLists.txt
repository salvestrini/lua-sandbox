enable_language(CXX)

include(CheckIncludeFile)
include(CheckSymbolExists)
include(GNUInstallDirs)

CHECK_INCLUDE_FILE(execinfo.h HAVE_EXECINFO_H)
if(HAVE_EXECINFO_H)
  CHECK_SYMBOL_EXISTS(backtrace         execinfo.h HAVE_BACKTRACE)
  CHECK_SYMBOL_EXISTS(backtrace_symbols execinfo.h HAVE_BACKTRACE_SYMBOLS)
endif()

CHECK_INCLUDE_FILE(regex.h HAVE_REGEX_H)
if(HAVE_REGEX_H)
  CHECK_SYMBOL_EXISTS(regexec  regex.h HAVE_REGEXEC)
  CHECK_SYMBOL_EXISTS(regcomp  regex.h HAVE_REGCOMP)
  CHECK_SYMBOL_EXISTS(regerror regex.h HAVE_REGERROR)
  CHECK_SYMBOL_EXISTS(regfree  regex.h HAVE_REGFREE)
endif()

set(LUASB_LIBRARIES "")

set(LUASB_INCLUDES "" PARENT_SCOPE)

include_directories(${LUASB_INCLUDES})

option(WANT_DEBUG    "Debugging"     ON)
option(WANT_LOGS     "Logs"          ON)

configure_file(config.hh.in config.hh)

#if(CMAKE_COMPILER_IS_GNUCXX)
#  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")
#endif()

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_BINARY_DIR})

add_library(luasb SHARED
  luasb.cc
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

target_link_libraries(luasb ${LUASB_LIBRARIES})

install(TARGETS luasb DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR})
