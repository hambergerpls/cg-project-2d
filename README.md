# 2D Computer Graphics Project
2D Computer Graphics Project using openGL and FreeGLUT

This project is for KT34303 - Computer Graphics course of Universiti Malaysia Sabah

## Team
- Lee Kim Hao
- Tan Mei Jun
- Nizam Bin Nordin
- Kennedy Gregory Mojuntin
- Ahmad Farhan Bin Ahmad Zaki
- Muhammad Danial Aiman Bin Mohd Hanif

## Setting up the project
### Requirements
- [Build Tools for Visual Studio 2019](https://visualstudio.microsoft.com/)
- [Visual Studio Code](https://code.visualstudio.com/) as our coding environment and setup.
- [CMake](https://cmake.org/download/) as our cross-platform configuration tool.
- [git](https://git-scm.com/downloads) is a **must** for development.

### Windows
#### Setting up the Build Tools for VS Code
You can follow this guide on how to install Build Tools(just follow the Prerequisite 1-3) (https://code.visualstudio.com/docs/cpp/config-msvc) on how to install the required C++ compiler.
#### Setting up vcpkg library manager to install FreeGLUT and OpenGL libraries
After you installed cmake and git, open the command prompt and type the following command to install `vcpkg`
```cmd
> cd C:\ 
> git clone https://github.com/microsoft/vcpkg
```
The above command should install vcpkg to `C:\vcpkg`. Then type the following command
```cmd
> .\vcpkg\bootstrap-vcpkg.bat
```
This will set up the necesssary configuration. Finally, install the FreeGLUT library with the following command
```cmd
> .\vcpkg\vcpkg install opengl:x64-windows
> .\vcpkg\vcpkg install freeglut:x64-windows
```
This will take a while, you will know the process is finished if the command prompt shows the following:
```
...
The package freeglut is compatible with built-in CMake targets:

    find_package(GLUT REQUIRED)
    target_link_libraries(main PRIVATE GLUT::GLUT)
...
```

### Linux
#### Setting up the C++ compiler for VS Code and install FreeGLUT
On Linux, the library installation is straight forward. Make sure you installed `build-essential` to install the required compilers and development libraries. Use your package manager to install FreeGLUT library `freeglut3-dev`
```sh
$ sudo apt get update
$ sudo apt get install build-essential
$ sudo apt get install freeglut3-dev
```

### Cloning this repo
To clone this repo, create a project folder anywhere you want.
Open command prompt or terminal in that folder and run the following command
```cmd
> git clone https://github.com/screamingDanana/cg-project-2d.git
```
The above command should clone this repo to your desired directory.

Or just download this repo as zip and extract it to your desired location.

### Setting up VS Code workspace
Open up Visual Studio Code and install the following extensions from the marketplace
- C/C++
- CMake
- CMake Tools

Next, go to `File>Open Folder...` then select the folder that you have just cloned, e.g `<your project directory>/cg-project-2d`

Press `Ctrl+Shift+P` to open vscode command pallete and type `cmake`. You should see `CMake: Configure` in the list, select it.

Next, it should list all the available compilers on your computer. For **Windows**, it should show a list like `Microsoft Visual Studio Build Tools 2019 x86_64` or something along the lines. Select the one with `x86_64` compiler. On **Linux**, select the latest GCC Compiler. It should automatically detect `CMakeList.txt` and configure the project.

### Configuring launch task
Make sure at the bottom it says `Cmake: [Release]: Ready`. If not, click on it and select `"Release"` Press `F7` to compile the program. This should create the executable `opengl_program.exe` for Windows or `opengl_program` for Linux.

**For Windows**: Press `F5` and select `C++ (Windows)`. A launch.json configuration file should open.
Change the `"program"` field to `"${workspaceFolder}/build/Release/opengl_program.exe"` you can look for the executable inside the build folder (should be in Release)

Your program field in launch.json should look like this
```json
...
"program": "${workspaceFolder}/build/Release/opengl_program.exe"
...
```
After that, save the file and press `F5`, the program should run.

**For Linux**: Press `F5` and select `C++ (GDB/LLDB)`. A launch.json configuration file should open.
Change the `"program"` field to `"${workspaceFolder}/build/opengl_program"`

Your program field in launch.json should look like this
```json
...
"program": "${workspaceFolder}/build/opengl_program"
...
```
After that, save the file and press `F5`, the program should run.

## License
This project is licensed under [MIT License](LICENSE)
