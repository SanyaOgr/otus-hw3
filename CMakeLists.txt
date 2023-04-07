cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("otus-hw3")

add_executable (ip_filter "ip_filter.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ip_filter PROPERTY CXX_STANDARD 20)
endif()


if(MSVC)
    # @see https://github.com/google/googletest/blob/v1.8.x/googletest/README.md
    # Visual Studio Dynamic vs Static Runtimes
    set(gtest_force_shared_crt ON CACHE BOOL "Always use msvcrt.dll" FORCE)
endif()

add_subdirectory(vendor/googletest)

enable_testing()

add_executable(
    test_filter
    "test_filter.cpp"
)

target_link_libraries(
    test_filter
    gtest
    gtest_main
)

add_test(test_filter test_filter)