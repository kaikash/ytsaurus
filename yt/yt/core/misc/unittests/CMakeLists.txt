
# This file was generated by the build system used internally in the Yandex monorepo.
# Only simple modifications are allowed (adding source-files to targets, adding simple properties
# like target_include_directories). These modifications will be ported to original
# ya.make files by maintainers. Any complex modifications which can't be ported back to the
# original buildsystem will not be accepted.


get_built_tool_path(
  TOOL_protoc_bin
  TOOL_protoc_dependency
  contrib/tools/protoc/bin
  protoc
)
get_built_tool_path(
  TOOL_cpp_styleguide_bin
  TOOL_cpp_styleguide_dependency
  contrib/tools/protoc/plugins/cpp_styleguide
  cpp_styleguide
)

add_executable(unittester-core-misc)
target_compile_options(unittester-core-misc PRIVATE
  -Wdeprecated-this-capture
)
target_include_directories(unittester-core-misc PRIVATE
  ${CMAKE_BINARY_DIR}/yt
)
target_link_libraries(unittester-core-misc PUBLIC
  contrib-libs-linux-headers
  contrib-libs-cxxsupp
  yutil
  cpp-ytalloc-impl
  library-cpp-cpuid_check
  cpp-testing-gtest
  cpp-testing-gtest_main
  yt-yt-core
  yt-core-test_framework
  contrib-libs-protobuf
)
target_link_options(unittester-core-misc PRIVATE
  -ldl
  -lrt
  -Wl,--no-as-needed
  -fPIC
  -fPIC
  -lpthread
  -lrt
  -ldl
  -lutil
)
target_proto_messages(unittester-core-misc PRIVATE
  ${CMAKE_SOURCE_DIR}/yt/yt/core/misc/unittests/proto/ref_counted_tracker_ut.proto
)
target_sources(unittester-core-misc PRIVATE
  ${CMAKE_SOURCE_DIR}/yt/yt/core/misc/unittests/algorithm_helpers_ut.cpp
  ${CMAKE_SOURCE_DIR}/yt/yt/core/misc/unittests/arithmetic_formula_ut.cpp
  ${CMAKE_SOURCE_DIR}/yt/yt/core/misc/unittests/atomic_ptr_ut.cpp
  ${CMAKE_SOURCE_DIR}/yt/yt/core/misc/unittests/async_expiring_cache_ut.cpp
  ${CMAKE_SOURCE_DIR}/yt/yt/core/misc/unittests/async_slru_cache_ut.cpp
  ${CMAKE_SOURCE_DIR}/yt/yt/core/misc/unittests/bind_ut.cpp
  ${CMAKE_SOURCE_DIR}/yt/yt/core/misc/unittests/bit_packed_integer_vector_ut.cpp
  ${CMAKE_SOURCE_DIR}/yt/yt/core/misc/unittests/boolean_formula_ut.cpp
  ${CMAKE_SOURCE_DIR}/yt/yt/core/misc/unittests/callback_ut.cpp
  ${CMAKE_SOURCE_DIR}/yt/yt/core/misc/unittests/checksum_ut.cpp
  ${CMAKE_SOURCE_DIR}/yt/yt/core/misc/unittests/concurrent_cache_ut.cpp
  ${CMAKE_SOURCE_DIR}/yt/yt/core/misc/unittests/dnf_ut.cpp
  ${CMAKE_SOURCE_DIR}/yt/yt/core/misc/unittests/digest_ut.cpp
  ${CMAKE_SOURCE_DIR}/yt/yt/core/misc/unittests/ema_counter_ut.cpp
  ${CMAKE_SOURCE_DIR}/yt/yt/core/misc/unittests/enum_ut.cpp
  ${CMAKE_SOURCE_DIR}/yt/yt/core/misc/unittests/error_code_ut.cpp
  ${CMAKE_SOURCE_DIR}/yt/yt/core/misc/unittests/error_ut.cpp
  ${CMAKE_SOURCE_DIR}/yt/yt/core/misc/unittests/fair_scheduler_ut.cpp
  ${CMAKE_SOURCE_DIR}/yt/yt/core/misc/unittests/fenwick_tree_ut.cpp
  ${CMAKE_SOURCE_DIR}/yt/yt/core/misc/unittests/finally_ut.cpp
  ${CMAKE_SOURCE_DIR}/yt/yt/core/misc/unittests/format_ut.cpp
  ${CMAKE_SOURCE_DIR}/yt/yt/core/misc/unittests/fs_ut.cpp
  ${CMAKE_SOURCE_DIR}/yt/yt/core/misc/unittests/future_ut.cpp
  ${CMAKE_SOURCE_DIR}/yt/yt/core/misc/unittests/guid_ut.cpp
  ${CMAKE_SOURCE_DIR}/yt/yt/core/misc/unittests/hash_filter_ut.cpp
  ${CMAKE_SOURCE_DIR}/yt/yt/core/misc/unittests/hazard_ptr_ut.cpp
  ${CMAKE_SOURCE_DIR}/yt/yt/core/misc/unittests/heap_ut.cpp
  ${CMAKE_SOURCE_DIR}/yt/yt/core/misc/unittests/histogram_ut.cpp
  ${CMAKE_SOURCE_DIR}/yt/yt/core/misc/unittests/historic_usage_aggregator_ut.cpp
  ${CMAKE_SOURCE_DIR}/yt/yt/core/misc/unittests/hyperloglog_ut.cpp
  ${CMAKE_SOURCE_DIR}/yt/yt/core/misc/unittests/intern_registry_ut.cpp
  ${CMAKE_SOURCE_DIR}/yt/yt/core/misc/unittests/job_signaler_ut.cpp
  ${CMAKE_SOURCE_DIR}/yt/yt/core/misc/unittests/lock_free_hash_table_ut.cpp
  ${CMAKE_SOURCE_DIR}/yt/yt/core/misc/unittests/lru_cache_ut.cpp
  ${CMAKE_SOURCE_DIR}/yt/yt/core/misc/unittests/memory_tag_ut.cpp
  ${CMAKE_SOURCE_DIR}/yt/yt/core/misc/unittests/mpsc_fair_share_queue_ut.cpp
  ${CMAKE_SOURCE_DIR}/yt/yt/core/misc/unittests/mpsc_stack_ut.cpp
  ${CMAKE_SOURCE_DIR}/yt/yt/core/misc/unittests/mpsc_queue_ut.cpp
  ${CMAKE_SOURCE_DIR}/yt/yt/core/misc/unittests/relaxed_mpsc_queue_ut.cpp
  ${CMAKE_SOURCE_DIR}/yt/yt/core/misc/unittests/mpl_ut.cpp
  ${CMAKE_SOURCE_DIR}/yt/yt/core/misc/unittests/pattern_formatter_ut.cpp
  ${CMAKE_SOURCE_DIR}/yt/yt/core/misc/unittests/persistent_queue_ut.cpp
  ${CMAKE_SOURCE_DIR}/yt/yt/core/misc/unittests/phoenix_ut.cpp
  ${CMAKE_SOURCE_DIR}/yt/yt/core/misc/unittests/pool_allocator_ut.cpp
  ${CMAKE_SOURCE_DIR}/yt/yt/core/misc/unittests/proc_ut.cpp
  ${CMAKE_SOURCE_DIR}/yt/yt/core/misc/unittests/random_ut.cpp
  ${CMAKE_SOURCE_DIR}/yt/yt/core/misc/unittests/ref_counted_tracker_ut.cpp
  ${CMAKE_SOURCE_DIR}/yt/yt/core/misc/unittests/ring_queue_ut.cpp
  ${CMAKE_SOURCE_DIR}/yt/yt/core/misc/unittests/skip_list_ut.cpp
  ${CMAKE_SOURCE_DIR}/yt/yt/core/misc/unittests/slab_allocator_ut.cpp
  ${CMAKE_SOURCE_DIR}/yt/yt/core/misc/unittests/sliding_window_ut.cpp
  ${CMAKE_SOURCE_DIR}/yt/yt/core/misc/unittests/sync_cache_ut.cpp
  ${CMAKE_SOURCE_DIR}/yt/yt/core/misc/unittests/spsc_queue_ut.cpp
  ${CMAKE_SOURCE_DIR}/yt/yt/core/misc/unittests/statistics_ut.cpp
  ${CMAKE_SOURCE_DIR}/yt/yt/core/misc/unittests/string_ut.cpp
  ${CMAKE_SOURCE_DIR}/yt/yt/core/misc/unittests/sync_expiring_cache_ut.cpp
  ${CMAKE_SOURCE_DIR}/yt/yt/core/misc/unittests/time_formula_ut.cpp
  ${CMAKE_SOURCE_DIR}/yt/yt/core/misc/unittests/tls_expiring_cache_ut.cpp
  ${CMAKE_SOURCE_DIR}/yt/yt/core/misc/unittests/topological_ordering_ut.cpp
  ${CMAKE_SOURCE_DIR}/yt/yt/core/misc/unittests/yverify_ut.cpp
  ${CMAKE_SOURCE_DIR}/yt/yt/core/misc/unittests/zerocopy_output_writer_ut.cpp
  ${CMAKE_SOURCE_DIR}/yt/yt/core/misc/unittests/hedging_manager_ut.cpp
  ${CMAKE_SOURCE_DIR}/yt/yt/core/misc/unittests/safe_memory_reader_ut.cpp
)
add_test(
  NAME
  unittester-core-misc
  COMMAND
  unittester-core-misc
)
set_property(
  TEST
  unittester-core-misc
  PROPERTY
  LABELS
  MEDIUM
)
set_property(
  TEST
  unittester-core-misc
  PROPERTY
  PROCESSORS
  4
)
target_proto_addincls(unittester-core-misc
  ./yt
  ${CMAKE_SOURCE_DIR}/yt
  ${CMAKE_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/yt
  ${CMAKE_SOURCE_DIR}/yt
  ${CMAKE_SOURCE_DIR}/contrib/libs/protobuf/src
  ${CMAKE_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}/contrib/libs/protobuf/src
)
target_proto_outs(unittester-core-misc
  --cpp_out=${CMAKE_BINARY_DIR}/yt
  --cpp_styleguide_out=${CMAKE_BINARY_DIR}/yt
)
vcs_info(unittester-core-misc)
