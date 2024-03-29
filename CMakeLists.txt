cmake_minimum_required(VERSION 3.26)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# HACK: An ugly hack to provide default compilation type.
if(DEFINED CMAKE_BUILD_TYPE)
   set(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} CACHE STRING "Choose the type of
build, options are: None(CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug
Release RelWithDebInfo MinSizeRel.")
else()
   set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "Choose the type of build,
options are: None(CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release
RelWithDebInfo MinSizeRel.")
endif()

#[[
if(APPLE)
  set(CMAKE_OSX_DEPLOYMENT_TARGET "10.10" CACHE STRING "Minimum macOS deployment version")
endif()
]]

project(VELES C CXX)
#[[
  if(WIN32 AND CMAKE_SIZEOF_VOID_P EQUAL 4)
    message(FATAL_ERROR "Windows 32-bit is not supported due to performance problems in msgpack")
  endif()
]]

include("cmake/googletest.cmake")
include("cmake/qt.cmake")
include("cmake/zlib.cmake")
include("cmake/msgpack.cmake")
include("cmake/cppgen.cmake")
include("cmake/server.cmake")
include("cmake/openssl.cmake")

# Compiler flags
#[[
if(MINGW)
  # MinGW is not supported because of C++14 problems (and many others).
  message(FATAL_ERROR "MinGW is not supported, use MSVC on Windows")
endif()
#]]
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH ON)
set(CMAKE_INSTALL_RPATH ".")
if(CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")  # No warnings
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++23")  # For clang-tidy
  #set(ADDITIONAL_LINK_LIBRARIES "pthread")
endif()

# FreeBSD support
if(${CMAKE_SYSTEM_NAME} STREQUAL "FreeBSD")
  # Link BSD threading.
  list(APPEND ADDITIONAL_LINK_LIBRARIES "thr")
endif()

if(MSVC)
  # Uncomment this line to use instrumentation in Visual Studio.
  # set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /Profile")

  # Set exception handling mode and linking mode.
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc ")
  # Build with multiple processes.
  # see: https://docs.microsoft.com/en-us/cpp/build/reference/mp-build-with-multiple-processes
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP ")
endif()
if(APPLE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++23")  # For clang-tidy
endif()

if(WIN32)
  set(WINDOWS_APPLICATION_OUT_DIRECTORY "Veles UI")
  # Overwrite default Debug/Release/RelWithDebInfo/MinSizeRel application directory.
  # We can't use CMAKE_RUNTIME_OUTPUT_DIRECTORY, because it appends config type to the path.
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${WINDOWS_APPLICATION_OUT_DIRECTORY})
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${WINDOWS_APPLICATION_OUT_DIRECTORY})
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${WINDOWS_APPLICATION_OUT_DIRECTORY})
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${WINDOWS_APPLICATION_OUT_DIRECTORY})

  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${WINDOWS_APPLICATION_OUT_DIRECTORY})
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${WINDOWS_APPLICATION_OUT_DIRECTORY})
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO ${WINDOWS_APPLICATION_OUT_DIRECTORY})
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_MINSIZEREL ${WINDOWS_APPLICATION_OUT_DIRECTORY})

  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${WINDOWS_APPLICATION_OUT_DIRECTORY})
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${WINDOWS_APPLICATION_OUT_DIRECTORY})
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO ${WINDOWS_APPLICATION_OUT_DIRECTORY})
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL ${WINDOWS_APPLICATION_OUT_DIRECTORY})
endif()

# Sources
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(TEST_DIR ${CMAKE_SOURCE_DIR}/test)

include_directories(${INCLUDE_DIR})

qt5_add_resources(VISUALIZATION_SHADERS ${SRC_DIR}/visualization/shaders/shaders.qrc)

set(MSGPACK_CPP_FWD_HEADER "${CMAKE_CURRENT_BINARY_DIR}/fwd_models.h")
set(MSGPACK_CPP_HEADER "${CMAKE_CURRENT_BINARY_DIR}/models.h")
set(MSGPACK_CPP_SOURCE "${CMAKE_CURRENT_BINARY_DIR}/models.cc")
set(PYTHON_DIR ${CMAKE_SOURCE_DIR}/python)

add_custom_command(OUTPUT ${MSGPACK_CPP_HEADER} ${MSGPACK_CPP_SOURCE} ${MSGPACK_CPP_FWD_HEADER}
    COMMAND ${PYEXE} -m veles.cpp.generate ${CMAKE_CURRENT_BINARY_DIR}
        veles.data.repack
        veles.proto.node
        veles.proto.check
        veles.proto.chunk
        veles.proto.connection
        veles.proto.operation
        veles.proto.messages
        veles.proto.msgpackwrap
        veles.tests.schema.cpp_test_models
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/python
    COMMENT "Generating msgpack C++ code from Python"
    DEPENDS cpp_python_gen
        ${PYTHON_DIR}/veles/cpp/generate.py
        ${PYTHON_DIR}/veles/data/repack.py
        ${PYTHON_DIR}/veles/proto/check.py
        ${PYTHON_DIR}/veles/proto/chunk.py
        ${PYTHON_DIR}/veles/proto/connection.py
        ${PYTHON_DIR}/veles/proto/exceptions.py
        ${PYTHON_DIR}/veles/proto/messages.py
        ${PYTHON_DIR}/veles/proto/msgpackwrap.py
        ${PYTHON_DIR}/veles/proto/operation.py
        ${PYTHON_DIR}/veles/proto/node.py
        ${PYTHON_DIR}/veles/schema/model.py
        ${PYTHON_DIR}/veles/schema/enumeration.py
        ${PYTHON_DIR}/veles/schema/fields.py
        ${PYTHON_DIR}/veles/tests/schema/cpp_test_models.py
    VERBATIM
)

file(GLOB KAITAI_HEADERS "${INCLUDE_DIR}/kaitai/*.h")
file(GLOB KAITAI_SOURCES "${SRC_DIR}/kaitai/*.cc")

# Resources
qt5_add_resources(RESOURCES resources/veles.qrc)
qt5_wrap_ui(FORMS
    ${SRC_DIR}/ui/dialogs/connectiondialog.ui
    ${SRC_DIR}/ui/connectionnotificationwidget.ui
    ${SRC_DIR}/ui/dialogs/createchunkdialog.ui
    ${SRC_DIR}/ui/databaseinfo.ui
    ${SRC_DIR}/ui/dialogs/gotoaddressdialog.ui
    ${SRC_DIR}/ui/logwidget.ui
    ${SRC_DIR}/ui/dialogs/optionsdialog.ui
    ${SRC_DIR}/ui/dialogs/searchdialog.ui
    ${SRC_DIR}/ui/shortcutselection.ui
    ${SRC_DIR}/ui/shortcutssettings.ui
    ${SRC_DIR}/visualization/selectrangedialog.ui
    ${SRC_DIR}/visualization/samplingmethoddialog.ui
)

if(WIN32)
  set(ICONS ${CMAKE_SOURCE_DIR}/resources/icons/veles.rc)
endif()

if(APPLE)
  set(ICONS ${CMAKE_SOURCE_DIR}/resources/icons/veles.icns)
  set(MACOSX_BUNDLE_ICON_FILE veles.icns)
  set_source_files_properties(${ICONS} PROPERTIES
      MACOSX_PACKAGE_LOCATION Resources)
endif()

if(WIN32 AND NOT "${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
  # Don't create console window on non-debug builds.
  set(GUI_TYPE WIN32)
endif()

add_library(veles_base
    ${INCLUDE_DIR}/client/dbif.h
    ${INCLUDE_DIR}/client/networkclient.h
    ${INCLUDE_DIR}/client/node.h
    ${INCLUDE_DIR}/client/nodetree.h
    ${INCLUDE_DIR}/data/bindata.h
    ${INCLUDE_DIR}/data/field.h
    ${INCLUDE_DIR}/data/nodeid.h
    ${INCLUDE_DIR}/data/repack.h
    ${INCLUDE_DIR}/data/types.h
    ${INCLUDE_DIR}/db/getter.h
    ${INCLUDE_DIR}/db/universe.h
    ${INCLUDE_DIR}/dbif/error.h
    ${INCLUDE_DIR}/dbif/info.h
    ${INCLUDE_DIR}/dbif/method.h
    ${INCLUDE_DIR}/dbif/promise.h
    ${INCLUDE_DIR}/dbif/types.h
    ${INCLUDE_DIR}/dbif/universe.h
    ${INCLUDE_DIR}/network/msgpackobject.h
    ${INCLUDE_DIR}/network/msgpackwrapper.h
    ${INCLUDE_DIR}/parser/parser.h
    ${INCLUDE_DIR}/parser/stream.h
    ${INCLUDE_DIR}/parser/unpng.h
    ${INCLUDE_DIR}/parser/unpyc.h
    ${INCLUDE_DIR}/parser/utils.h
    ${INCLUDE_DIR}/proto/exceptions.h
    ${INCLUDE_DIR}/ui/color_picker_button.h
    ${INCLUDE_DIR}/ui/connectionmanager.h
    ${INCLUDE_DIR}/ui/databaseinfo.h
    ${INCLUDE_DIR}/ui/dialogs/connectiondialog.h
    ${INCLUDE_DIR}/ui/dialogs/createchunkdialog.h
    ${INCLUDE_DIR}/ui/dialogs/gotoaddressdialog.h
    ${INCLUDE_DIR}/ui/dialogs/optionsdialog.h
    ${INCLUDE_DIR}/ui/dialogs/searchdialog.h
    ${INCLUDE_DIR}/ui/dockwidget.h
    ${INCLUDE_DIR}/ui/dockwidget_native.h
    ${INCLUDE_DIR}/ui/fileblobitem.h
    ${INCLUDE_DIR}/ui/fileblobmodel.h
    ${INCLUDE_DIR}/ui/filters/activatedockeventfilter.h
    ${INCLUDE_DIR}/ui/filters/tabbareventfilter.h
    ${INCLUDE_DIR}/ui/hexedit.h
    ${INCLUDE_DIR}/ui/hexeditwidget.h
    ${INCLUDE_DIR}/ui/logwidget.h
    ${INCLUDE_DIR}/ui/mainwindowwithdetachabledockwidgets.h
    ${INCLUDE_DIR}/ui/nodetreewidget.h
    ${INCLUDE_DIR}/ui/nodewidget.h
    ${INCLUDE_DIR}/ui/rootfileblobitem.h
    ${INCLUDE_DIR}/ui/shortcutedit.h
    ${INCLUDE_DIR}/ui/shortcutssettings.h
    ${INCLUDE_DIR}/ui/simplefileblobitem.h
    ${INCLUDE_DIR}/ui/slice.h
    ${INCLUDE_DIR}/ui/spinbox.h
    ${INCLUDE_DIR}/ui/spinboxvalidator.h
    ${INCLUDE_DIR}/ui/subchunkfileblobitem.h
    ${INCLUDE_DIR}/ui/veles_mainwindow.h
    ${INCLUDE_DIR}/ui/velesapplication.h
    ${INCLUDE_DIR}/util/concurrency/threadpool.h
    ${INCLUDE_DIR}/util/edit.h
    ${INCLUDE_DIR}/util/encoders/base64_encoder.h
    ${INCLUDE_DIR}/util/encoders/c_data_encoder.h
    ${INCLUDE_DIR}/util/encoders/c_string_encoder.h
    ${INCLUDE_DIR}/util/encoders/factory.h
    ${INCLUDE_DIR}/util/encoders/hex_encoder.h
    ${INCLUDE_DIR}/util/encoders/idecoder.h
    ${INCLUDE_DIR}/util/encoders/iencoder.h
    ${INCLUDE_DIR}/util/encoders/text_encoder.h
    ${INCLUDE_DIR}/util/encoders/url_encoder.h
    ${INCLUDE_DIR}/util/icons.h
    ${INCLUDE_DIR}/util/int_bytes.h
    ${INCLUDE_DIR}/util/math.h
    ${INCLUDE_DIR}/util/misc.h
    ${INCLUDE_DIR}/util/sampling/fake_sampler.h
    ${INCLUDE_DIR}/util/sampling/isampler.h
    ${INCLUDE_DIR}/util/sampling/uniform_sampler.h
    ${INCLUDE_DIR}/util/settings/connection_client.h
    ${INCLUDE_DIR}/util/settings/hexedit.h
    ${INCLUDE_DIR}/util/settings/shortcuts.h
    ${INCLUDE_DIR}/util/settings/theme.h
    ${INCLUDE_DIR}/util/settings/visualization.h
    ${INCLUDE_DIR}/util/string_utils.h
    ${INCLUDE_DIR}/visualization/base.h
    ${INCLUDE_DIR}/visualization/digram.h
    ${INCLUDE_DIR}/visualization/manipulator.h
    ${INCLUDE_DIR}/visualization/minimap.h
    ${INCLUDE_DIR}/visualization/minimap_panel.h
    ${INCLUDE_DIR}/visualization/panel.h
    ${INCLUDE_DIR}/visualization/samplingmethoddialog.h
    ${INCLUDE_DIR}/visualization/selectrangedialog.h
    ${INCLUDE_DIR}/visualization/trigram.h

    ${SRC_DIR}/client/dbif.cc
    ${SRC_DIR}/client/networkclient.cc
    ${SRC_DIR}/client/nodetree.cc
    ${SRC_DIR}/data/bindata.cc
    ${SRC_DIR}/data/nodeid.cc
    ${SRC_DIR}/data/repack.cc
    ${SRC_DIR}/db/universe.cc
    ${SRC_DIR}/dbif/dbif.cc
    ${SRC_DIR}/network/msgpackobject.cc
    ${SRC_DIR}/parser/parser.cc
    ${SRC_DIR}/parser/unpng.cc
    ${SRC_DIR}/parser/unpyc.cc
    ${SRC_DIR}/parser/utils.cc
    ${SRC_DIR}/ui/color_picker_button.cc
    ${SRC_DIR}/ui/connectionmanager.cc
    ${SRC_DIR}/ui/databaseinfo.cc
    ${SRC_DIR}/ui/dialogs/connectiondialog.cc
    ${SRC_DIR}/ui/dialogs/createchunkdialog.cc
    ${SRC_DIR}/ui/dialogs/gotoaddressdialog.cc
    ${SRC_DIR}/ui/dialogs/optionsdialog.cc
    ${SRC_DIR}/ui/dialogs/searchdialog.cc
    ${SRC_DIR}/ui/dockwidget.cc
    ${SRC_DIR}/ui/dockwidget_native.cc
    ${SRC_DIR}/ui/fileblobitem.cc
    ${SRC_DIR}/ui/fileblobmodel.cc
    ${SRC_DIR}/ui/filters/activatedockeventfilter.cc
    ${SRC_DIR}/ui/filters/tabbareventfilter.cc
    ${SRC_DIR}/ui/hexedit.cc
    ${SRC_DIR}/ui/hexeditwidget.cc
    ${SRC_DIR}/ui/logwidget.cc
    ${SRC_DIR}/ui/main.cc
    ${SRC_DIR}/ui/mainwindowwithdetachabledockwidgets.cc
    ${SRC_DIR}/ui/nodetreewidget.cc
    ${SRC_DIR}/ui/nodewidget.cc
    ${SRC_DIR}/ui/rootfileblobitem.cc
    ${SRC_DIR}/ui/shortcutedit.cc
    ${SRC_DIR}/ui/shortcutssettings.cc
    ${SRC_DIR}/ui/spinbox.cc
    ${SRC_DIR}/ui/spinboxvalidator.cc
    ${SRC_DIR}/ui/subchunkfileblobitem.cc
    ${SRC_DIR}/ui/veles_mainwindow.cc
    ${SRC_DIR}/util/concurrency/threadpool.cc
    ${SRC_DIR}/util/edit.cc
    ${SRC_DIR}/util/encoders/base64_encoder.cc
    ${SRC_DIR}/util/encoders/c_data_encoder.cc
    ${SRC_DIR}/util/encoders/c_string_encoder.cc
    ${SRC_DIR}/util/encoders/factory.cc
    ${SRC_DIR}/util/encoders/hex_encoder.cc
    ${SRC_DIR}/util/encoders/text_encoder.cc
    ${SRC_DIR}/util/encoders/url_encoder.cc
    ${SRC_DIR}/util/icons.cc
    ${SRC_DIR}/util/math.cc
    ${SRC_DIR}/util/misc.cc
    ${SRC_DIR}/util/random.cc
    ${SRC_DIR}/util/sampling/fake_sampler.cc
    ${SRC_DIR}/util/sampling/isampler.cc
    ${SRC_DIR}/util/sampling/uniform_sampler.cc
    ${SRC_DIR}/util/settings/connection_client.cc
    ${SRC_DIR}/util/settings/hexedit.cc
    ${SRC_DIR}/util/settings/shortcuts.cc
    ${SRC_DIR}/util/settings/theme.cc
    ${SRC_DIR}/util/settings/visualization.cc
    ${SRC_DIR}/util/string_utils.cc
    ${SRC_DIR}/util/version.cc
    ${SRC_DIR}/visualization/base.cc
    ${SRC_DIR}/visualization/digram.cc
    ${SRC_DIR}/visualization/manipulator.cc
    ${SRC_DIR}/visualization/minimap.cc
    ${SRC_DIR}/visualization/minimap_panel.cc
    ${SRC_DIR}/visualization/panel.cc
    ${SRC_DIR}/visualization/samplingmethoddialog.cc
    ${SRC_DIR}/visualization/selectrangedialog.cc
    ${SRC_DIR}/visualization/trigram.cc

    ${KAITAI_HEADERS}
    ${MSGPACK_CPP_FWD_HEADER}
    ${MSGPACK_CPP_HEADER}
    ${MSGPACK_CPP_SOURCE}
    ${KAITAI_SOURCES}
    ${FORMS}
)

# Exe: Main executable
add_executable(main_exe
    ${GUI_TYPE}
    ${RESOURCES}
    ${ICONS}
    ${VISUALIZATION_SHADERS}
)

qt5_use_modules(veles_base Core Gui Widgets Network)

target_link_libraries(main_exe PRIVATE veles_base msgpack-cxx ZLIB::ZLIB OpenSSL::SSL OpenSSL::Crypto ${ADDITIONAL_LINK_LIBRARIES})
set_target_properties(main_exe PROPERTIES OUTPUT_NAME "veles")
#add_dependencies(main_exe msgpack-cxx)

if(GTEST_FOUND AND GMOCK_FOUND)
  include_directories(${GTEST_INCLUDE_DIRS} ${GMOCK_INCLUDE_DIRS})
  add_executable(run_test
      ${TEST_DIR}/run_test.cc
      ${TEST_DIR}/data/bindata.cc
      ${TEST_DIR}/data/copybits.cc
      ${TEST_DIR}/data/nodeid.cc
      ${TEST_DIR}/data/repack.cc
      ${TEST_DIR}/network/msgpackobject.cc
      ${TEST_DIR}/network/model.cc
      ${TEST_DIR}/util/encoders/base64_encoder.cc
      ${TEST_DIR}/util/encoders/c_data_encoder.cc
      ${TEST_DIR}/util/encoders/c_string_encoder.cc
      ${TEST_DIR}/util/encoders/hex_encoder.cc
      ${TEST_DIR}/util/encoders/text_encoder.cc
      ${TEST_DIR}/util/encoders/url_encoder.cc
      ${TEST_DIR}/util/encoders/factory.cc
      ${TEST_DIR}/util/sampling/mock_sampler.h
      ${TEST_DIR}/util/sampling/isampler.cc
      ${TEST_DIR}/util/sampling/uniform_sampler.cc
      ${TEST_DIR}/util/int_bytes.cc
      ${TEST_DIR}/util/edit.cc
  )

  target_link_libraries(run_test veles_base ${GTEST_LIBRARIES} ${GMOCK_LIBRARIES})

  add_custom_command(TARGET run_test
      COMMENT "Running tests"
      COMMAND $<TARGET_FILE:run_test> "--gtest_output=xml:results.xml"
      DEPENDS $<TARGET_FILE:run_test>
  )
else()
  message("gtest and/or gmock not found - tests won't be built")
endif()

# Post-build: linting

message(STATUS "Looking for clang-format")
find_program(CLANG_FORMAT NAMES clang-format-6.0 clang-format HINTS ${CLANG_TOOLS_PATH})

if(CLANG_FORMAT)
  message(STATUS "Looking for clang-format - found")
  file(GLOB_RECURSE FORMAT_ALL_SOURCE_FILES ${SRC_DIR}/*.cc ${INCLUDE_DIR}/*.h ${TEST_DIR}/*.cc ${TEST_DIR}/*.h)
  # On Windows, cmd.exe limits commands to 8192 characters.
  # Please be *very* cautious when editing this code: when command length
  # exceeds 8192 characters, the 8192th character is silently dropped and the
  # rest is glued together (sic!).
  # We pass arguments via a file to overcome the limit.
  set(FORMAT_CMDLINE_FILE "${CMAKE_CURRENT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/clang-format-cmdline.txt")
  file(WRITE ${FORMAT_CMDLINE_FILE} "-style=file\n")
  file(APPEND ${FORMAT_CMDLINE_FILE} "-sort-includes\n")
  file(APPEND ${FORMAT_CMDLINE_FILE} "-i\n")
  foreach(FORMAT_SOURCE_FILE ${FORMAT_ALL_SOURCE_FILES})
    file(APPEND ${FORMAT_CMDLINE_FILE} "${FORMAT_SOURCE_FILE}\n")
  endforeach()
  add_custom_target(format COMMAND ${CLANG_FORMAT} "\"@${FORMAT_CMDLINE_FILE}\"")
else()
  message(STATUS "Looking for clang-format - not found")
  message(STATUS "  Build target 'format' will not be available.")
endif()


message(STATUS "Looking for clang-tidy")
find_program(CLANG_TIDY NAMES clang-tidy-6.0 clang-tidy HINTS ${CLANG_TOOLS_PATH})

if(CLANG_TIDY)
  # Generate 'lint' target.
  # Currently we have to run clang-tidy by hand. Please fix this code if you
  # know a better solution.
  # Other unsuitable alternatives:
  #   - Use LLVM/share/clang/run-clang-tidy.py: We can't do it because it needs
  #     compile_commands.json file, which CMake can generate only for Make and
  #     ninja.
  #   - Use CMAKE_CXX_CLANG_TIDY: Requires CMake 3.6+ which isn't available on
  #     current Ubuntu LTS. This flag also seemed to have no effect on Windows.

  message(STATUS "Looking for clang-tidy - found")
  file(GLOB_RECURSE LINT_ALL_SOURCE_FILES "${SRC_DIR}/*.cc" "${TEST_DIR}/*.cc")

  # Don't lint kaitai-generated code, it contains too many issues.
  list(FILTER LINT_ALL_SOURCE_FILES EXCLUDE REGEX ".*/kaitai/.*")
  #foreach(LINT_SRC_FILE ${LINT_ALL_SOURCE_FILES})
  #  if(LINT_SRC_FILE MATCHES ".*/kaitai/.*")
  #    list(REMOVE_ITEM LINT_ALL_SOURCE_FILES ${LINT_SRC_FILE})
  #  endif()
  #endforeach()

  # Get includes from the main file.
  get_property(LINT_INC_DIRS TARGET main_exe PROPERTY INCLUDE_DIRECTORIES)
  get_property(LINT_INC_DIRS_BASE TARGET veles_base PROPERTY INCLUDE_DIRECTORIES)
  list(APPEND LINT_INC_DIRS ${LINT_INC_DIRS_BASE})

  if(APPLE)
    # macOS hack - remove surplus include directories
    list(FILTER LINT_INC_DIRS EXCLUDE REGEX "Qt[^/]+\\.framework$")
    #foreach(LINT_INCLUDE_FILE ${LINT_INC_DIRS})
    #  if(LINT_INCLUDE_FILE MATCHES "Qt[^/]+\\.framework$")
    #    list(REMOVE_ITEM LINT_INC_DIRS ${LINT_INCLUDE_FILE})
    #  endif()
    #endforeach()
  endif()

  # Remove duplicates.
  list(REMOVE_DUPLICATES LINT_INC_DIRS)

  # Use this hack, so that cmake will not escape space characters when passing
  # the list to COMMAND, for example by using "-I$<JOIN:${LINT_INC_DIRS}, -I>"
  #string(REPLACE ";" ";-I" LINT_INCLUDES "${LINT_INC_DIRS}")

  #message(STATUS "clang-tidy includes: -I${LINT_INCLUDES} -I${CMAKE_BINARY_DIR} -I${PROJECT_SOURCE_DIR}")
  # Parse CMAKE_CXX_FLAGS to list, so spaces will not be escaped in COMMANDs.
  #separate_arguments(LINT_CXX_FLAGS UNIX_COMMAND ${CMAKE_CXX_FLAGS})

  # As an alternative - we could use:
     list(APPEND LINT_CHECKS "google-*")
     list(APPEND LINT_CHECKS "performance-*")
     string(REPLACE ";" "," LINT_CHECKS_STR "${LINT_CHECKS}")
     set(CMAKE_CXX_CLANG_TIDY clang-tidy;-style=google;-checks=${LINT_CHECKS_STR})
  # and then all the magic should happen at compile time.
  # CMake 3.6+ is required for this (Ubuntu 18.04 LTS).

  add_custom_target(lint)

  # This target is needed so dependencies are not built for each clang-tidy call.
  add_custom_target(lint_depends
      DEPENDS
          ${MSGPACK_CPP_HEADER}
          ${MSGPACK_EXTRACT_PATH}
          ${FORMS}
  )

  # foreach is needed so maximum command line length is not reached.
  # Create intermediary targets to allow parallel checks with -jN.
  set(LINT_INDEX 0)
  foreach(LINT_SOURCE_FILE ${LINT_ALL_SOURCE_FILES})
    set(LINT_TARGET_NAME "__lint-${LINT_INDEX}")
    math(EXPR LINT_INDEX "${LINT_INDEX}+1")
    add_custom_target(
        ${LINT_TARGET_NAME}
        COMMAND
            ${CLANG_TIDY}
            # Test dir has some headers inside, don't skip them.
            "\"-header-filter=((${INCLUDE_DIR})|(${TEST_DIR}))[/\\].*\""
            -quiet
            ${LINT_SOURCE_FILE}
            --
            ${LINT_CXX_FLAGS}
            # Don't know how to force CMake to invoke compiler with -fPIC.
            "$<$<NOT:$<OR:$<BOOL:${WIN32}>,$<BOOL:${WIN64}>>>:-fPIC>"
            # Nasty hack to set -iframework flag for Qt on macOS
            "$<$<BOOL:${APPLE}>:-iframework${CMAKE_PREFIX_PATH}/lib>"
            -I${LINT_INCLUDES}
            -I${CMAKE_BINARY_DIR}
            -I${PROJECT_SOURCE_DIR}
        DEPENDS
            lint_depends
    )
    add_dependencies(lint ${LINT_TARGET_NAME})
  endforeach()
else()
  message(STATUS "Looking for clang-tidy - not found")
  message(STATUS "  Build target 'lint' will not be available.")
endif()


# Post-build packaging

# Unix paths
if(CMAKE_HOST_UNIX AND NOT CMAKE_HOST_APPLE)
  set(CPACK_PACKAGE_CONTACT "contact@veles.io")
  set(CPACK_DEBIAN_PACKAGE_SECTION "utils")
  set(CPACK_DEBIAN_PACKAGE_DEPENDS "libqt5core5a (>= 5.5.1), libqt5gui5 (>= 5.5.1),
      libqt5widgets5 (>= 5.5.1), libqt5network5 (>= 5.5.1), zlib1g (>= 1:1.2.8), g++,
      python3 (>= 3.5.0), python3-venv (>= 3.5.0), python3-dev (>= 3.5.0),
      openssl (>= 1.0.0), libffi-dev, libssl-dev (>= 1.0.0)"
  )
  install(TARGETS main_exe RUNTIME DESTINATION bin COMPONENT "application")

  install(FILES "${PROJECT_SOURCE_DIR}/resources/install/veles.desktop" DESTINATION share/applications/ COMPONENT "application")
  install(FILES "${PROJECT_SOURCE_DIR}/resources/icons/veles.ico" DESTINATION share/veles/ COMPONENT "application")
endif()

# Windows
if(WIN32)
  set_target_properties(main_exe PROPERTIES WIN32 TRUE)
  # Run winddeployqt if it can be found
  find_program(WINDEPLOYQT_EXECUTABLE NAMES windeployqt HINTS ${QTDIR} ENV QT PATH_SUFFIXES bin)
  add_custom_command(
      TARGET main_exe POST_BUILD
      COMMENT "Ensuring Qt dependencies"
      COMMAND ${WINDEPLOYQT_EXECUTABLE} ${WINDEPLOYQT_ARGS} $<TARGET_FILE:main_exe>
      DEPENDS $<TARGET_FILE:main_exe>
  )
  # Copy winddeployqt output to the directory with the main UI binary.
  install(DIRECTORY ${WIN_DEPLOY_DIR} DESTINATION ${WINDOWS_APPLICATION_OUT_DIRECTORY} COMPONENT "application")
  add_custom_command(
      TARGET main_exe POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_directory "${WIN_DEPLOY_DIR}" "${WINDOWS_APPLICATION_OUT_DIRECTORY}"
      DEPENDS $<TARGET_FILE:main_exe>
  )

  install(TARGETS main_exe RUNTIME DESTINATION ${WINDOWS_APPLICATION_OUT_DIRECTORY} COMPONENT "application")
  set(CPACK_NSIS_EXTRA_INSTALL_COMMANDS "ExecWait '\\\"$INSTDIR\\\\${WINDOWS_APPLICATION_OUT_DIRECTORY}\\\\${VCREDIST_BINARY}\\\" /install /passive'")
  install(FILES "${OPENSSL_DLL_DIR}/libeay32.dll" "${OPENSSL_DLL_DIR}/ssleay32.dll" DESTINATION ${WINDOWS_APPLICATION_OUT_DIRECTORY} COMPONENT "application")
  add_custom_command(
      TARGET main_exe POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_if_different
          "${OPENSSL_DLL_DIR}/libeay32.dll"
          "${OPENSSL_DLL_DIR}/ssleay32.dll"
          ${WINDOWS_APPLICATION_OUT_DIRECTORY}
      COMMENT "Copying OpenSSL DLLs"
  )
  set(CPACK_NSIS_EXECUTABLES_DIRECTORY ${WINDOWS_APPLICATION_OUT_DIRECTORY})
  set(CPACK_NSIS_MUI_FINISHPAGE_RUN "veles")
  set(CPACK_NSIS_INSTALLED_ICON_NAME "${WINDOWS_APPLICATION_OUT_DIRECTORY}/veles.exe")
  set(CPACK_NSIS_DISPLAY_NAME "Veles")
  set(CPACK_PACKAGE_INSTALL_REGISTRY_KEY "Codisec")
  set(CPACK_PACKAGE_INSTALL_DIRECTORY "Veles")
  set(CPACK_NSIS_ENABLE_UNINSTALL_BEFORE_INSTALL ON)
  set(CPACK_NSIS_URL_INFO_ABOUT "https://veles.io")
  set(CPACK_NSIS_CONTACT "contact@veles.io")
  set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/resources/install/license.txt")
  set(CPACK_PACKAGE_EXECUTABLES "veles" "VELES")
  set(CPACK_CREATE_DESKTOP_LINKS "veles")
  set(CPACK_NSIS_MODIFY_PATH ON)
endif()

# Apple
if(APPLE)
  set(CPACK_INSTALL_PREFIX "/Applications")
  set(CMAKE_MACOSX_RPATH on)
  # Finding MacDeployQt
  find_program(MACDEPLOYQT_EXECUTABLE
      macdeployqt
      ENV QT
      PATH_SUFFIXES "5.7/clang_64/bin"
  )
  add_custom_command(TARGET main_exe POST_BUILD
      COMMENT "Ensuring Qt dependencies"
      COMMAND ${MACDEPLOYQT_EXECUTABLE} ARGS ${CMAKE_CURRENT_BINARY_DIR}/\${CONFIGURATION}/$<TARGET_PROPERTY:main_exe,OUTPUT_NAME>.app ${MACDEPLOYQT_ARGS}
      DEPENDS $<TARGET_FILE:main_exe>
  )
  set_target_properties(main_exe PROPERTIES MACOSX_BUNDLE TRUE)
  set_target_properties(main_exe PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${CMAKE_SOURCE_DIR}/resources/MacOSXBundleInfo.plist.in)
  install(TARGETS main_exe BUNDLE DESTINATION "./" COMPONENT "application")
  set(CPACK_PACKAGE_EXECUTABLES "veles.app" "VELES")
endif()

set(CPACK_COMPONENT_APPLICATION_DISPLAY_NAME "Veles UI application")
set(CPACK_COMPONENT_SERVER_DISPLAY_NAME "Veles server")
set(CPACK_COMPONENT_APPLICATION_REQUIRED ON)

# Few common CPack settings
set(CPACK_PACKAGE_VENDOR "Codilime")
set(CPACK_PACKAGE_NAME "veles")
string(TIMESTAMP VERSION "%Y.%m")
set(CPACK_PACKAGE_VERSION "${VERSION}")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Veles tool for binary data analysis")
set(CPACK_MONOLITHIC_INSTALL)
set(CPACK_STRIP_FILES false)
include(CPack)