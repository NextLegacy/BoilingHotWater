file(GLOB_RECURSE BHWSources ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE BHWHeaders ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)

add_library(BHW ${BHWSources} ${BHWHeaders})

target_include_directories(BHW PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
    $<INSTALL_INTERFACE:include>
)

add_library(BHW::BHW ALIAS BHW)