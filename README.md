OpenGL FreeType2 test
=====================

Test application for rendering text with FreeType2 to an OpenGL texture.

<img src="https://raw.githubusercontent.com/bartjoyce/gl-freetype/master/assets/screenshot.jpg" width="400" />

## Structure

```
- In FreeType:
    - Open font file
    - Get glyph
    - Create a bitmap
- In OpenGL
    - Create a texture
    - Load the bitmap into texture
    - Render the texture
```

## Installation

### 1. Prerequisites

This app has 4 external dependencies:

- **CMake** to build the project,
- **pkg-config** to locate shared libraries,
- **freetype** to read and write video files.

On MacOS using Homebrew, run:

```sh
brew install cmake pkg-config
```

### 2. Clone

```sh
git clone https://github.com/bartjoyce/gl-freetype --recursive
```

The repository includes a submodule for GLFW, so make sure to *recursively* clone the repo. If CMake complains and says it can't find GLFW, it might be because you did not clone it properly. In that case, try:

```sh
git submodule update --init
```

### 3. Build

Inside the repo, create a build directory and run CMake within it:

```sh
mkdir build
cd build
cmake ..
make
```

### 4. Run

```sh
./gl-freetype
```
