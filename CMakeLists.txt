cmake_minimum_required(VERSION 3.20.42)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/install)

project(BoilingHotWater VERSION 0.0.1 LANGUAGES CXX)

add_subdirectory(BHW)

include(GNUInstallDirs)
include(CPack)

install(TARGETS BoilingHotWater
    EXPORT BoilingHotWater
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(
    DIRECTORY BHW
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    PATTERN "CMakeLists.txt" EXCLUDE
    PATTERN "*.cpp" EXCLUDE
)

install(
    EXPORT BoilingHotWater
    NAMESPACE BoilingHotWater::
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/BoilingHotWater
    FILE BoilingHotWaterConfig.cmake
)

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/BoilingHotWaterConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

install(
    FILES ${CMAKE_CURRENT_BINARY_DIR}/BoilingHotWaterConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/BoilingHotWater
)