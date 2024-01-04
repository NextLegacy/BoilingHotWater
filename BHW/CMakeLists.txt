file(GLOB_RECURSE BHWSources *.cpp)
file(GLOB_RECURSE BHWHeaders *.hpp)

add_library(BHW STATIC ${BHWSources} ${BHWHeaders})

target_include_directories(BHW PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
    $<INSTALL_INTERFACE:include>
)

add_library(BHW::BHW ALIAS BHW)