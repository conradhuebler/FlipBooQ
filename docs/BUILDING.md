# Building FlipBooQ

## Requirements

### All Platforms
- CMake 3.5 or higher
- C++17 compatible compiler
- Qt5 (5.15+) or Qt6 (6.2+)

### Linux
```bash
# Debian/Ubuntu
sudo apt install build-essential cmake qt6-base-dev

# Fedora/RHEL
sudo dnf install gcc-c++ cmake qt6-qtbase-devel

# Arch Linux
sudo pacman -S base-devel cmake qt6-base
```

### Windows
- Visual Studio 2019+ or MinGW
- Qt from https://www.qt.io/download
- CMake from https://cmake.org/download/

### macOS
```bash
# Using Homebrew
brew install cmake qt@6
```

## Building from Source

### Basic Build

```bash
# Clone repository
git clone https://github.com/conradhuebler/FlipBooQ.git
cd FlipBooQ

# Create build directory
mkdir build
cd build

# Configure
cmake ..

# Build
make -j$(nproc)

# Run
./FlipBooQ
```

### CMake Options

#### Force Qt Version
```bash
# Qt6 only
cmake -DQT_VERSION_MAJOR=6 ..

# Qt5 only
cmake -DQT_VERSION_MAJOR=5 ..
```

#### Build Type
```bash
# Debug build (default)
cmake -DCMAKE_BUILD_TYPE=Debug ..

# Release build
cmake -DCMAKE_BUILD_TYPE=Release ..

# Release with debug info
cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo ..
```

#### Installation Prefix
```bash
cmake -DCMAKE_INSTALL_PREFIX=/usr/local ..
make install
```

### Platform-Specific Builds

#### Linux
```bash
# Standard build
mkdir build && cd build
cmake ..
make -j$(nproc)

# Install system-wide
sudo make install
```

#### Windows with Visual Studio
```bash
# Configure for Visual Studio
mkdir build
cd build
cmake -G "Visual Studio 16 2019" ..

# Build
cmake --build . --config Release

# Run
Release\FlipBooQ.exe
```

#### Windows with MinGW
```bash
mkdir build
cd build
cmake -G "MinGW Makefiles" ..
mingw32-make -j4
```

#### macOS
```bash
mkdir build && cd build

# Specify Qt path if needed
cmake -DCMAKE_PREFIX_PATH=/usr/local/opt/qt@6 ..

make -j$(sysctl -n hw.ncpu)

# Create app bundle
open FlipBooQ.app
```

## Advanced Build Options

### Verbose Build
```bash
make VERBOSE=1
```

### Parallel Build
```bash
# Linux/macOS
make -j$(nproc)

# Specify exact number
make -j4
```

### Clean Build
```bash
# Clean build artifacts
make clean

# Complete rebuild
rm -rf build
mkdir build && cd build
cmake .. && make
```

## Testing (Phase 3+)

```bash
# Build with tests enabled
cmake -DBUILD_TESTING=ON ..
make

# Run all tests
ctest

# Verbose test output
ctest --output-on-failure

# Run specific test
./tests/test_cropping
```

## Creating Packages (Phase 4)

### Linux Packages

#### DEB Package
```bash
cmake -DCMAKE_INSTALL_PREFIX=/usr ..
make package
# Creates: FlipBooQ-0.1-Linux.deb
```

#### RPM Package
```bash
cmake -DCMAKE_INSTALL_PREFIX=/usr ..
make package
# Creates: FlipBooQ-0.1-Linux.rpm
```

#### AppImage
```bash
# Install linuxdeploy
# Build and deploy
make install DESTDIR=AppDir
linuxdeploy --appdir AppDir --output appimage
```

### Windows Installer

```bash
# Install NSIS
cmake -DCMAKE_INSTALL_PREFIX=C:/FlipBooQ ..
cmake --build . --target package
# Creates: FlipBooQ-0.1-win64.exe
```

### macOS DMG

```bash
cmake ..
make
macdeployqt FlipBooQ.app -dmg
# Creates: FlipBooQ.dmg
```

## Troubleshooting

### Qt Not Found
```bash
# Specify Qt installation path
cmake -DCMAKE_PREFIX_PATH=/path/to/Qt/6.5.0/gcc_64 ..
```

### Compiler Not Found
```bash
# Specify compilers
cmake -DCMAKE_CXX_COMPILER=g++-11 ..
```

### Linking Errors
```bash
# Clear CMake cache
rm CMakeCache.txt
cmake ..
```

### Missing Dependencies
```bash
# Check required Qt modules
cmake .. 2>&1 | grep "Could not find"
```

## Build Performance

### Recommended Settings

**For development (fast iteration):**
```bash
cmake -DCMAKE_BUILD_TYPE=Debug ..
make -j$(nproc)
```

**For testing:**
```bash
cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo ..
make -j$(nproc)
```

**For distribution:**
```bash
cmake -DCMAKE_BUILD_TYPE=Release ..
make -j$(nproc)
strip FlipBooQ  # Remove debug symbols
```

## IDE Integration

### Qt Creator
1. Open CMakeLists.txt as project
2. Configure build directory
3. Build → Run

### Visual Studio Code
```json
// .vscode/settings.json
{
    "cmake.configureArgs": [
        "-DCMAKE_BUILD_TYPE=Debug"
    ]
}
```

### CLion
1. Open project folder
2. CLion auto-detects CMake
3. Run/Debug configurations available

## Cross-Compilation

### Linux → Windows (MinGW)
```bash
cmake -DCMAKE_TOOLCHAIN_FILE=mingw-w64.cmake ..
```

### Linux → Android (Phase 4)
```bash
# Set Qt Android paths
export ANDROID_NDK=/path/to/ndk
cmake -DANDROID_PLATFORM=android-28 ..
```
