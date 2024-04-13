file(GLOB_RECURSE BoilingHotWaterSources *.cpp)
file(GLOB_RECURSE BoilingHotWaterHeaders *.hpp)

add_library(BoilingHotWater STATIC ${BoilingHotWaterSources} ${BoilingHotWaterHeaders})

target_include_directories(BoilingHotWater PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
    $<INSTALL_INTERFACE:include>
)

set_target_properties(BoilingHotWater PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")