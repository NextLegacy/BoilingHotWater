# BoilingHotWater

## Pretty accurate representation of the disk utilization :)
<img src='https://github.com/siveryt/BoilingHotWater/assets/50551841/8d1253a7-f8a6-472a-be33-f3799d2beb86' width='400'>

> made with :fire: by [@Sivery](https://github.com/siveryt)

## Abstract
This is a dependency-free cross-platform C++ library with various general-purpose utilities, which aims to abstract away platform-specific code and provide a simple and easy-to-use interface.

It's worth mentioning that it is currently under development; consequently, **eveything is subject to change and may not work as intendent**, furthermore, **the only supported platform currently is Windows**.

Originally, I wrote this library for my game engine, [TeaPot](https://github.com/NextLegacy/Engine), hence the name `BoilingHotWater`. I decided to split it off into its own repository to facilitate its use in future projects of mine.

## Table of Contents
- [BoilingHotWater](#boilinghotwater)
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

## Features

A quick overview of partially implemented and planed features:

- [X] Logging (subjey to change)
- [X] File Handling (not recommended currently)
- [X] String Utilities
- [X] Entity Component System 
- [X] Serialization (JSON)
- [X] Threading
- [X] Reflection
- [X] Random Number Generation ([Xoshiro256**](https://prng.di.unimi.it/))
- [X] Time
- [ ] Math (Vector, Matrix, Quaternion, etc.)
- [ ] Networking
- [ ] ... and more to come!

## Examples
  
There are currently no examples, apart from my game engine [TeaPot](https://github.com/NextLegacy/Engine), that utilizes this library.

## Build and Install

### CMake

This library uses [CMake](https://cmake.org/) as its build system.

To build and Install the library, you can run the following commands:

```bash	
cmake --build build --target ALL_BUILD --config Release
cmake --build build --target INSTALL --config Release
```

afterwards, you can link the library to your project by adding the following to your `CMakeLists.txt`:

```cmake
list(APPEND CMAKE_PREFIX_PATH path/to/BoilingHotWater/install)
find_package(BHW REQUIRED)
target_link_libraries(<your-target> PRIVATE BHW::BHW)
```

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
