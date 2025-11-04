# FlipBooQ - Claude AI Development Guide

## Project Overview

**FlipBooQ** is a Qt-based desktop application for automatic white border removal from multiple images simultaneously. The project is designed as an educational and practical tool for batch image processing with a focus on simplicity and efficiency.

**Key Capabilities:**
1. Load multiple images (PNG, JPG, XPM) simultaneously
2. Automatic detection of content boundaries based on background color
3. Unified bounding rectangle calculation across all images
4. Batch export of cropped images
5. Visual preview with flow layout
6. Cross-platform support (Linux, Windows, macOS)

**Educational Focus:** Qt application development, image processing, GUI design patterns, CMake build systems

---

## General Instructions for AI Assistance

### Documentation Standards
- Keep explanations concise and focused
- Use code examples where appropriate
- Reference specific file locations (e.g., `mainwindow.cpp:178`)
- Update this document when implementing major features

### Task Placement
- Add new tasks to `TODO.md` with appropriate priority labels [ADD/WIP/TESTED/APPROVED]
- Mark completed tasks with ✅ and date
- Move current work items from TODO.md to this file's "Current Work" section

### Git & Commits
- Use conventional commit format: `type(scope): description`
- Types: feat, fix, refactor, docs, test, chore, style
- Always test changes before committing
- Keep commits focused and atomic

### Code Organization
- Place UI code in `ui/` directory
- Keep business logic separate from UI (consider `core/` dir for Phase 3)
- Use Qt naming conventions (m_ prefix for members, camelCase)
- Follow existing code style (see CMakeLists.txt compiler flags)

---

## Current Capabilities

### Implemented Features (v0.1)
1. ✅ Image loading via QFileDialog (PNG, JPG, XPM)
2. ✅ Visual preview with FlowLayout (0.5x scale)
3. ✅ Automatic bounding rectangle detection (pixel 0,0 as background)
4. ✅ Unified crop rectangle across all images
5. ✅ Batch export with "export_" prefix
6. ✅ Clear functionality to reset workspace
7. ✅ Qt5/Qt6 dual support via CMake
8. ✅ Strict compiler warnings (GCC)

### Technology Stack
- **Language:** C++17
- **Framework:** Qt5/Qt6 Widgets
- **Build System:** CMake 3.5+
- **Platforms:** Linux (primary), Windows, macOS
- **License:** GNU GPL v3

---

## Architecture

### Core Components
```
FlipBooQ/
├── main.cpp                    # Application entry point
├── ui/
│   ├── mainwindow.h/.cpp      # Main window (load, analyze, save, clear)
│   └── tools/
│       └── flowlayout.h/.cpp  # Flow layout from Qt examples
├── CMakeLists.txt             # Build configuration
├── TODO.md                    # Improvement roadmap
└── CLAUDE.md                  # This file
```

### Key Classes
- **MainWindow**: Central UI controller
  - Image loading and display management
  - Crop algorithm orchestration
  - Export functionality
  - Button state management

- **FlowLayout**: Dynamic layout for image previews (from Qt examples)

### Design Patterns
- Qt Model-View architecture (partial)
- Signals/Slots for event handling
- QPointer for safe widget references

---

## Implementation Standards

### Parameter Definitions
When implementing new features:
1. Define configuration structs for complex settings
2. Use enums for mode selection (e.g., DetectionMode)
3. Provide sensible defaults
4. Store user preferences with QSettings

Example:
```cpp
struct CropSettings {
    enum class DetectionMode {
        CornerPixel,
        AutoDetect,
        ManualColor,
        Threshold
    };
    DetectionMode mode = DetectionMode::AutoDetect;
    int tolerance = 10;
    bool perImageCrop = false;
};
```

### Error Handling
Always validate:
- File existence before loading
- Pixmap validity after creation
- Disk space before saving
- User permissions for write operations

Provide feedback via QMessageBox for errors.

### Memory Management
- Use QPointer for widgets that may be deleted
- Call `qDeleteAll()` when clearing containers
- Delete both widget AND layout item in loops
- Clear containers after deletion

---

## Copyright and Attribution

### Project Files
All original project files (mainwindow.h/.cpp, main.cpp):
```cpp
/*
 * FlipBooQ - Automatic white border removal tool
 * Copyright (C) 2022 Conrad Hübler <Conrad.Huebler@gmx.net>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */
```

### Third-Party Code
- **flowlayout.h/.cpp**: Copyright (C) 2016 The Qt Company Ltd. (BSD License)
- When adding Qt examples, preserve original copyright headers

---

## Build and Test Commands

### Build Instructions
```bash
# Configure
mkdir build && cd build
cmake ..

# Compile
make -j$(nproc)

# Run
./FlipBooQ
```

### CMake Options
```bash
# Force Qt6
cmake -DQT_VERSION_MAJOR=6 ..

# Debug build
cmake -DCMAKE_BUILD_TYPE=Debug ..

# Release build
cmake -DCMAKE_BUILD_TYPE=Release ..
```

### Testing (Phase 3)
```bash
# Run tests
cd build
ctest --output-on-failure

# Run specific test
./tests/test_cropping
```

---

## Current Work

### Active Development [WIP]
*(Move items here from TODO.md when actively working on them)*

**Status:** Planning phase - documentation created
- TODO.md with roadmap created ✅ 2025-01-04
- CLAUDE.md development guide created ✅ 2025-01-04

### Next Up
1. Phase 1.1: Error handling and robustness
2. Phase 1.2: Drag & Drop support
3. Phase 1.3: Export dialog with options

---

## Completed Developments

### Version 0.1 (Initial Release - 2022)
- ✅ Basic Qt application structure
- ✅ Image loading dialog
- ✅ Flow layout for previews
- ✅ Bounding rectangle detection algorithm
- ✅ Batch export functionality
- ✅ CMake build system with Qt5/Qt6 support

### Documentation (2025-01-04)
- ✅ TODO.md roadmap created
- ✅ CLAUDE.md development guide created
- ✅ Four-phase improvement plan established

---

## Development Standards

### Logging System
Currently using `qDebug()` statements:
```cpp
qDebug() << i << "export_" + f.path() + QDir::separator() + "export_" + f.fileName();
```

**Phase 2 Goal:** Replace with structured logging:
```cpp
qCInfo(cropCategory) << "Exporting image" << i << "to" << outputPath;
```

### Configuration Handling
**Current:** Hardcoded values
**Phase 1 Goal:** QSettings-based persistence
```cpp
QSettings settings("FlipBooQ", "FlipBooQ");
settings.setValue("lastDirectory", path);
```

### Unit System
Image coordinates and dimensions use Qt's integer pixel system (QRect, QPoint).

---

## Planned Development

### Phase 1: Foundation (High Priority)
Focus: Stability, basic UX improvements, persistence
- Error handling and validation
- Drag & Drop support
- Zoom slider activation
- Export dialog
- QSettings integration

### Phase 2: Enhancement (Medium Priority)
Focus: Better algorithms, more control
- Improved crop detection (tolerance, multi-corner analysis)
- Settings panel with detection mode options
- Before/After preview split view
- More image format support

### Phase 3: Advanced (Low Priority)
Focus: Performance, testing, CLI
- Full Qt6 migration and C++20
- QtConcurrent for parallel processing
- Command-line interface
- Unit testing framework

### Phase 4: Polish (Future)
Focus: Distribution, professionalization
- Comprehensive documentation
- CI/CD pipeline
- Installers for all platforms
- Internationalization (i18n)

**Breaking Changes:**
- Qt6-only mode (Phase 3): Will drop Qt5 support
- API changes when refactoring to MVC pattern (Phase 3)

---

## Known Issues

### Current Bugs
- [ ] Zoom slider is disabled (mainwindow.cpp:124-128)
- [ ] No error handling for QPixmap::save() failures
- [ ] Potential memory leak in clear() with layout items
- [ ] Pixel (0,0) detection fails for images with dark corners

### Testing Needed
- Large image sets (>100 images)
- Very large individual images (>10000px)
- Images with transparent backgrounds
- Non-square images with extreme aspect ratios

---

## Recently Resolved

*(None yet - initial documentation)*

---

## Key Algorithms

### Bounding Rectangle Detection
**Location:** `mainwindow.cpp:178-190`

**Algorithm:**
1. For each image, convert to QImage
2. Create mask from corner pixel color at (0,0)
3. Convert mask to QRegion and get bounding rect
4. Union all rectangles to get final crop area

**Current Limitation:** Always uses pixel (0,0) as background reference

**Improvement Path (Phase 2):**
```cpp
QRect MainWindow::getRect(const QVector<QPixmap>& pixmaps,
                          const CropSettings& settings) {
    QVector<QRect> rects;
    for (const QPixmap& pix : pixmaps) {
        QImage image = pix.toImage();
        QColor bgColor = detectBackgroundColor(image, settings.mode);
        rects << findContentBounds(image, bgColor, settings.tolerance);
    }

    if (settings.perImageCrop) {
        // Return individual rects
    }

    QRect final;
    for (const QRect& rect : rects) {
        final = final.united(rect);
    }
    return final;
}
```

---

## Project-Specific Conventions

### Widget Naming
- Prefix: `m_` for member variables
- Buttons: descriptive action name (m_load, m_save, m_clear)
- Layouts: type suffix (m_flowLayout, mainLayout)
- Containers: plural form (m_images, m_file_names)

### File Naming
- UI files: lowercase, no prefix (mainwindow.h)
- Utility files: purpose-based (flowlayout.h)
- Future: Consider namespace prefixes for services (cropservice.h)

### Signal/Slot Connections
Prefer new-style connections:
```cpp
connect(m_load, &QPushButton::clicked, this, &MainWindow::load);
```

Avoid old-style SIGNAL/SLOT macros.

---

## Resource Management

### Image Storage
- Stored as QPixmap in QVector<QPixmap>
- Filenames in parallel QStringList
- Views/Scenes in QVector<QPointer<T>>

**Memory Considerations:**
- Large images are not downsampled (just scaled in view)
- All images kept in memory simultaneously
- Phase 3: Consider on-demand loading for large sets

### Layout Management
- FlowLayout manages visual arrangement
- Widgets added to layout, owned by layout
- Must delete widgets explicitly when clearing

---

## Testing Philosophy

### Test-Driven Development (Phase 3+)
When implementing new algorithms:
1. Write test cases first
2. Implement minimal code to pass
3. Refactor while keeping tests green
4. Add edge case tests

### Manual Testing Checklist
Before any commit:
- [ ] Load various image types (PNG, JPG)
- [ ] Test with 1, 10, 100+ images
- [ ] Verify export creates correct files
- [ ] Check memory usage doesn't spike
- [ ] Test clear functionality

---

## AI Development Workflow

### When Adding Features
1. Check TODO.md for priority and phase
2. Update task status to [WIP]
3. Read relevant sections in this file
4. Implement with proper error handling
5. Test manually (Phase 1-2) or with unit tests (Phase 3+)
6. Update TODO.md status to [TESTED]
7. Request code review → [APPROVED]
8. Commit with conventional format
9. Mark task as ✅ with date
10. Update this file's "Completed Developments"

### When Fixing Bugs
1. Add to "Known Issues" if not listed
2. Write failing test case (if Phase 3+)
3. Fix the issue
4. Verify test passes
5. Move to "Recently Resolved" with date

### When Refactoring
1. Ensure current tests pass (Phase 3+)
2. Perform refactoring
3. Verify tests still pass
4. Update documentation if API changed
5. Commit with `refactor(scope):` prefix

---

## References

### Qt Documentation
- Qt Widgets: https://doc.qt.io/qt-6/qtwidgets-index.html
- QPixmap: https://doc.qt.io/qt-6/qpixmap.html
- QImage: https://doc.qt.io/qt-6/qimage.html
- Qt Examples: https://doc.qt.io/qt-6/qtexamples.html

### Project Files
- TODO.md: Detailed improvement roadmap
- CMakeLists.txt: Build configuration and compiler flags
- LICENSE: GNU GPL v3 full text

---

**Last Updated:** 2025-01-04
**Current Version:** 0.1
**Target Version:** 0.2 (Phase 1 completion)
**Maintainer:** Conrad Hübler
**AI Assistant Context:** This file is optimized for Claude Code and similar AI assistants
