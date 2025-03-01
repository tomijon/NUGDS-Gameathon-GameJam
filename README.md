# OpenGL Fullscreen Application Template for C++ (Windows)
Use this template to get a basic window opened with an OpenGL context attached. Pressing F11 toggles between FULLSCREEN and WINDOWED mode.

## Setup and Execution

#### Manually Using CMake

This project requires `CMake (minimum 3.31)` to set up. (It might work with lower versions but those have not been tested).

In the root directory:

```cmake
cmake -B build
```

To change the name of the project, change the argument of the project function found at the top of the root CMakeLists.txt.

For building:
```cmake
cmake --build build --config Release // For Release Mode.
cmake --build build --config Debug // For Debug Mode.
```

This will build to either `./build/Release/` or `./build/Debug/` respectively.

#### Using the Batch Scripts

The following batch scripts are available to use:

```
setup.bat            // Runs CMake to build solution.
build-release.bat    // Runs CMake to compile the solution in release mode.
build-debug.bat      // Runs CMake to compile the solution in debug mode.
run-release.bat      // Runs the release mode application.
run-debug.bat        // Runs the debug mode application.
```

Both `run-release.bat` and `run-debug.bat` call the respective `build-mode.bat` files if the release and debug mode builds cannot be found. `build-release.bat` and `build-debug.bat` call `setup.bat` if the `build/` folder does not exist.

### Third Party Libraries

This project uses a number of third party libraries and are fetched automatically by CMake. These are

- Glad (for OpenGL bindings) https://glad.dav1d.de/
- GLFW (For window creation) https://www.glfw.org/
