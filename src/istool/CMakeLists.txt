
add_executable(simpletool simpletool.cc)

target_link_libraries(simpletool config)
target_link_libraries(simpletool utility)
target_link_libraries(simpletool tinyxml2)
