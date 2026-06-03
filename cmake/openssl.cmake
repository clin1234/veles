if(WIN32)
  if(NOT OPENSSL_DLL_DIR)
    FIND_PACKAGE(Perl REQUIRED)

    set(OPENSSL_URL "https://github.com/openssl/openssl/releases/download/OpenSSL_1_0_2u/openssl-1.0.2u.tar.gz")
    set(OPENSSL_ARCHIVE_PATH "${CMAKE_CURRENT_BINARY_DIR}/openssl-1.0.2u.tar.gz")
    set(OPENSSL_SHA256 "ecd0c6ffb493dd06707d38b14bb4d8c2288bb7033735606569d8f90f89669d16")
    set(OPENSSL_DIR "${CMAKE_CURRENT_BINARY_DIR}/openssl-1.0.2u")
    file(DOWNLOAD ${OPENSSL_URL} ${OPENSSL_ARCHIVE_PATH} EXPECTED_HASH SHA256=${OPENSSL_SHA256})

    add_custom_command(OUTPUT ${OPENSSL_DIR}
        COMMAND ${CMAKE_COMMAND} -E tar xzf ${OPENSSL_ARCHIVE_PATH}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    )
    if("${CMAKE_SIZEOF_VOID_P}" EQUAL "8")
      add_custom_command(
          OUTPUT "${OPENSSL_DIR}/crypto/buildinf.h"
          COMMAND ${PERL_EXECUTABLE} Configure VC-WIN64A
          WORKING_DIRECTORY ${OPENSSL_DIR}
          DEPENDS ${OPENSSL_DIR}
          COMMENT "Configuring OpenSSL"
          VERBATIM
      )
      add_custom_command(
          OUTPUT "${OPENSSL_DIR}/MINFO"
          COMMAND cmd /c ${OPENSSL_DIR}/ms/do_win64a
          WORKING_DIRECTORY ${OPENSSL_DIR}
          DEPENDS "${OPENSSL_DIR}/crypto/buildinf.h"
          COMMENT "Additional configuration"
          VERBATIM
      )
      add_custom_command(
          OUTPUT "${OPENSSL_DIR}/out32dll/libeay32.dll"
                 "${OPENSSL_DIR}/out32dll/ssleay32.dll"
          COMMAND nmake -f ms/ntdll.mak
          WORKING_DIRECTORY ${OPENSSL_DIR}
          DEPENDS "${OPENSSL_DIR}/MINFO"
          COMMENT "Building OpenSSL"
          VERBATIM
      )
    else()
      add_custom_command(
          OUTPUT "${OPENSSL_DIR}/crypto/buildinf.h"
          COMMAND ${PERL_EXECUTABLE} Configure VC-WIN32
          WORKING_DIRECTORY ${OPENSSL_DIR}
          DEPENDS ${OPENSSL_DIR}
          COMMENT "Configuring OpenSSL"
          VERBATIM
      )
      add_custom_command(
          OUTPUT "${OPENSSL_DIR}/MINFO"
          COMMAND cmd /c "${OPENSSL_DIR}/ms/do_nasm"
          WORKING_DIRECTORY ${OPENSSL_DIR}
          DEPENDS "${OPENSSL_DIR}/crypto/buildinf.h"
          COMMENT "Additional configuration"
          VERBATIM
      )
      add_custom_command(
          OUTPUT "${OPENSSL_DIR}/out32dll/libeay32.dll"
                 "${OPENSSL_DIR}/out32dll/ssleay32.dll"
          COMMAND nmake -f ms/ntdll.mak
          WORKING_DIRECTORY ${OPENSSL_DIR}
          DEPENDS "${OPENSSL_DIR}/MINFO"
          COMMENT "Building OpenSSL"
          VERBATIM
      )
    endif()
    set(OPENSSL_DLL_DIR "${OPENSSL_DIR}/out32dll")
    add_custom_target(openssl
        DEPENDS "${OPENSSL_DIR}/out32dll/libeay32.dll"
                "${OPENSSL_DIR}/out32dll/ssleay32.dll"
    )
  else()
    add_custom_target(openssl)
  endif()
else()
  add_custom_target(openssl)
endif()
