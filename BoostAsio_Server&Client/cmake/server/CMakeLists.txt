include_directories($(Logger_SOURCE_DIR}/server/src)
link_directories($(Logger_SOURCE_DIR}/server/src)
add_executable(server main.cpp log_server.cpp session.cpp)