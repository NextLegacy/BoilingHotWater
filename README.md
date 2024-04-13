# BoilingHotWater

## Pretty accurate representation of the disk utilization :)
<img src='https://github.com/siveryt/BoilingHotWater/assets/50551841/8d1253a7-f8a6-472a-be33-f3799d2beb86' width='400'>

> made with :fire: by [@Sivery](https://github.com/siveryt)

## Abstract
This is a dependency-free cross-platform C++ library with various general-purpose utilities, which aims to abstract away platform-specific code and provide a simple and easy-to-use interface.

It's worth mentioning that it is currently under development; consequently, **eveything is subject to change and may not work as intendent**, furthermore, **the only supported platform currently is Windows**.

Originally, I wrote this library for my game engine, [TeaPot](https://github.com/NextLegacy/Engine), hence the name `BoilingHotWater`. I decided to split it off into its own repository to facilitate its use in future projects of mine.

This is pretty much just here so that I can get my hand on various concepts and algorithms and implement them by myself to get a good look and understanding of how they work; I thought: before I throw in a bunch of libraris on my projects, I may as well, for the sake of learning a thing or two, reinvent the wheel in the process.

Feel free to grab code snippets or the whole library if you find it useful, but keep in mind that it is still under development and may not be suitable for production use.

## Table of Contents
- [BoilingHotWater](#boilinghotwater)
  - [Pretty accurate representation of the disk utilization :)](#pretty-accurate-representation-of-the-disk-utilization-)
  - [Abstract](#abstract)
  - [Table of Contents](#table-of-contents)
  - [Currently Supported Platforms](#currently-supported-platforms)
  - [Features](#features)
  - [Examples](#examples)
  - [Build and Install](#build-and-install)
    - [CMake](#cmake)
  - [License](#license)

## Currently Supported Platforms
- [X] Windows
- [ ] Linux
- [ ] MacOS
- [X] Web (via Emscripten)

## Features

A quick overview of partially implemented and planed features:

- [X] Reflection
- [X] Entity Component System 
- [X] Threading
- [X] Random Number Generation ([Xoshiro256**](https://prng.di.unimi.it/))
- [X] Serialization (JSON)
- [X] Logging (subject to change)
- [X] File Handling (gets the job done, but is not recommended at its current state)
- [X] String Utilities
- [X] Time
- [ ] Math (Vector, Matrix, Quaternion, etc.)
- [ ] Networking
- [ ] ... and more to come!

## Examples
  
There are currently no examples, apart from my game engine [TeaPot](https://github.com/NextLegacy/Engine), that utilize this library.

## Build and Install

### CMake

This library uses [CMake](https://cmake.org/) as its build system.

To build and Install the library, you can run the following commands:

```bash
# Explicitly specify a build directory.
cmake -B build

# Optionally, you can specify the install directory. By default this will be set to "/usr/local" on UNIX, and "<SystemDrive>/Program Files/<ProjectName>" on Windows
cmake -B build -D CMAKE_INSTALL_PREFIX=PATH_TO_INSTALL_DIR

# Build the library in Release mode. The Library will be installed in the install directory.
cmake --build build --target INSTALL --config Release

# Use the custom target INSTALL_EMSCRIPTEN to install the library for web.
cmake --build build --target INSTALL_EMSCRIPTEN
```

afterwards, you can link the library to your project by adding the following to your `CMakeLists.txt`:

```cmake
find_package(BoilingHotWater REQUIRED)
target_link_libraries(<your-target> PUBLIC BoilingHotWater::BoilingHotWater)
```

make sure to set the BoilingHotWater_DIR to the install directory if you have specified a custom install directory. You may do this trough the folwing ways:

```bash
# Set the BoilingHotWater_DIR environment variable to the install directory
cmake -D BoilingHotWater_DIR=PATH_TO_INSTALL_DIR
```

or
  
```cmake
set(BoilingHotWater_DIR PATH_TO_INSTALL_DIR)
```

or

```cmake
list(APPEND CMAKE_PREFIX_PATH path/to/BoilingHotWater/install)
```

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
