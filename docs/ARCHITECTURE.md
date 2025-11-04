# FlipBooQ Architecture

## Project Structure

```
FlipBooQ/
├── main.cpp                    # Application entry point
├── ui/
│   ├── mainwindow.h/.cpp      # Main window (load, analyze, save, clear)
│   └── tools/
│       └── flowlayout.h/.cpp  # Flow layout from Qt examples
├── docs/                       # Documentation
├── CMakeLists.txt             # Build configuration
├── TODO.md                    # Improvement roadmap
└── CLAUDE.md                  # AI development guide
```

## Core Components

### MainWindow (ui/mainwindow.h/.cpp)
Central UI controller responsible for:
- Image loading and display management
- Crop algorithm orchestration
- Export functionality
- Button state management

**Key Methods:**
- `addFile()`: Load single image, create view/scene
- `load()`: File dialog for multiple images
- `get()`: Calculate bounding rectangle
- `save()`: Export cropped images
- `clear()`: Reset workspace
- `getRect()`: Core crop detection algorithm

### FlowLayout (ui/tools/flowlayout.h/.cpp)
Dynamic layout from Qt examples for flexible image arrangement.

## Design Patterns

- **Qt Model-View**: Partial implementation with QGraphicsView/Scene
- **Signals/Slots**: Event handling throughout
- **RAII**: Resource management with Qt parent-child ownership

## Data Flow

```
Load Images → Display in FlowLayout → Analyze (getRect) →
Visualize Crop Rectangle → Export Cropped Images
```

## Key Algorithms

### Bounding Rectangle Detection (mainwindow.cpp:178-190)

**Current Implementation:**
1. For each image, convert QPixmap to QImage
2. Get background color from pixel at (0,0)
3. Create mask: `QBitmap::fromImage(image.createMaskFromColor(bgColor))`
4. Convert mask to QRegion and extract bounding rectangle
5. Union all rectangles: `final = final.united(rect)`

**Algorithm Pseudo-code:**
```
function getRect(images[]):
    rects = []
    for each image in images:
        bgColor = image.pixel(0,0)
        mask = createMaskFromColor(bgColor)
        rect = mask.boundingRect()
        rects.append(rect)

    finalRect = empty
    for each rect in rects:
        finalRect = union(finalRect, rect)

    return finalRect
```

**Limitations:**
- Always uses pixel (0,0) as reference
- No tolerance for color variations
- No multi-corner analysis
- Unified crop only (no per-image option)

**Planned Improvements (Phase 2):**
- Multi-corner background detection
- Tolerance-based matching
- Individual vs. unified crop modes

## Memory Management

### Image Storage
- **m_images**: QVector<QPixmap> - Full resolution in memory
- **m_file_names**: QStringList - Parallel array of paths
- **m_image_view**: QVector<QPointer<QGraphicsView>> - View widgets
- **m_image_scene**: QVector<QPointer<QGraphicsScene>> - Scene objects

### Resource Cleanup
Critical: When clearing, must delete:
1. Pixmaps (automatic via clear())
2. Scenes (qDeleteAll)
3. Views (qDeleteAll)
4. Layout items AND their widgets

## Threading Considerations

**Current:** Single-threaded, all operations on main UI thread

**Future (Phase 3):**
- QtConcurrent for parallel image processing
- Worker threads for crop analysis
- Async export with progress updates

## Qt Version Compatibility

Code supports both Qt5 and Qt6 via CMake detection:
```cmake
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
```

**Qt5 vs Qt6 differences handled:**
- Executable creation (qt_add_executable vs add_executable)
- Container preferences (QVector vs QList)
- CMake helper functions

## Build System

### CMake Structure
- Minimum version: 3.5
- C++ standard: 17
- Auto-tools: AUTOUIC, AUTOMOC, AUTORCC
- Strict compiler warnings for GCC (40+ flags)

### Compiler Flags
Extensive warning flags enabled for GCC:
- All standard warnings (-Wall -Wextra -pedantic)
- Format security checks
- Uninitialized variable detection
- Type safety warnings
- Notable exclusions: -Wno-deprecated-declarations

## Future Architecture (Phase 3+)

### Planned Refactoring

**Service Layer:**
```
core/
├── cropservice.h/.cpp        # Crop algorithm logic
├── exportservice.h/.cpp      # Export operations
└── settingsservice.h/.cpp    # Configuration management
```

**Enhanced MVC:**
- Model: ImageCollection class
- View: MainWindow + custom widgets
- Controller: Service classes + coordinators

**Testing Layer:**
```
tests/
├── test_cropping.cpp         # Algorithm tests
├── test_export.cpp           # Export tests
└── fixtures/                 # Test images
```
