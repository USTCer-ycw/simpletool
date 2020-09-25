#set(config_srcs
#	PathHelper.h
#	PathHelper.cc
#	ConfigSetting.h
#	ConfigSetting.cc
#	XMLSysPathInfoHandler.h
#	XMLSysPathInfoHandler.cc
#  )

aux_source_directory(. config_srcs)

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/include)


LINK_DIRECTORIES(${PROJECT_SOURCE_DIR})
LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/lib)

add_library(config STATIC ${config_srcs})
target_link_libraries(config utility)
target_link_libraries(config tinyxml2)
