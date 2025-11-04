# CLAUDE.md - AI Development Guide

Quick reference for AI assistants working on FlipBooQ.

## Project Summary
Qt C++17 desktop app for batch image cropping (automatic white border removal).
**Current:** v0.1 | **Target:** v0.2 | **License:** GPL v3

## Key Files
- `TODO.md` - Development roadmap with 4 phases
- `docs/ARCHITECTURE.md` - Detailed architecture & algorithms
- `docs/BUILDING.md` - Build instructions
- `docs/CONTRIBUTING.md` - Contribution workflow
- `ui/mainwindow.cpp:178` - Core crop algorithm

## Quick Build
```bash
mkdir build && cd build && cmake .. && make -j$(nproc)
```

## Development Workflow
1. Check `TODO.md`, update task to [WIP]
2. Read `docs/ARCHITECTURE.md` for relevant section
3. Implement with error handling
4. Test (see checklist below)
5. Update `TODO.md` to [TESTED]
6. Commit: `type(scope): description`
7. Mark ✅ with date in TODO.md

## Commit Format
```
type(scope): brief description

- Detailed changes
- Reference issues

Types: feat, fix, refactor, docs, test, chore
Scopes: ui, core, export, settings, build
```

## Code Standards
```cpp
// Naming
QVector<QPixmap> m_images;        // Members: m_ prefix
void loadImage(const QString& path);  // Functions: camelCase

// Signals/Slots (new-style only)
connect(m_load, &QPushButton::clicked, this, &MainWindow::load);

// Error handling (always validate)
if (!QFile::exists(file)) {
    QMessageBox::warning(this, tr("Error"), tr("File not found"));
    return false;
}

// Memory (delete widget AND layout item)
while ((item = layout->takeAt(0))) {
    delete item->widget();
    delete item;
}
```

## Testing Checklist
- [ ] Load PNG, JPG, mixed formats
- [ ] Test 1, 10, 50+ images
- [ ] Verify exports are correct
- [ ] Check memory usage
- [ ] Test clear functionality

## Current Work [WIP]
- Documentation restructured ✅ 2025-01-04

Next: Phase 1.1 - Error handling & robustness

## Known Issues
- Zoom slider disabled (mainwindow.cpp:124-128)
- No error handling for save failures
- Memory leak in clear() with layout items
- Pixel (0,0) detection unreliable

## Copyright Headers
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
Third-party: Preserve original headers (e.g., Qt examples)

## Documentation Structure
- **CLAUDE.md** (this file): AI quick reference
- **README.md**: User-facing documentation
- **TODO.md**: Development roadmap
- **docs/ARCHITECTURE.md**: Technical details
- **docs/BUILDING.md**: Build & packaging
- **docs/CONTRIBUTING.md**: Contribution guide

---
**Last Updated:** 2025-01-04 | **Maintainer:** Conrad Hübler
