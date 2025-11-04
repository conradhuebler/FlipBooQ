# FlipBooQ

A Qt-based desktop application for automatic batch removal of white borders from multiple images simultaneously.

[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
[![Qt Version](https://img.shields.io/badge/Qt-5%20%7C%206-green.svg)](https://www.qt.io/)
[![C++ Standard](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://isocpp.org/)

## Features

- **Batch Processing**: Load and process multiple images at once
- **Automatic Border Detection**: Intelligently detects and removes white (or uniform) borders
- **Visual Preview**: See all images before processing with interactive flow layout
- **Unified Cropping**: Applies consistent crop dimensions across all images
- **Multiple Formats**: Supports PNG, JPG, and XPM image formats
- **Cross-Platform**: Works on Linux, Windows, and macOS
- **Qt Powered**: Modern Qt5/Qt6 interface with responsive design

## Use Cases

Perfect for:
- Scanned document cleanup
- Batch photo processing
- Preparing images for presentations
- Cleaning up screenshot collections
- Academic paper illustrations
- E-book image preparation

## Installation

### Pre-built Binaries (Coming Soon)

Binary releases for Linux, Windows, and macOS will be available on the [Releases](https://github.com/conradhuebler/FlipBooQ/releases) page.

### Build from Source

#### Requirements

- CMake 3.5 or higher
- C++17 compatible compiler (GCC 7+, Clang 5+, MSVC 2017+)
- Qt5 (5.15+) or Qt6 (6.2+) with Widgets module

#### Linux

```bash
# Debian/Ubuntu
sudo apt install build-essential cmake qt6-base-dev

# Fedora/RHEL
sudo dnf install gcc-c++ cmake qt6-qtbase-devel

# Arch Linux
sudo pacman -S base-devel cmake qt6-base
```

#### Windows

1. Install [Qt](https://www.qt.io/download) for Windows
2. Install [CMake](https://cmake.org/download/)
3. Install Visual Studio 2019+ or MinGW

#### macOS

```bash
brew install cmake qt@6
```

#### Building

```bash
# Clone the repository
git clone https://github.com/conradhuebler/FlipBooQ.git
cd FlipBooQ

# Create build directory
mkdir build && cd build

# Configure and build
cmake ..
make -j$(nproc)

# Run
./FlipBooQ
```

For detailed build instructions and troubleshooting, see [docs/BUILDING.md](docs/BUILDING.md).

## Usage

### Basic Workflow

1. **Load Images**: Click "Load Image Files" or drag and drop images into the window
2. **Analyze**: Click "Analyse Images" to detect borders and calculate crop area
3. **Preview**: Review the crop rectangle overlaid on all images
4. **Save**: Click "Save Images" to export cropped versions
5. **Clear**: Click "Clear Images" to start over with new images

### Tips

- **Consistent Backgrounds**: Works best when all images have similar background colors
- **Batch Efficiency**: Process entire folders of images at once
- **Preview Scale**: Images are displayed at 0.5x scale for easier overview
- **Output Location**: Cropped images are saved in the same directory as originals with "export_" prefix

### Example

```bash
# Input:  /home/user/photos/scan001.png (with white borders)
# Output: /home/user/photos/export_scan001.png (cropped)
```

## How It Works

FlipBooQ uses a sophisticated algorithm to detect content boundaries:

1. **Background Detection**: Analyzes the corner pixel (0,0) of each image to determine background color
2. **Mask Creation**: Creates a binary mask separating content from background
3. **Bounding Rectangle**: Calculates the smallest rectangle containing all content
4. **Unified Crop**: Finds the union of all bounding rectangles across all images
5. **Batch Export**: Applies the same crop dimensions to all loaded images

This ensures consistent sizing across your entire image batch.

## Roadmap

FlipBooQ is actively being improved! See [TODO.md](TODO.md) for the complete roadmap.

### Upcoming Features (v0.2)

- **Enhanced Detection**: Multiple corner analysis and tolerance settings
- **Drag & Drop**: Direct file dropping into the application
- **Export Options**: Choose output directory and file naming patterns
- **Settings Panel**: Configure detection modes and parameters
- **Zoom Control**: Interactive zoom slider for preview
- **Better Error Handling**: Comprehensive validation and user feedback

### Future Plans (v0.3+)

- Command-line interface for scripting
- Individual vs. unified crop modes
- More image formats (TIFF, WebP, BMP)
- Before/After comparison view
- Parallel processing for large batches
- Settings persistence
- Dark mode support

## Documentation

- **[TODO.md](TODO.md)** - Development roadmap and planned features
- **[CLAUDE.md](CLAUDE.md)** - AI development guide
- **[docs/ARCHITECTURE.md](docs/ARCHITECTURE.md)** - Technical architecture and algorithms
- **[docs/BUILDING.md](docs/BUILDING.md)** - Detailed build instructions
- **[docs/CONTRIBUTING.md](docs/CONTRIBUTING.md)** - Contribution guidelines

## Contributing

Contributions are welcome! Please see [docs/CONTRIBUTING.md](docs/CONTRIBUTING.md) for guidelines.

### Quick Start for Contributors

1. Check [TODO.md](TODO.md) for open tasks
2. Read [CLAUDE.md](CLAUDE.md) for quick reference
3. Follow the commit format: `type(scope): description`
4. Submit a pull request

## Technology

- **Language**: C++17
- **Framework**: Qt5/Qt6 (Widgets module)
- **Build System**: CMake
- **Image Processing**: Qt's QImage and QPixmap APIs
- **Layout**: Custom FlowLayout (adapted from Qt examples)

## Known Limitations

- Background color is detected from pixel (0,0) - may not work for all images
- All images are kept in memory - very large images or batches may consume significant RAM
- Export filename prefix is currently hardcoded to "export_"

These limitations are being addressed in upcoming versions.

## License

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

See [LICENSE](LICENSE) for the full license text.

## Author

**Conrad Hübler**
- Email: Conrad.Huebler@gmx.net
- GitHub: [@conradhuebler](https://github.com/conradhuebler)

## Acknowledgments

- FlowLayout implementation adapted from Qt examples (Copyright © 2016 The Qt Company Ltd.)
- Built with [Qt](https://www.qt.io/) - Cross-platform application framework

## Support

- **Issues**: Report bugs or request features on [GitHub Issues](https://github.com/conradhuebler/FlipBooQ/issues)
- **Documentation**: Check the [docs/](docs/) directory for detailed information

---

**Version**: 0.1
**Status**: Active Development
**Last Updated**: 2025-01-04
