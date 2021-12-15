file(GLOB_RECURSE CPPS  ./*.cpp )

add_executable(ml_graph ${CPPS})

target_link_libraries(ml_graph nodes)
