# Google Test

if(GOOGLETEST_SRC_PATH)
  if(MSVC)
    option(gtest_force_shared_crt "" ON)
  endif()
  add_subdirectory(${GOOGLETEST_SRC_PATH} "googletest-bin" EXCLUDE_FROM_ALL)
  set(GTEST_FOUND true)
  set(GMOCK_FOUND true)
  set(GTEST_LIBRARIES "gtest")
  set(GMOCK_LIBRARIES "gmock")
  set(GTEST_INCLUDE_DIRS "${GOOGLETEST_SRC_PATH}/googletest/include/")
  set(GMOCK_INCLUDE_DIRS "${GOOGLETEST_SRC_PATH}/googlemock/include/")
else()
  find_package(GTest)
  find_package(GMock)
endif()

#[[
if(NOT MSVC)
  set(GTEST_LIBRARIES ${GTEST_LIBRARIES} pthread m)
endif()
#]]
