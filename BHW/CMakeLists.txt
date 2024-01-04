file(GLOB_RECURSE BoilingHotWaterSources *.cpp)
file(GLOB_RECURSE BoilingHotWaterHeaders *.hpp)

add_library(BoilingHotWater STATIC ${BoilingHotWaterSources} ${BoilingHotWaterHeaders})

target_include_directories(BoilingHotWater PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
    $<INSTALL_INTERFACE:include>
)

add_library(BoilingHotWater::BoilingHotWater ALIAS BoilingHotWater)