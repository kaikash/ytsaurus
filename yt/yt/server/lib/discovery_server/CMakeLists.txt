
# This file was generated by the build system used internally in the Yandex monorepo.
# Only simple modifications are allowed (adding source-files to targets, adding simple properties
# like target_include_directories). These modifications will be ported to original
# ya.make files by maintainers. Any complex modifications which can't be ported back to the
# original buildsystem will not be accepted.


add_subdirectory(unittests)
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

add_library(server-lib-discovery_server)
target_compile_options(server-lib-discovery_server PRIVATE
  -Wdeprecated-this-capture
)
target_link_libraries(server-lib-discovery_server PUBLIC
  contrib-libs-linux-headers
  contrib-libs-cxxsupp
  yutil
  yt-yt-core
  yt-yt-ytlib
  yt-ytlib-discovery_client
  contrib-libs-protobuf
)
target_proto_messages(server-lib-discovery_server PRIVATE
  ${CMAKE_SOURCE_DIR}/yt/yt/server/lib/discovery_server/proto/discovery_server_service.proto
)
target_sources(server-lib-discovery_server PRIVATE
  ${CMAKE_SOURCE_DIR}/yt/yt/server/lib/discovery_server/config.cpp
  ${CMAKE_SOURCE_DIR}/yt/yt/server/lib/discovery_server/cypress_integration.cpp
  ${CMAKE_SOURCE_DIR}/yt/yt/server/lib/discovery_server/discovery_server.cpp
  ${CMAKE_SOURCE_DIR}/yt/yt/server/lib/discovery_server/group.cpp
  ${CMAKE_SOURCE_DIR}/yt/yt/server/lib/discovery_server/group_manager.cpp
  ${CMAKE_SOURCE_DIR}/yt/yt/server/lib/discovery_server/group_tree.cpp
  ${CMAKE_SOURCE_DIR}/yt/yt/server/lib/discovery_server/helpers.cpp
  ${CMAKE_SOURCE_DIR}/yt/yt/server/lib/discovery_server/member.cpp
)
target_proto_addincls(server-lib-discovery_server
  ./
  ${CMAKE_SOURCE_DIR}/
  ${CMAKE_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/yt
  ${CMAKE_SOURCE_DIR}/contrib/libs/protobuf/src
  ${CMAKE_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}/contrib/libs/protobuf/src
)
target_proto_outs(server-lib-discovery_server
  --cpp_out=${CMAKE_BINARY_DIR}/
  --cpp_styleguide_out=${CMAKE_BINARY_DIR}/
)
