cmake_minimum_required (VERSION 3.9)
project (nix-plugins)
set (nix-plugins_VERSION_MAJOR 15)
set (nix-plugins_VERSION_MINOR 0)
set (nix-plugins_VERSION_PATCH 0)

find_package(PkgConfig)

pkg_check_modules(NIX REQUIRED nix-expr>=2.26 nix-main>=2.26 nix-store>=2.26)

find_path(BOOST_INCLUDE_DIR boost/format.hpp)
if(BOOST_INCLUDE_DIR STREQUAL "BOOST_INCLUDE_DIR-NOTFOUND")
  message(FATAL_ERROR "Could not find Boost formatting library.")
endif()
include_directories(${BOOST_INCLUDE_DIR})

if(APPLE)
  set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -flat_namespace -undefined suppress")
endif()

add_library(example-plugin MODULE plugin.cc)
target_include_directories(example-plugin PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(example-plugin PUBLIC ${NIX_INCLUDE_DIRS})
target_compile_options(example-plugin PUBLIC ${NIX_CFLAGS_OTHER})

target_compile_options(example-plugin PUBLIC 
    ${NIX_CFLAGS_OTHER}
    -fPIC
    -fvisibility-inlines-hidden
    -fvisibility=hidden
)

add_compile_definitions(SYSTEM="x86_64-linux")

target_compile_definitions(example-plugin PRIVATE
    NIX_PLUGIN_EXPORT="__attribute__((visibility(\"default\")))"
)

install(TARGETS example-plugin DESTINATION lib/nix/plugins)
