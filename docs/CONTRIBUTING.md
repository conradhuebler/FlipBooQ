# Contributing to FlipBooQ

Thank you for your interest in contributing to FlipBooQ! This document provides guidelines and instructions for contributing.

## Development Workflow

### 1. Choose a Task
- Check `TODO.md` for prioritized tasks
- Look for tasks marked `[ADD]` (not yet started)
- Higher phases (1-2) are prioritized over lower phases (3-4)

### 2. Update Task Status
- Change status from `[ADD]` to `[WIP]` (Work In Progress)
- This prevents duplicate work

### 3. Create Feature Branch
```bash
git checkout -b feature/short-description
# Examples:
# feature/drag-drop
# feature/export-dialog
# fix/memory-leak-clear
```

### 4. Development
- Read relevant sections in `CLAUDE.md` and `docs/ARCHITECTURE.md`
- Follow coding standards (see below)
- Write tests if Phase 3+ (unit tests with Qt Test)

### 5. Testing
**Manual Testing (Phase 1-2):**
- [ ] Load various image types (PNG, JPG, mixed)
- [ ] Test with 1, 10, 50+ images
- [ ] Verify export creates correct files
- [ ] Check UI responsiveness
- [ ] Test clear functionality
- [ ] Test on at least 2 platforms if possible

**Automated Testing (Phase 3+):**
```bash
cd build
make test
# or
ctest --output-on-failure
```

### 6. Update Documentation
- Update `TODO.md` status to `[TESTED]`
- Update `CLAUDE.md` if APIs changed
- Add entry to `docs/ARCHITECTURE.md` if new components
- Update `README.md` if user-facing features

### 7. Commit
Follow conventional commit format:
```bash
git commit -m "type(scope): brief description

- Detailed change 1
- Detailed change 2
- Closes #issue-number (if applicable)
"
```

**Types:**
- `feat`: New feature
- `fix`: Bug fix
- `refactor`: Code restructuring without behavior change
- `docs`: Documentation changes
- `test`: Adding or updating tests
- `chore`: Maintenance tasks (dependencies, build config)
- `style`: Formatting, whitespace

**Scopes:**
- `ui`: User interface changes
- `core`: Core algorithm/logic
- `export`: Export functionality
- `settings`: Settings/preferences
- `build`: Build system (CMake)

**Examples:**
```
feat(ui): Add drag and drop support for images
fix(core): Correct bounding box calculation for transparent images
refactor(export): Extract export logic to separate service class
docs(readme): Add usage examples and screenshots
```

### 8. Push and Create PR
```bash
git push origin feature/short-description
```
Create Pull Request on GitHub with:
- Clear description of changes
- Reference to TODO.md item
- Screenshots for UI changes
- Testing performed

### 9. Code Review
- Mark TODO.md as `[APPROVED]` after review
- Address review feedback
- Squash commits if requested

### 10. After Merge
- Mark TODO.md item as ✅ with date
- Update `CLAUDE.md` "Completed Developments" section
- Delete feature branch

## Coding Standards

### C++ Style

#### Naming Conventions
```cpp
// Member variables: m_ prefix
QVector<QPixmap> m_images;
QPushButton* m_loadButton;

// Local variables: camelCase
QString fileName;
int imageCount;

// Functions: camelCase
void loadImage(const QString& path);

// Classes: PascalCase
class ImageProcessor;

// Constants: UPPER_SNAKE_CASE or kPrefix
const int MAX_IMAGE_SIZE = 10000;
constexpr double kDefaultScale = 0.5;
```

#### Code Formatting
```cpp
// Braces: K&R style (opening brace on same line)
void MainWindow::load() {
    if (condition) {
        doSomething();
    } else {
        doSomethingElse();
    }
}

// Indentation: 4 spaces (no tabs)
void function() {
    if (condition) {
        statement;
    }
}

// Pointer/reference alignment: with type
QString* pointer;
const QString& reference;
```

#### Qt Conventions
```cpp
// Prefer new-style signals/slots
connect(button, &QPushButton::clicked, this, &MainWindow::onButtonClicked);

// Not:
connect(button, SIGNAL(clicked()), this, SLOT(onButtonClicked()));

// Use const references for parameters
void addImage(const QString& path, const QPixmap& pixmap);

// Use auto where type is obvious
auto* button = new QPushButton("Click me");
auto result = computeValue();

// Range-based loops
for (const auto& image : m_images) {
    processImage(image);
}
```

### Error Handling

```cpp
// Always validate input
bool MainWindow::addFile(const QString& file) {
    if (!QFile::exists(file)) {
        QMessageBox::warning(this, tr("Error"),
                           tr("File not found: %1").arg(file));
        return false;
    }

    QPixmap pix(file);
    if (pix.isNull()) {
        QMessageBox::warning(this, tr("Error"),
                           tr("Cannot load image: %1").arg(file));
        return false;
    }

    // Process...
    return true;
}

// Use return codes or exceptions appropriately
// Provide user feedback for errors
```

### Memory Management

```cpp
// Prefer Qt parent-child ownership
auto* widget = new QWidget(parent);  // Parent owns, will delete

// Use QPointer for widgets that may be deleted
QPointer<QWidget> safePointer = widget;
if (safePointer) {
    safePointer->show();
}

// Clear containers properly
qDeleteAll(m_widgets);
m_widgets.clear();

// Delete layout items with widgets
QLayoutItem* item;
while ((item = layout->takeAt(0))) {
    delete item->widget();  // Delete widget first
    delete item;            // Then layout item
}
```

### Documentation

```cpp
/**
 * @brief Detects content bounding rectangle in images
 *
 * Analyzes all provided images to find the smallest rectangle
 * containing all non-background content across all images.
 *
 * @param pixmaps Vector of images to analyze
 * @param settings Detection settings (mode, tolerance, etc.)
 * @return Unified bounding rectangle, or empty rect if no content
 *
 * @note Background color is determined based on settings.mode
 * @see CropSettings for configuration options
 */
QRect getRect(const QVector<QPixmap>& pixmaps,
              const CropSettings& settings);
```

## Testing Guidelines

### Unit Tests (Phase 3+)

```cpp
// tests/test_cropping.cpp
#include <QtTest>

class TestCropping : public QObject {
    Q_OBJECT

private slots:
    void initTestCase() {
        // Setup before all tests
    }

    void testWhiteBorderDetection() {
        // Arrange
        QImage img(100, 100, QImage::Format_RGB32);
        img.fill(Qt::white);
        QPainter p(&img);
        p.fillRect(20, 20, 60, 60, Qt::black);

        // Act
        QRect bounds = detectContentBounds(img, Qt::white, 0);

        // Assert
        QCOMPARE(bounds, QRect(20, 20, 60, 60));
    }

    void cleanupTestCase() {
        // Cleanup after all tests
    }
};

QTEST_MAIN(TestCropping)
#include "test_cropping.moc"
```

### Test Coverage Goals
- Phase 3: Core algorithms (>80% coverage)
- Phase 4: UI interactions (>60% coverage)

## Documentation Standards

### Code Comments
```cpp
// Use comments for "why", not "what"
// Good:
// Use tolerance to handle JPEG compression artifacts
const int tolerance = 10;

// Bad:
// Set tolerance to 10
const int tolerance = 10;

// Complex algorithms need explanation
// Calculate unified bounding box by taking the union of all
// individual content rectangles. This ensures consistent cropping
// across all images in the batch.
for (const QRect& rect : rects) {
    final = final.united(rect);
}
```

### Commit Messages
```
feat(ui): Add drag and drop support for image loading

- Implement dragEnterEvent and dropEvent handlers
- Support multiple files dropped simultaneously
- Show visual feedback during drag operation
- Filter for supported image formats only

Closes #42
```

### Pull Request Template
```markdown
## Description
Brief description of changes

## Related Issue
Closes #issue-number

## Type of Change
- [ ] Bug fix
- [ ] New feature
- [ ] Breaking change
- [ ] Documentation update

## Testing
- [ ] Manual testing performed
- [ ] Unit tests added/updated
- [ ] All tests passing

## Screenshots (if UI changes)
[Add screenshots here]

## Checklist
- [ ] Code follows project style guidelines
- [ ] Documentation updated
- [ ] TODO.md updated
- [ ] No compiler warnings
```

## Review Process

### What Reviewers Look For
1. **Correctness**: Does it solve the problem?
2. **Style**: Follows coding standards?
3. **Tests**: Adequate test coverage?
4. **Documentation**: Code and docs updated?
5. **Performance**: No obvious bottlenecks?
6. **Memory**: No leaks or dangling pointers?

### Review Response
- Be open to feedback
- Ask questions if unclear
- Make requested changes promptly
- Mark conversations as resolved

## Getting Help

### Resources
- **Qt Documentation**: https://doc.qt.io/
- **TODO.md**: Task roadmap and priorities
- **CLAUDE.md**: Quick reference for AI assistance
- **docs/ARCHITECTURE.md**: Detailed architecture overview

### Community
- Open an issue for questions
- Tag issues appropriately (bug, enhancement, question)
- Be respectful and constructive

## License

By contributing, you agree that your contributions will be licensed under the GNU GPL v3, the same license as the project.

All new files must include the license header:
```cpp
/*
 * FlipBooQ - Automatic white border removal tool
 * Copyright (C) 2022 Conrad Hübler <Conrad.Huebler@gmx.net>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */
```

## Copyright Attribution

### Third-Party Code
When integrating code from other sources:
1. Check license compatibility (must be GPL-compatible)
2. Preserve original copyright headers
3. Add attribution comment at top of file
4. Update ATTRIBUTION.md (if exists)

Example:
```cpp
/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
** ...
****************************************************************************/
```

---

Thank you for contributing to FlipBooQ! 🎉
