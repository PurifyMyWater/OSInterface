# Copilot Instructions for OSInterface

## Project Overview
OSInterface is a C++ interface library that provides target-specific functions to other components. It defines abstract interfaces for OS-level operations like threading, synchronization, timers, and memory management.

## Language and Standards
- **Language**: C++
- **Standard**: C++23
- **Build System**: CMake (minimum version 3.16)

## Code Style and Standards
- Follow the `.clang-format` configuration for code formatting
- Adhere to `.clang-tidy` rules for code quality
- Use clear, descriptive names for functions, variables, and types
- Include comprehensive Doxygen comments for all public APIs
- Prefer standard library types (e.g., `uint32_t`, `std::string`) over platform-specific types

## Architecture Guidelines
- This is an **interface library** - it defines pure virtual classes that must be implemented by platform-specific code
- All methods in the `OSInterface` class are pure virtual (`= 0`)
- Implementations are provided by platform-specific derived classes (not part of this repository)
- Do not add platform-specific implementations to this repository

## Build and Test
- Configure: `cmake -DCMAKE_BUILD_TYPE=Release -S . -B ./build`
- Build: `cmake --build ./build`
- The project uses static library target: `OSInterface`

## CI/CD
- The CI pipeline uses `cpp-linter-action` for code quality checks
- Both clang-format and clang-tidy checks must pass
- The pipeline runs on pushes to `main` and `develop` branches and on pull requests

## Header Files Organization
- All public headers are located in `Source/include/`
- Main header: `OSInterface.h` includes all other interface headers
- Individual interface headers:
  - `OSInterface_Log.h` - Logging functionality
  - `OSInterface_Mutex.h` - Mutex synchronization
  - `OSInterface_BinarySemaphore.h` - Binary semaphore
  - `OSInterface_Timer.h` - Timer functionality

## When Making Changes
1. Ensure all changes maintain the abstract interface nature of the library
2. Update Doxygen documentation for any API changes
3. Run clang-format and clang-tidy locally before committing
4. Keep the interface minimal and focused on core OS abstraction needs
5. Consider thread-safety and callback execution contexts in design

## Key Design Principles
- **Abstract Interface**: Define contracts, not implementations
- **Platform Independence**: No platform-specific code in interfaces
- **Resource Management**: Document ownership and lifecycle of created objects
- **Thread Safety**: Clearly document thread-safety guarantees and requirements
- **Minimal Dependencies**: Keep external dependencies minimal

## CODEOWNERS
- Changes will be reviewed by @vacmg and @aom20021
