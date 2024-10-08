cmake_minimum_required(VERSION 3.30.1)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32")

set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

project(BoilingHotWater VERSION 0.0.1 LANGUAGES CXX)

message(STATUS "CMAKE_INSTALL_PREFIX: ${CMAKE_GENERATOR_PLATFORM}")

add_subdirectory(BHW)

message(STATUS ${CMAKE_GENERATOR_PLATFORM})

include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_CURRENT_SOURCE_DIR}/LICENSE)
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_GENERATOR WIX)
set(CPACK_WIX_VERSION "4.0.0")

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

if(EMSCRIPTEN_BUILD)
    set(EMSCRIPTEN_BUILD_DIR ${CMAKE_CURRENT_BINARY_DIR}/emscripten)

    file(MAKE_DIRECTORY ${EMSCRIPTEN_BUILD_DIR})

    add_custom_target(
        INSTALL_EMSCRIPTEN ALL
        COMMAND emcmake cmake ${CMAKE_CURRENT_SOURCE_DIR} -DEMSCRIPTEN_BUILD=ON && cmake --build ${EMSCRIPTEN_BUILD_DIR} && cmake --install ${EMSCRIPTEN_BUILD_DIR} 
        WORKING_DIRECTORY ${EMSCRIPTEN_BUILD_DIR}
    )
endif()