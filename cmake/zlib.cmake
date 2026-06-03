# zlib
find_package(ZLIB)

if(ZLIB_FOUND)
  # Only to satisfy dependencies
  add_custom_target(zlib)
else()
  include(ExternalProject)
  # An external project for zlib
  set(ZLIB_SOURCE  "${CMAKE_CURRENT_BINARY_DIR}/zlib-src")
  set(ZLIB_BUILD   "${CMAKE_CURRENT_BINARY_DIR}/zlib")
  set(ZLIB_INSTALL "${CMAKE_CURRENT_BINARY_DIR}/prefix")
  set(ZLIB_FILE "https://zlib.net/zlib-1.3.2.tar.xz")
  set(ZLIB_HASH "SHA256=d7a0654783a4da529d1bb793b7ad9c3318020af77667bcae35f95d0e42a792f3")

  if(CMAKE_CFG_INTDIR STREQUAL ".")
    set(ZLIB_BUILD_TYPE ${CMAKE_BUILD_TYPE})
  else()
    set(ZLIB_BUILD_TYPE ${CMAKE_CFG_INTDIR})
  endif()

  ExternalProject_Add(
      zlib
      DOWNLOAD_DIR ${CMAKE_CURRENT_BINARY_DIR}
      SOURCE_DIR ${ZLIB_SOURCE}
      BINARY_DIR ${ZLIB_BUILD}
      INSTALL_DIR ${ZLIB_INSTALL}
      URL ${ZLIB_FILE}
      URL_HASH ${ZLIB_HASH}
      PATCH_COMMAND ${CMAKE_COMMAND} -E remove "<SOURCE_DIR>/zconf.h"
      CMAKE_CACHE_ARGS
      -DCMAKE_CXX_FLAGS:STRING=${CMAKE_CXX_FLAGS}
      -DCMAKE_C_FLAGS:STRING=${CMAKE_C_FLAGS}
      -DCMAKE_BUILD_TYPE:STRING=${ZLIB_BUILD_TYPE}
      ${ZLIB_EXTRA_ARGS}
      CMAKE_ARGS
      -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
  )

  set(ZLIB_INCLUDE_DIRS "${ZLIB_INSTALL}/include/")
  set(ZLIB_INCLUDES "${ZLIB_INCLUDE_DIRS}/zconf.h" "${ZLIB_INCLUDE_DIRS}/zlib.h")

  if(MSVC)
    set(ZLIB_LIBRARIES "${ZLIB_INSTALL}/lib/zlibstatic$<$<CONFIG:Debug>:d>.lib")
  endif()
  if(UNIX)
    set(ZLIB_LIBRARIES "${ZLIB_INSTALL}/lib/libz.a")
  endif()
endif()

include_directories(${ZLIB_INCLUDE_DIRS})
