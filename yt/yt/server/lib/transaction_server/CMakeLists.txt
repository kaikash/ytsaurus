
# This file was generated by the build system used internally in the Yandex monorepo.
# Only simple modifications are allowed (adding source-files to targets, adding simple properties
# like target_include_directories). These modifications will be ported to original
# ya.make files by maintainers. Any complex modifications which can't be ported back to the
# original buildsystem will not be accepted.



add_library(server-lib-transaction_server)
target_compile_options(server-lib-transaction_server PRIVATE
  -Wdeprecated-this-capture
)
target_link_libraries(server-lib-transaction_server PUBLIC
  contrib-libs-linux-headers
  contrib-libs-cxxsupp
  yutil
  yt-yt-ytlib
)
target_sources(server-lib-transaction_server PRIVATE
  ${CMAKE_SOURCE_DIR}/yt/yt/server/lib/transaction_server/helpers.cpp
  ${CMAKE_SOURCE_DIR}/yt/yt/server/lib/transaction_server/timestamp_proxy_service.cpp
)
