
# This file was generated by the build system used internally in the Yandex monorepo.
# Only simple modifications are allowed (adding source-files to targets, adding simple properties
# like target_include_directories). These modifications will be ported to original
# ya.make files by maintainers. Any complex modifications which can't be ported back to the
# original buildsystem will not be accepted.


get_built_tool_path(
  TOOL_rescompiler_bin
  TOOL_rescompiler_dependency
  tools/rescompiler/bin
  rescompiler
)
get_built_tool_path(
  TOOL_rescompiler_bin
  TOOL_rescompiler_dependency
  tools/rescompiler/bin
  rescompiler
)
get_built_tool_path(
  TOOL_rescompiler_bin
  TOOL_rescompiler_dependency
  tools/rescompiler/bin
  rescompiler
)
get_built_tool_path(
  TOOL_rescompiler_bin
  TOOL_rescompiler_dependency
  tools/rescompiler/bin
  rescompiler
)

add_library(query-unittests-udf INTERFACE)
target_link_libraries(query-unittests-udf INTERFACE
  contrib-libs-linux-headers
  contrib-libs-cxxsupp
  yutil
  library-cpp-resource
)

add_global_library_for(query-unittests-udf.global query-unittests-udf)
target_compile_options(query-unittests-udf.global PRIVATE
  -Wdeprecated-this-capture
)
target_include_directories(query-unittests-udf.global PRIVATE
  ${CMAKE_SOURCE_DIR}/yt
)
target_link_libraries(query-unittests-udf.global PUBLIC
  contrib-libs-linux-headers
  contrib-libs-cxxsupp
  yutil
  library-cpp-resource
)
target_sources(query-unittests-udf.global PRIVATE
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/unittests/udf/2062ac0d56b10bdeaa23560378a409a3.cpp
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/unittests/udf/bac0e4f65ff99b8fb74dd4fd574cfc92.cpp
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/unittests/udf/9ee5169557a669d524c6d6d45b5b6de8.cpp
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/unittests/udf/553b3a2404ace59eb76ee28e72b94162.cpp
)
add_custom_command(
  OUTPUT
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/unittests/udf/malloc_udf_optimized.bc
  DEPENDS
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/unittests/udf/malloc_udf_merged.bc
  COMMAND
  ${LLVMOPT}
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/unittests/udf/malloc_udf_merged.bc
  -o
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/unittests/udf/malloc_udf_optimized.bc
  -O2
  -globalopt
  -globaldce
  -internalize
  -internalize-public-api-list=malloc_udf
)
add_custom_command(
  OUTPUT
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/unittests/udf/malloc_udf_merged.bc
  DEPENDS
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/unittests/udf/malloc_udf.c.bc
  COMMAND
  ${LLVMLINK}
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/unittests/udf/malloc_udf.c.bc
  -o
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/unittests/udf/malloc_udf_merged.bc
)
add_custom_command(
  OUTPUT
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/unittests/udf/test_udfs_optimized.bc
  DEPENDS
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/unittests/udf/test_udfs_merged.bc
  COMMAND
  ${LLVMOPT}
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/unittests/udf/test_udfs_merged.bc
  -o
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/unittests/udf/test_udfs_optimized.bc
  -O2
  -globalopt
  -globaldce
  -internalize
  -internalize-public-api-list=seventyfive#strtol_udf#exp_udf#tolower_udf#is_null_udf#abs_udf#sum_udf#throw_if_negative_udf#avg_udaf_init#avg_udaf_update#avg_udaf_merge#avg_udaf_finalize
)
add_custom_command(
  OUTPUT
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/unittests/udf/test_udfs_merged.bc
  DEPENDS
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/unittests/udf/test_udfs.c.bc
  COMMAND
  ${LLVMLINK}
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/unittests/udf/test_udfs.c.bc
  -o
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/unittests/udf/test_udfs_merged.bc
)
add_custom_command(
  OUTPUT
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/unittests/udf/test_udfs_fc_optimized.bc
  DEPENDS
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/unittests/udf/test_udfs_fc_merged.bc
  COMMAND
  ${LLVMOPT}
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/unittests/udf/test_udfs_fc_merged.bc
  -o
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/unittests/udf/test_udfs_fc_optimized.bc
  -O2
  -globalopt
  -globaldce
  -internalize
  -internalize-public-api-list=udf_with_function_context
)
add_custom_command(
  OUTPUT
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/unittests/udf/test_udfs_fc_merged.bc
  DEPENDS
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/unittests/udf/test_udfs_fc.cpp.bc
  COMMAND
  ${LLVMLINK}
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/unittests/udf/test_udfs_fc.cpp.bc
  -o
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/unittests/udf/test_udfs_fc_merged.bc
)
add_custom_command(
  OUTPUT
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/unittests/udf/xor_aggregate_optimized.bc
  DEPENDS
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/unittests/udf/xor_aggregate_merged.bc
  COMMAND
  ${LLVMOPT}
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/unittests/udf/xor_aggregate_merged.bc
  -o
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/unittests/udf/xor_aggregate_optimized.bc
  -O2
  -globalopt
  -globaldce
  -internalize
  -internalize-public-api-list=xor_aggregate_init#xor_aggregate_update#xor_aggregate_merge#xor_aggregate_finalize
)
add_custom_command(
  OUTPUT
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/unittests/udf/xor_aggregate_merged.bc
  DEPENDS
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/unittests/udf/xor_aggregate.c.bc
  COMMAND
  ${LLVMLINK}
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/unittests/udf/xor_aggregate.c.bc
  -o
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/unittests/udf/xor_aggregate_merged.bc
)
llvm_compile_c(query-unittests-udf.global
  ${CMAKE_SOURCE_DIR}/yt/yt/library/query/unittests/udf/malloc_udf.c
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/unittests/udf/malloc_udf.c.bc
  ${CLANGC}
  -Wno-unknown-warning-option
  -emit-llvm
)
llvm_compile_c(query-unittests-udf.global
  ${CMAKE_SOURCE_DIR}/yt/yt/library/query/unittests/udf/test_udfs.c
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/unittests/udf/test_udfs.c.bc
  ${CLANGC}
  -Wno-unknown-warning-option
  -emit-llvm
)
llvm_compile_c(query-unittests-udf.global
  ${CMAKE_SOURCE_DIR}/yt/yt/library/query/unittests/udf/xor_aggregate.c
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/unittests/udf/xor_aggregate.c.bc
  ${CLANGC}
  -Wno-unknown-warning-option
  -emit-llvm
)
llvm_compile_cxx(query-unittests-udf.global
  ${CMAKE_SOURCE_DIR}/yt/yt/library/query/unittests/udf/test_udfs_fc.cpp
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/unittests/udf/test_udfs_fc.cpp.bc
  ${CLANGPLUSPLUS}
  -Wno-unknown-warning-option
  -emit-llvm
)
resources(query-unittests-udf.global
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/unittests/udf/2062ac0d56b10bdeaa23560378a409a3.cpp
  INPUTS
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/unittests/udf/malloc_udf_optimized.bc
  KEYS
  /llvm_bc/malloc_udf
)
resources(query-unittests-udf.global
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/unittests/udf/bac0e4f65ff99b8fb74dd4fd574cfc92.cpp
  INPUTS
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/unittests/udf/test_udfs_optimized.bc
  KEYS
  /llvm_bc/test_udfs
)
resources(query-unittests-udf.global
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/unittests/udf/9ee5169557a669d524c6d6d45b5b6de8.cpp
  INPUTS
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/unittests/udf/test_udfs_fc_optimized.bc
  KEYS
  /llvm_bc/test_udfs_fc
)
resources(query-unittests-udf.global
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/unittests/udf/553b3a2404ace59eb76ee28e72b94162.cpp
  INPUTS
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/unittests/udf/xor_aggregate_optimized.bc
  KEYS
  /llvm_bc/xor_aggregate
)
