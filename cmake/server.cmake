set(SERVER_DIR "${CMAKE_CURRENT_BINARY_DIR}/veles-server")
set(SERVER_OUTPUT_STARTUP_SCRIPT_FILE "${SERVER_DIR}/srv.py")

add_custom_target(
    copy-server-files ALL
    COMMAND cmake -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/python" "${CMAKE_CURRENT_BINARY_DIR}/python"
)

add_custom_command(
    OUTPUT ${SERVER_OUTPUT_STARTUP_SCRIPT_FILE}
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_CURRENT_BINARY_DIR}/python/srv.py"
    "${SERVER_OUTPUT_STARTUP_SCRIPT_FILE}"
    COMMENT "Copying server script"
)

if(WIN32)
  if("${CMAKE_SIZEOF_VOID_P}" EQUAL "8")
    set(BASEPYEXE py.exe -3)
    if(NOT EMBED_PYTHON_ARCHIVE_PATH)
      set(EMBED_PYTHON_URL "https://www.python.org/ftp/python/3.14.5/python-3.14.5-embed-amd64.zip")
      set(EMBED_PYTHON_ARCHIVE_PATH "${CMAKE_CURRENT_BINARY_DIR}/python-3.14.5-embed-amd64.zip")
      set(EMBED_PYTHON_SHA256 "ab8d1b0cc087c20d4c32c0e4fcf7d0c733a95da12cedc6d63b3f0a9af07427e2")
      file(DOWNLOAD ${EMBED_PYTHON_URL} ${EMBED_PYTHON_ARCHIVE_PATH} EXPECTED_HASH SHA256=${EMBED_PYTHON_SHA256})
    endif()
  else()
    set(BASEPYEXE py.exe -3.14-32)
    if(NOT EMBED_PYTHON_ARCHIVE_PATH)
      set(EMBED_PYTHON_URL "https://www.python.org/ftp/python/3.14.5/python-3.14.5-embed-win32.zip")
      set(EMBED_PYTHON_ARCHIVE_PATH "${CMAKE_CURRENT_BINARY_DIR}/python-3.14.5-embed-win32.zip")
      set(EMBED_PYTHON_SHA256 "9b461868ff63d5fd4275f8f7a802812672eacc8486aba9d7c6a0c4e3290af52b")
      file(DOWNLOAD ${EMBED_PYTHON_URL} ${EMBED_PYTHON_ARCHIVE_PATH} EXPECTED_HASH SHA256=${EMBED_PYTHON_SHA256})
    endif()
  endif()
  set(SERVER_PYTHON_DIR "${SERVER_DIR}/python")
  set(SERVER_DIR_DESTINATION "/")
  file(TO_NATIVE_PATH ${SERVER_PYTHON_DIR} SERVER_PYTHON_DIR_NATIVE)

  # marker file to indicate requirements installation is complete
  set(SERVER_OUTPUT_REQUIRMENTS_FILE "${SERVER_PYTHON_DIR}/requirements.installed")
  set(SERVER_OUTPUT_EMBED_PYTHON_FILE "${SERVER_PYTHON_DIR}/python.exe")
  set(SERVER_OUTPUT_VELES_LIB_FILE "${SERVER_PYTHON_DIR}/veles/__init__.py")

  add_custom_command(
      OUTPUT ${SERVER_OUTPUT_REQUIRMENTS_FILE}
      COMMAND ${BASEPYEXE} -m pip install -r "${CMAKE_CURRENT_BINARY_DIR}/python/requirements.txt" -t ${SERVER_DIR}/python
      COMMAND ${CMAKE_COMMAND} -E touch ${SERVER_OUTPUT_REQUIRMENTS_FILE}
      COMMENT "Installing veles python lib requirements"
  )

  add_custom_command(
      OUTPUT ${SERVER_OUTPUT_EMBED_PYTHON_FILE}
      COMMAND ${CMAKE_COMMAND} -E tar xzf ${EMBED_PYTHON_ARCHIVE_PATH}
      WORKING_DIRECTORY ${SERVER_PYTHON_DIR}
      COMMENT "Installing server embed python"
  )

  add_custom_command(
      OUTPUT ${SERVER_OUTPUT_VELES_LIB_FILE}
      COMMAND ${BASEPYEXE} -m pip install . -U --target ${SERVER_PYTHON_DIR_NATIVE}
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/python/
      COMMENT "Installing veles python lib"
  )

  add_custom_target(
      server
      DEPENDS ${SERVER_OUTPUT_REQUIRMENTS_FILE}
      DEPENDS ${SERVER_OUTPUT_EMBED_PYTHON_FILE}
      DEPENDS ${SERVER_OUTPUT_VELES_LIB_FILE}
      DEPENDS ${SERVER_OUTPUT_STARTUP_SCRIPT_FILE}
  )
endif()

if(CMAKE_HOST_UNIX AND NOT CMAKE_HOST_APPLE)
  set(BASEPYEXE python3)
  set(SERVER_DIR_DESTINATION share)
  # create venv with dependencies after installation and remove it when removing package
  set(CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA
      ${CMAKE_CURRENT_SOURCE_DIR}/resources/install/postinst
      ${CMAKE_CURRENT_SOURCE_DIR}/resources/install/prerm
  )

  set(SERVER_OUTPUT_REQUIRMENTS_FILE ${SERVER_DIR}/requirements.txt)

  add_custom_command(
      OUTPUT ${SERVER_OUTPUT_REQUIRMENTS_FILE}
      COMMAND ${CMAKE_COMMAND} -E copy_if_different
      "${CMAKE_CURRENT_BINARY_DIR}/python/requirements.txt"
      "${SERVER_DIR}/requirements.txt"
      COMMENT "Copying server script"
  )

  set(SERVER_OUTPUT_VELES_LIB_FILE "${SERVER_PYTHON_DIR}/veles")

  add_custom_command(
      OUTPUT ${SERVER_OUTPUT_VELES_LIB_FILE}
      COMMAND ${BASEPYEXE} setup.py sdist --dist-dir ${SERVER_DIR}
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/python/
      COMMENT "Installing veles python lib"
  )

  add_custom_target(server
      DEPENDS ${SERVER_OUTPUT_REQUIRMENTS_FILE}
      DEPENDS ${SERVER_OUTPUT_STARTUP_SCRIPT_FILE}
      DEPENDS ${SERVER_OUTPUT_VELES_LIB_FILE}
  )
endif()

if(CMAKE_HOST_APPLE)
  set(BASEPYEXE python3)
  set(SERVER_DIR_DESTINATION "veles.app/Contents/Resources/")
  set(SERVER_PYTHON_VENV_DIR ${SERVER_DIR}/venv)

  set(SERVER_OUTPUT_VELES_VENV_PYTHON ${SERVER_DIR}/venv/bin/python3)
  add_custom_command(
      OUTPUT ${SERVER_OUTPUT_VELES_VENV_PYTHON}
      COMMAND ${BASEPYEXE} -m venv ${SERVER_PYTHON_VENV_DIR}
      COMMENT "Creating veles python virtual environment"
  )

  set(SERVER_OUTPUT_VELES_LIB_REQUIRMENTS ${SERVER_DIR}/requirements)
  add_custom_command(
      OUTPUT ${SERVER_OUTPUT_VELES_LIB_REQUIRMENTS}
      COMMAND ${SERVER_OUTPUT_VELES_VENV_PYTHON} -m pip install -r requirements.txt
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/python/
      DEPENDS ${SERVER_OUTPUT_VELES_VENV_PYTHON}
      COMMENT "Installing veles python lib requirements"
  )

  set(SERVER_OUTPUT_VELES_LIB_FILE ${SERVER_DIR}/veleslib)
  add_custom_command(
      OUTPUT ${SERVER_OUTPUT_VELES_LIB_FILE}
      COMMAND ${SERVER_OUTPUT_VELES_VENV_PYTHON} -m pip install . -U
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/python/
      DEPENDS ${SERVER_OUTPUT_VELES_VENV_PYTHON}
      COMMENT "Installing veles python lib"
  )

  add_custom_target(
      server
      DEPENDS ${SERVER_OUTPUT_STARTUP_SCRIPT_FILE}
      DEPENDS ${SERVER_OUTPUT_VELES_LIB_FILE}
      DEPENDS ${SERVER_OUTPUT_VELES_LIB_REQUIRMENTS}
  )
endif()

# Prepare server environment only in `install` target.
install(CODE "execute_process(COMMAND \"${CMAKE_COMMAND}\" --build \"${CMAKE_CURRENT_BINARY_DIR}\" --target server)")
install(DIRECTORY ${SERVER_DIR} DESTINATION ${SERVER_DIR_DESTINATION} COMPONENT "server")
