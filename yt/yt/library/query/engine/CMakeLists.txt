
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

add_library(library-query-engine)
target_compile_options(library-query-engine PRIVATE
  -Wdeprecated-this-capture
)
target_include_directories(library-query-engine PRIVATE
  ${CMAKE_BINARY_DIR}/yt
  ${CMAKE_SOURCE_DIR}/contrib/libs/sparsehash/src
  ${CMAKE_SOURCE_DIR}/contrib/libs/re2
  ${CMAKE_SOURCE_DIR}/contrib/libs/xdelta3
)
target_link_libraries(library-query-engine PUBLIC
  contrib-libs-linux-headers
  contrib-libs-cxxsupp
  yutil
  yt-yt-core
  yt-library-codegen
  library-query-misc
  library-query-proto
  library-query-base
  yt-yt-client
  cpp-yt-memory
  cpp-xdelta3-state
  contrib-libs-sparsehash
  library-cpp-resource
)
target_sources(library-query-engine PRIVATE
  ${CMAKE_SOURCE_DIR}/yt/yt/library/query/engine/cg_fragment_compiler.cpp
  ${CMAKE_SOURCE_DIR}/yt/yt/library/query/engine/cg_helpers.cpp
  ${CMAKE_SOURCE_DIR}/yt/yt/library/query/engine/cg_ir_builder.cpp
  ${CMAKE_SOURCE_DIR}/yt/yt/library/query/engine/cg_routines.cpp
  ${CMAKE_SOURCE_DIR}/yt/yt/library/query/engine/column_evaluator.cpp
  ${CMAKE_SOURCE_DIR}/yt/yt/library/query/engine/config.cpp
  ${CMAKE_SOURCE_DIR}/yt/yt/library/query/engine/coordinator.cpp
  ${CMAKE_SOURCE_DIR}/yt/yt/library/query/engine/evaluation_helpers.cpp
  ${CMAKE_SOURCE_DIR}/yt/yt/library/query/engine/evaluator.cpp
  ${CMAKE_SOURCE_DIR}/yt/yt/library/query/engine/folding_profiler.cpp
  ${CMAKE_SOURCE_DIR}/yt/yt/library/query/engine/functions_cg.cpp
  ${CMAKE_SOURCE_DIR}/yt/yt/library/query/engine/functions_builder.cpp
  ${CMAKE_SOURCE_DIR}/yt/yt/library/query/engine/functions_builtin_profilers.cpp
  ${CMAKE_SOURCE_DIR}/yt/yt/library/query/engine/range_inferrer.cpp
)

add_global_library_for(library-query-engine.global library-query-engine)
target_compile_options(library-query-engine.global PRIVATE
  -Wdeprecated-this-capture
)
target_include_directories(library-query-engine.global PRIVATE
  ${CMAKE_BINARY_DIR}/yt
  ${CMAKE_SOURCE_DIR}/contrib/libs/sparsehash/src
  ${CMAKE_SOURCE_DIR}/contrib/libs/re2
  ${CMAKE_SOURCE_DIR}/contrib/libs/xdelta3
)
target_link_libraries(library-query-engine.global PUBLIC
  contrib-libs-linux-headers
  contrib-libs-cxxsupp
  yutil
  yt-yt-core
  yt-library-codegen
  library-query-misc
  library-query-proto
  library-query-base
  yt-yt-client
  cpp-yt-memory
  cpp-xdelta3-state
  contrib-libs-sparsehash
  library-cpp-resource
)
target_sources(library-query-engine.global PRIVATE
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/7012e6bf1f3f80fdfce54d63afee3869.cpp
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/4ea047f29359e3ff85a43c2543e4ce0b.cpp
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/f4f5f9a1dc189a93c6482fc5d1bf55fb.cpp
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/0680164b1b2d7a3009f45ca5fe358052.cpp
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/3cdfaa942527999ed18a33f359e2cf3e.cpp
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/60ad550d891a29805e726874c57ef36a.cpp
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/223c93075db70d4bf4537276bcbff515.cpp
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/f876b2a9884e4bebbbf4b079ee82a487.cpp
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/737152a993bed557c44fc80c57b4770a.cpp
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/70f91f505af875ed195810036e510f1e.cpp
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/ddb6d2ed0678e1cd1cf0421f38baada1.cpp
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/6f9672363d86885757d05d833295f5b0.cpp
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/3ec77e425a852b536353a21a8ea196a4.cpp
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/47ee53635911ccb5e9e2ee208b131e5e.cpp
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/8612743541c6a8f3336686e050bd30e8.cpp
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/fa5223e6e0305ead558739f3efdbef9c.cpp
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/bfbc701f4d6d63efc47c4c254fe12159.cpp
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/d930b71c13c5eb81a9643257198db5df.cpp
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/af42b9c6dbe0713e1e50a65ea99528a4.cpp
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/6bc8056dac697953d13f7c8bc9486329.cpp
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/75da4cea6889896baa494bec9313e22c.cpp
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/fc2bd36183284aed418f1589e5511393.cpp
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/b3a3e9a9b46f60092a08755bf58496fd.cpp
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/aef3fcfb2f42efbbe6e19dc5e42865dc.cpp
)
add_custom_command(
  OUTPUT
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/hyperloglog_optimized.bc
  DEPENDS
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/hyperloglog_merged.bc
  COMMAND
  ${LLVMOPT}
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/hyperloglog_merged.bc
  -o
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/hyperloglog_optimized.bc
  -O2
  -globalopt
  -globaldce
  -internalize
  -internalize-public-api-list=cardinality_init#cardinality_update#cardinality_merge#cardinality_finalize
)
add_custom_command(
  OUTPUT
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/hyperloglog_merged.bc
  DEPENDS
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/udf/hyperloglog.cpp.bc
  COMMAND
  ${LLVMLINK}
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/udf/hyperloglog.cpp.bc
  -o
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/hyperloglog_merged.bc
)
add_custom_command(
  OUTPUT
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/farm_hash_optimized.bc
  DEPENDS
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/farm_hash_merged.bc
  COMMAND
  ${LLVMOPT}
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/farm_hash_merged.bc
  -o
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/farm_hash_optimized.bc
  -O2
  -globalopt
  -globaldce
  -internalize
  -internalize-public-api-list=farm_hash
)
add_custom_command(
  OUTPUT
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/farm_hash_merged.bc
  DEPENDS
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/udf/farm_hash.cpp.bc
  COMMAND
  ${LLVMLINK}
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/udf/farm_hash.cpp.bc
  -o
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/farm_hash_merged.bc
)
add_custom_command(
  OUTPUT
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/bigb_hash_optimized.bc
  DEPENDS
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/bigb_hash_merged.bc
  COMMAND
  ${LLVMOPT}
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/bigb_hash_merged.bc
  -o
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/bigb_hash_optimized.bc
  -O2
  -globalopt
  -globaldce
  -internalize
  -internalize-public-api-list=bigb_hash
)
add_custom_command(
  OUTPUT
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/bigb_hash_merged.bc
  DEPENDS
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/udf/bigb_hash.cpp.bc
  COMMAND
  ${LLVMLINK}
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/udf/bigb_hash.cpp.bc
  -o
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/bigb_hash_merged.bc
)
add_custom_command(
  OUTPUT
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/make_map_optimized.bc
  DEPENDS
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/make_map_merged.bc
  COMMAND
  ${LLVMOPT}
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/make_map_merged.bc
  -o
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/make_map_optimized.bc
  -O2
  -globalopt
  -globaldce
  -internalize
  -internalize-public-api-list=make_map
)
add_custom_command(
  OUTPUT
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/make_map_merged.bc
  DEPENDS
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/udf/make_map.cpp.bc
  COMMAND
  ${LLVMLINK}
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/udf/make_map.cpp.bc
  -o
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/make_map_merged.bc
)
add_custom_command(
  OUTPUT
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/str_conv_optimized.bc
  DEPENDS
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/str_conv_merged.bc
  COMMAND
  ${LLVMOPT}
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/str_conv_merged.bc
  -o
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/str_conv_optimized.bc
  -O2
  -globalopt
  -globaldce
  -internalize
  -internalize-public-api-list=numeric_to_string#parse_int64#parse_uint64#parse_double
)
add_custom_command(
  OUTPUT
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/str_conv_merged.bc
  DEPENDS
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/udf/str_conv.cpp.bc
  COMMAND
  ${LLVMLINK}
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/udf/str_conv.cpp.bc
  -o
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/str_conv_merged.bc
)
add_custom_command(
  OUTPUT
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/regex_optimized.bc
  DEPENDS
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/regex_merged.bc
  COMMAND
  ${LLVMOPT}
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/regex_merged.bc
  -o
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/regex_optimized.bc
  -O2
  -globalopt
  -globaldce
  -internalize
  -internalize-public-api-list=regex_full_match#regex_partial_match#regex_replace_first#regex_replace_all#regex_extract#regex_escape
)
add_custom_command(
  OUTPUT
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/regex_merged.bc
  DEPENDS
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/udf/regex.cpp.bc
  COMMAND
  ${LLVMLINK}
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/udf/regex.cpp.bc
  -o
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/regex_merged.bc
)
add_custom_command(
  OUTPUT
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/avg_optimized.bc
  DEPENDS
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/avg_merged.bc
  COMMAND
  ${LLVMOPT}
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/avg_merged.bc
  -o
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/avg_optimized.bc
  -O2
  -globalopt
  -globaldce
  -internalize
  -internalize-public-api-list=avg_init#avg_update#avg_merge#avg_finalize
)
add_custom_command(
  OUTPUT
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/avg_merged.bc
  DEPENDS
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/udf/avg.c.bc
  COMMAND
  ${LLVMLINK}
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/udf/avg.c.bc
  -o
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/avg_merged.bc
)
add_custom_command(
  OUTPUT
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/concat_optimized.bc
  DEPENDS
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/concat_merged.bc
  COMMAND
  ${LLVMOPT}
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/concat_merged.bc
  -o
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/concat_optimized.bc
  -O2
  -globalopt
  -globaldce
  -internalize
  -internalize-public-api-list=concat
)
add_custom_command(
  OUTPUT
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/concat_merged.bc
  DEPENDS
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/udf/concat.c.bc
  COMMAND
  ${LLVMLINK}
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/udf/concat.c.bc
  -o
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/concat_merged.bc
)
add_custom_command(
  OUTPUT
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/first_optimized.bc
  DEPENDS
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/first_merged.bc
  COMMAND
  ${LLVMOPT}
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/first_merged.bc
  -o
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/first_optimized.bc
  -O2
  -globalopt
  -globaldce
  -internalize
  -internalize-public-api-list=first_init#first_update#first_merge#first_finalize
)
add_custom_command(
  OUTPUT
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/first_merged.bc
  DEPENDS
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/udf/first.c.bc
  COMMAND
  ${LLVMLINK}
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/udf/first.c.bc
  -o
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/first_merged.bc
)
add_custom_command(
  OUTPUT
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/is_prefix_optimized.bc
  DEPENDS
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/is_prefix_merged.bc
  COMMAND
  ${LLVMOPT}
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/is_prefix_merged.bc
  -o
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/is_prefix_optimized.bc
  -O2
  -globalopt
  -globaldce
  -internalize
  -internalize-public-api-list=is_prefix
)
add_custom_command(
  OUTPUT
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/is_prefix_merged.bc
  DEPENDS
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/udf/is_prefix.c.bc
  COMMAND
  ${LLVMLINK}
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/udf/is_prefix.c.bc
  -o
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/is_prefix_merged.bc
)
add_custom_command(
  OUTPUT
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/is_substr_optimized.bc
  DEPENDS
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/is_substr_merged.bc
  COMMAND
  ${LLVMOPT}
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/is_substr_merged.bc
  -o
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/is_substr_optimized.bc
  -O2
  -globalopt
  -globaldce
  -internalize
  -internalize-public-api-list=is_substr
)
add_custom_command(
  OUTPUT
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/is_substr_merged.bc
  DEPENDS
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/udf/is_substr.c.bc
  COMMAND
  ${LLVMLINK}
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/udf/is_substr.c.bc
  -o
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/is_substr_merged.bc
)
add_custom_command(
  OUTPUT
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/to_any_optimized.bc
  DEPENDS
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/to_any_merged.bc
  COMMAND
  ${LLVMOPT}
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/to_any_merged.bc
  -o
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/to_any_optimized.bc
  -O2
  -globalopt
  -globaldce
  -internalize
  -internalize-public-api-list=to_any
)
add_custom_command(
  OUTPUT
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/to_any_merged.bc
  DEPENDS
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/udf/to_any.cpp.bc
  COMMAND
  ${LLVMLINK}
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/udf/to_any.cpp.bc
  -o
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/to_any_merged.bc
)
add_custom_command(
  OUTPUT
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/max_optimized.bc
  DEPENDS
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/max_merged.bc
  COMMAND
  ${LLVMOPT}
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/max_merged.bc
  -o
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/max_optimized.bc
  -O2
  -globalopt
  -globaldce
  -internalize
  -internalize-public-api-list=max_init#max_update#max_merge#max_finalize
)
add_custom_command(
  OUTPUT
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/max_merged.bc
  DEPENDS
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/udf/max.c.bc
  COMMAND
  ${LLVMLINK}
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/udf/max.c.bc
  -o
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/max_merged.bc
)
add_custom_command(
  OUTPUT
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/min_optimized.bc
  DEPENDS
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/min_merged.bc
  COMMAND
  ${LLVMOPT}
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/min_merged.bc
  -o
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/min_optimized.bc
  -O2
  -globalopt
  -globaldce
  -internalize
  -internalize-public-api-list=min_init#min_update#min_merge#min_finalize
)
add_custom_command(
  OUTPUT
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/min_merged.bc
  DEPENDS
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/udf/min.c.bc
  COMMAND
  ${LLVMLINK}
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/udf/min.c.bc
  -o
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/min_merged.bc
)
add_custom_command(
  OUTPUT
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/sleep_optimized.bc
  DEPENDS
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/sleep_merged.bc
  COMMAND
  ${LLVMOPT}
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/sleep_merged.bc
  -o
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/sleep_optimized.bc
  -O2
  -globalopt
  -globaldce
  -internalize
  -internalize-public-api-list=sleep#sleep
)
add_custom_command(
  OUTPUT
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/sleep_merged.bc
  DEPENDS
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/udf/sleep.c.bc
  COMMAND
  ${LLVMLINK}
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/udf/sleep.c.bc
  -o
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/sleep_merged.bc
)
add_custom_command(
  OUTPUT
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/sum_optimized.bc
  DEPENDS
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/sum_merged.bc
  COMMAND
  ${LLVMOPT}
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/sum_merged.bc
  -o
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/sum_optimized.bc
  -O2
  -globalopt
  -globaldce
  -internalize
  -internalize-public-api-list=sum_init#sum_update#sum_merge#sum_finalize
)
add_custom_command(
  OUTPUT
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/sum_merged.bc
  DEPENDS
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/udf/sum.c.bc
  COMMAND
  ${LLVMLINK}
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/udf/sum.c.bc
  -o
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/sum_merged.bc
)
add_custom_command(
  OUTPUT
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/ypath_get_optimized.bc
  DEPENDS
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/ypath_get_merged.bc
  COMMAND
  ${LLVMOPT}
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/ypath_get_merged.bc
  -o
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/ypath_get_optimized.bc
  -O2
  -globalopt
  -globaldce
  -internalize
  -internalize-public-api-list=try_get_int64#get_int64#try_get_uint64#get_uint64#try_get_double#get_double#try_get_boolean#get_boolean#try_get_string#get_string#try_get_any#get_any
)
add_custom_command(
  OUTPUT
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/ypath_get_merged.bc
  DEPENDS
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/udf/ypath_get.c.bc
  COMMAND
  ${LLVMLINK}
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/udf/ypath_get.c.bc
  -o
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/ypath_get_merged.bc
)
add_custom_command(
  OUTPUT
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/lower_optimized.bc
  DEPENDS
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/lower_merged.bc
  COMMAND
  ${LLVMOPT}
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/lower_merged.bc
  -o
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/lower_optimized.bc
  -O2
  -globalopt
  -globaldce
  -internalize
  -internalize-public-api-list=lower
)
add_custom_command(
  OUTPUT
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/lower_merged.bc
  DEPENDS
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/udf/lower.cpp.bc
  COMMAND
  ${LLVMLINK}
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/udf/lower.cpp.bc
  -o
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/lower_merged.bc
)
add_custom_command(
  OUTPUT
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/dates_optimized.bc
  DEPENDS
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/dates_merged.bc
  COMMAND
  ${LLVMOPT}
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/dates_merged.bc
  -o
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/dates_optimized.bc
  -O2
  -globalopt
  -globaldce
  -internalize
  -internalize-public-api-list=format_timestamp#timestamp_floor_hour#timestamp_floor_day#timestamp_floor_week#timestamp_floor_month#timestamp_floor_year
)
add_custom_command(
  OUTPUT
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/dates_merged.bc
  DEPENDS
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/udf/dates.c.bc
  COMMAND
  ${LLVMLINK}
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/udf/dates.c.bc
  -o
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/dates_merged.bc
)
add_custom_command(
  OUTPUT
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/format_guid_optimized.bc
  DEPENDS
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/format_guid_merged.bc
  COMMAND
  ${LLVMOPT}
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/format_guid_merged.bc
  -o
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/format_guid_optimized.bc
  -O2
  -globalopt
  -globaldce
  -internalize
  -internalize-public-api-list=format_guid
)
add_custom_command(
  OUTPUT
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/format_guid_merged.bc
  DEPENDS
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/udf/format_guid.c.bc
  COMMAND
  ${LLVMLINK}
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/udf/format_guid.c.bc
  -o
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/format_guid_merged.bc
)
add_custom_command(
  OUTPUT
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/list_contains_optimized.bc
  DEPENDS
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/list_contains_merged.bc
  COMMAND
  ${LLVMOPT}
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/list_contains_merged.bc
  -o
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/list_contains_optimized.bc
  -O2
  -globalopt
  -globaldce
  -internalize
  -internalize-public-api-list=list_contains
)
add_custom_command(
  OUTPUT
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/list_contains_merged.bc
  DEPENDS
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/udf/list_contains.cpp.bc
  COMMAND
  ${LLVMLINK}
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/udf/list_contains.cpp.bc
  -o
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/list_contains_merged.bc
)
add_custom_command(
  OUTPUT
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/any_to_yson_string_optimized.bc
  DEPENDS
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/any_to_yson_string_merged.bc
  COMMAND
  ${LLVMOPT}
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/any_to_yson_string_merged.bc
  -o
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/any_to_yson_string_optimized.bc
  -O2
  -globalopt
  -globaldce
  -internalize
  -internalize-public-api-list=any_to_yson_string
)
add_custom_command(
  OUTPUT
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/any_to_yson_string_merged.bc
  DEPENDS
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/udf/any_to_yson_string.cpp.bc
  COMMAND
  ${LLVMLINK}
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/udf/any_to_yson_string.cpp.bc
  -o
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/any_to_yson_string_merged.bc
)
add_custom_command(
  OUTPUT
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/has_permissions_optimized.bc
  DEPENDS
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/has_permissions_merged.bc
  COMMAND
  ${LLVMOPT}
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/has_permissions_merged.bc
  -o
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/has_permissions_optimized.bc
  -O2
  -globalopt
  -globaldce
  -internalize
  -internalize-public-api-list=has_permissions
)
add_custom_command(
  OUTPUT
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/has_permissions_merged.bc
  DEPENDS
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/udf/has_permissions.cpp.bc
  COMMAND
  ${LLVMLINK}
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/udf/has_permissions.cpp.bc
  -o
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/has_permissions_merged.bc
)
add_custom_command(
  OUTPUT
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/xdelta_optimized.bc
  DEPENDS
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/xdelta_merged.bc
  COMMAND
  ${LLVMOPT}
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/xdelta_merged.bc
  -o
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/xdelta_optimized.bc
  -O2
  -globalopt
  -globaldce
  -internalize
  -internalize-public-api-list=xdelta_init#xdelta_update#xdelta_merge#xdelta_finalize
)
add_custom_command(
  OUTPUT
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/xdelta_merged.bc
  DEPENDS
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/udf/xdelta3.c.bc
  COMMAND
  ${LLVMLINK}
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/udf/xdelta3.c.bc
  -o
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/xdelta_merged.bc
)
llvm_compile_c(library-query-engine.global
  ${CMAKE_SOURCE_DIR}/yt/yt/library/query/engine/udf/avg.c
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/udf/avg.c.bc
  ${CLANGC}
  -Wno-unknown-warning-option
  -emit-llvm
)
llvm_compile_c(library-query-engine.global
  ${CMAKE_SOURCE_DIR}/yt/yt/library/query/engine/udf/concat.c
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/udf/concat.c.bc
  ${CLANGC}
  -Wno-unknown-warning-option
  -emit-llvm
)
llvm_compile_c(library-query-engine.global
  ${CMAKE_SOURCE_DIR}/yt/yt/library/query/engine/udf/first.c
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/udf/first.c.bc
  ${CLANGC}
  -Wno-unknown-warning-option
  -emit-llvm
)
llvm_compile_c(library-query-engine.global
  ${CMAKE_SOURCE_DIR}/yt/yt/library/query/engine/udf/is_prefix.c
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/udf/is_prefix.c.bc
  ${CLANGC}
  -Wno-unknown-warning-option
  -emit-llvm
)
llvm_compile_c(library-query-engine.global
  ${CMAKE_SOURCE_DIR}/yt/yt/library/query/engine/udf/is_substr.c
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/udf/is_substr.c.bc
  ${CLANGC}
  -Wno-unknown-warning-option
  -emit-llvm
)
llvm_compile_c(library-query-engine.global
  ${CMAKE_SOURCE_DIR}/yt/yt/library/query/engine/udf/max.c
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/udf/max.c.bc
  ${CLANGC}
  -Wno-unknown-warning-option
  -emit-llvm
)
llvm_compile_c(library-query-engine.global
  ${CMAKE_SOURCE_DIR}/yt/yt/library/query/engine/udf/min.c
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/udf/min.c.bc
  ${CLANGC}
  -Wno-unknown-warning-option
  -emit-llvm
)
llvm_compile_c(library-query-engine.global
  ${CMAKE_SOURCE_DIR}/yt/yt/library/query/engine/udf/sleep.c
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/udf/sleep.c.bc
  ${CLANGC}
  -Wno-unknown-warning-option
  -emit-llvm
)
llvm_compile_c(library-query-engine.global
  ${CMAKE_SOURCE_DIR}/yt/yt/library/query/engine/udf/sum.c
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/udf/sum.c.bc
  ${CLANGC}
  -Wno-unknown-warning-option
  -emit-llvm
)
llvm_compile_c(library-query-engine.global
  ${CMAKE_SOURCE_DIR}/yt/yt/library/query/engine/udf/ypath_get.c
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/udf/ypath_get.c.bc
  ${CLANGC}
  -Wno-unknown-warning-option
  -emit-llvm
)
llvm_compile_c(library-query-engine.global
  ${CMAKE_SOURCE_DIR}/yt/yt/library/query/engine/udf/dates.c
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/udf/dates.c.bc
  ${CLANGC}
  -Wno-unknown-warning-option
  -emit-llvm
)
llvm_compile_c(library-query-engine.global
  ${CMAKE_SOURCE_DIR}/yt/yt/library/query/engine/udf/format_guid.c
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/udf/format_guid.c.bc
  ${CLANGC}
  -Wno-unknown-warning-option
  -emit-llvm
)
llvm_compile_c(library-query-engine.global
  ${CMAKE_SOURCE_DIR}/yt/yt/library/query/engine/udf/xdelta3.c
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/udf/xdelta3.c.bc
  ${CLANGC}
  -Wno-unknown-warning-option
  -emit-llvm
)
llvm_compile_cxx(library-query-engine.global
  ${CMAKE_SOURCE_DIR}/yt/yt/library/query/engine/udf/hyperloglog.cpp
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/udf/hyperloglog.cpp.bc
  ${CLANGPLUSPLUS}
  -Wno-unknown-warning-option
  -emit-llvm
)
llvm_compile_cxx(library-query-engine.global
  ${CMAKE_SOURCE_DIR}/yt/yt/library/query/engine/udf/farm_hash.cpp
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/udf/farm_hash.cpp.bc
  ${CLANGPLUSPLUS}
  -Wno-unknown-warning-option
  -emit-llvm
)
llvm_compile_cxx(library-query-engine.global
  ${CMAKE_SOURCE_DIR}/yt/yt/library/query/engine/udf/bigb_hash.cpp
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/udf/bigb_hash.cpp.bc
  ${CLANGPLUSPLUS}
  -Wno-unknown-warning-option
  -emit-llvm
)
llvm_compile_cxx(library-query-engine.global
  ${CMAKE_SOURCE_DIR}/yt/yt/library/query/engine/udf/make_map.cpp
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/udf/make_map.cpp.bc
  ${CLANGPLUSPLUS}
  -Wno-unknown-warning-option
  -emit-llvm
)
llvm_compile_cxx(library-query-engine.global
  ${CMAKE_SOURCE_DIR}/yt/yt/library/query/engine/udf/str_conv.cpp
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/udf/str_conv.cpp.bc
  ${CLANGPLUSPLUS}
  -Wno-unknown-warning-option
  -emit-llvm
)
llvm_compile_cxx(library-query-engine.global
  ${CMAKE_SOURCE_DIR}/yt/yt/library/query/engine/udf/regex.cpp
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/udf/regex.cpp.bc
  ${CLANGPLUSPLUS}
  -Wno-unknown-warning-option
  -emit-llvm
)
llvm_compile_cxx(library-query-engine.global
  ${CMAKE_SOURCE_DIR}/yt/yt/library/query/engine/udf/to_any.cpp
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/udf/to_any.cpp.bc
  ${CLANGPLUSPLUS}
  -Wno-unknown-warning-option
  -emit-llvm
)
llvm_compile_cxx(library-query-engine.global
  ${CMAKE_SOURCE_DIR}/yt/yt/library/query/engine/udf/lower.cpp
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/udf/lower.cpp.bc
  ${CLANGPLUSPLUS}
  -Wno-unknown-warning-option
  -emit-llvm
)
llvm_compile_cxx(library-query-engine.global
  ${CMAKE_SOURCE_DIR}/yt/yt/library/query/engine/udf/list_contains.cpp
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/udf/list_contains.cpp.bc
  ${CLANGPLUSPLUS}
  -Wno-unknown-warning-option
  -emit-llvm
)
llvm_compile_cxx(library-query-engine.global
  ${CMAKE_SOURCE_DIR}/yt/yt/library/query/engine/udf/any_to_yson_string.cpp
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/udf/any_to_yson_string.cpp.bc
  ${CLANGPLUSPLUS}
  -Wno-unknown-warning-option
  -emit-llvm
)
llvm_compile_cxx(library-query-engine.global
  ${CMAKE_SOURCE_DIR}/yt/yt/library/query/engine/udf/has_permissions.cpp
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/udf/has_permissions.cpp.bc
  ${CLANGPLUSPLUS}
  -Wno-unknown-warning-option
  -emit-llvm
)
resources(library-query-engine.global
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/7012e6bf1f3f80fdfce54d63afee3869.cpp
  INPUTS
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/hyperloglog_optimized.bc
  KEYS
  /llvm_bc/hyperloglog
)
resources(library-query-engine.global
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/4ea047f29359e3ff85a43c2543e4ce0b.cpp
  INPUTS
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/farm_hash_optimized.bc
  KEYS
  /llvm_bc/farm_hash
)
resources(library-query-engine.global
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/f4f5f9a1dc189a93c6482fc5d1bf55fb.cpp
  INPUTS
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/bigb_hash_optimized.bc
  KEYS
  /llvm_bc/bigb_hash
)
resources(library-query-engine.global
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/0680164b1b2d7a3009f45ca5fe358052.cpp
  INPUTS
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/make_map_optimized.bc
  KEYS
  /llvm_bc/make_map
)
resources(library-query-engine.global
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/3cdfaa942527999ed18a33f359e2cf3e.cpp
  INPUTS
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/str_conv_optimized.bc
  KEYS
  /llvm_bc/str_conv
)
resources(library-query-engine.global
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/60ad550d891a29805e726874c57ef36a.cpp
  INPUTS
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/regex_optimized.bc
  KEYS
  /llvm_bc/regex
)
resources(library-query-engine.global
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/223c93075db70d4bf4537276bcbff515.cpp
  INPUTS
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/avg_optimized.bc
  KEYS
  /llvm_bc/avg
)
resources(library-query-engine.global
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/f876b2a9884e4bebbbf4b079ee82a487.cpp
  INPUTS
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/concat_optimized.bc
  KEYS
  /llvm_bc/concat
)
resources(library-query-engine.global
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/737152a993bed557c44fc80c57b4770a.cpp
  INPUTS
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/first_optimized.bc
  KEYS
  /llvm_bc/first
)
resources(library-query-engine.global
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/70f91f505af875ed195810036e510f1e.cpp
  INPUTS
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/is_prefix_optimized.bc
  KEYS
  /llvm_bc/is_prefix
)
resources(library-query-engine.global
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/ddb6d2ed0678e1cd1cf0421f38baada1.cpp
  INPUTS
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/is_substr_optimized.bc
  KEYS
  /llvm_bc/is_substr
)
resources(library-query-engine.global
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/6f9672363d86885757d05d833295f5b0.cpp
  INPUTS
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/to_any_optimized.bc
  KEYS
  /llvm_bc/to_any
)
resources(library-query-engine.global
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/3ec77e425a852b536353a21a8ea196a4.cpp
  INPUTS
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/max_optimized.bc
  KEYS
  /llvm_bc/max
)
resources(library-query-engine.global
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/47ee53635911ccb5e9e2ee208b131e5e.cpp
  INPUTS
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/min_optimized.bc
  KEYS
  /llvm_bc/min
)
resources(library-query-engine.global
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/8612743541c6a8f3336686e050bd30e8.cpp
  INPUTS
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/sleep_optimized.bc
  KEYS
  /llvm_bc/sleep
)
resources(library-query-engine.global
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/fa5223e6e0305ead558739f3efdbef9c.cpp
  INPUTS
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/sum_optimized.bc
  KEYS
  /llvm_bc/sum
)
resources(library-query-engine.global
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/bfbc701f4d6d63efc47c4c254fe12159.cpp
  INPUTS
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/ypath_get_optimized.bc
  KEYS
  /llvm_bc/ypath_get
)
resources(library-query-engine.global
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/d930b71c13c5eb81a9643257198db5df.cpp
  INPUTS
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/lower_optimized.bc
  KEYS
  /llvm_bc/lower
)
resources(library-query-engine.global
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/af42b9c6dbe0713e1e50a65ea99528a4.cpp
  INPUTS
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/dates_optimized.bc
  KEYS
  /llvm_bc/dates
)
resources(library-query-engine.global
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/6bc8056dac697953d13f7c8bc9486329.cpp
  INPUTS
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/format_guid_optimized.bc
  KEYS
  /llvm_bc/format_guid
)
resources(library-query-engine.global
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/75da4cea6889896baa494bec9313e22c.cpp
  INPUTS
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/list_contains_optimized.bc
  KEYS
  /llvm_bc/list_contains
)
resources(library-query-engine.global
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/fc2bd36183284aed418f1589e5511393.cpp
  INPUTS
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/any_to_yson_string_optimized.bc
  KEYS
  /llvm_bc/any_to_yson_string
)
resources(library-query-engine.global
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/b3a3e9a9b46f60092a08755bf58496fd.cpp
  INPUTS
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/has_permissions_optimized.bc
  KEYS
  /llvm_bc/has_permissions
)
resources(library-query-engine.global
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/aef3fcfb2f42efbbe6e19dc5e42865dc.cpp
  INPUTS
  ${CMAKE_BINARY_DIR}/yt/yt/library/query/engine/xdelta_optimized.bc
  KEYS
  /llvm_bc/xdelta
)
