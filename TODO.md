# FlipBooQ - TODO & Improvement Roadmap

## Overview
This document outlines planned improvements and modernization efforts for FlipBooQ, a Qt application for automatic white border removal from multiple images.

---

## Phase 1: Grundlegende Verbesserungen (HIGH PRIORITY)

### 1.1 Fehlerbehandlung und Robustheit ✅ 2025-01-04
- [x] Validierung beim Laden von Bildern
  - Dateiexistenz prüfen
  - Bildformat validieren
  - Größenlimits implementieren (>10000px warnen)
- [x] Fehlerbehandlung beim Speichern
  - Schreibrechte prüfen
  - Speichern validieren
  - Fehlgeschlagene Exports loggen
- [x] QMessageBox für Benutzerfeedback bei Fehlern
- [x] Memory-Management verbessern in `clear()`
  - Szenen und Views ordnungsgemäß löschen
  - Layout-Items mit Widgets löschen

### 1.2 UI/UX Basisfunktionen ✅ 2025-01-04
- [x] **Drag & Drop Support** implementiert
  - dragEnterEvent und dropEvent hinzugefügt
  - Filtert Bilddateien automatisch
  - Zeigt Zusammenfassung von erfolgreich/fehlgeschlagen
- [x] **Zoom-Slider aktiviert**
  - Dynamische Skalierung 0.1x - 2.0x
  - Alle Views synchron zoomen
  - Wird auf neue Bilder angewendet
- [x] **Keyboard Shortcuts** hinzugefügt
  - Ctrl+O: Open files
  - Ctrl+S: Save
  - Ctrl+W: Clear
  - Ctrl+Q: Quit
  - Ctrl+A: Analyze

### 1.3 Export-Verbesserungen [ADD]
- [ ] **Export-Dialog** mit Optionen erstellen
  - Ausgabeverzeichnis wählen
  - Dateinamens-Template (z.B. "cropped_{name}")
  - Format wählen (PNG, JPG, WebP)
  - Qualitätseinstellungen für JPG
- [ ] **Progress-Dialog** für Batch-Export
  - Fortschrittsbalken
  - Anzahl verarbeiteter Bilder
  - Abbrechen-Button
- [ ] Export-Präfix konfigurierbar machen (nicht hardcoded "export_")

### 1.4 Einstellungen persistieren [ADD]
- [ ] **QSettings** Integration
  - Letztes Verzeichnis merken
  - Zoom-Level speichern
  - Erkennungsmodus & Toleranz
  - Fenstergröße und Position
- [ ] Settings beim Start laden
- [ ] Settings beim Beenden/Ändern speichern

---

## Phase 2: Erweiterte Features (MEDIUM PRIORITY)

### 2.1 Verbesserter Erkennungsalgorithmus [ADD]
- [ ] **CropSettings Struktur** erstellen
  ```cpp
  struct CropSettings {
      enum class DetectionMode {
          CornerPixel,    // Aktuell: (0,0)
          AutoDetect,     // Alle 4 Ecken analysieren
          ManualColor,    // Benutzer wählt Farbe
          Threshold       // Farbabweichungs-Schwellwert
      };
      DetectionMode mode;
      QColor manualColor;
      int tolerance;
      bool perImageCrop;
  };
  ```
- [ ] **Intelligente Hintergrundfarb-Erkennung**
  - Alle 4 Ecken analysieren
  - Häufigste Farbe ermitteln
  - Oder Mittelwert der Eckpixel
- [ ] **Toleranz-basierte Erkennung**
  - RGB-Abweichung berücksichtigen
  - Konfigurierbare Schwellwerte
- [ ] **Individuelles vs. vereinigtes Rechteck**
  - Option für separate Bounding-Boxes pro Bild
  - Oder gemeinsames Rechteck (aktuelles Verhalten)

### 2.2 Settings-Panel [ADD]
- [ ] **SettingsPanel Widget** erstellen
  - QComboBox für Erkennungsmodus
  - QSpinBox für Toleranz
  - QCheckBox für individuelles Beschneiden
  - QPushButton für Color-Picker
- [ ] Settings-Panel in MainWindow integrieren
- [ ] Live-Preview bei Settings-Änderung

### 2.3 Erweiterte Ansichten [ADD]
- [ ] **Vorher/Nachher-Ansicht**
  - Split-View mit QSplitter
  - Original vs. beschnittenes Bild
  - Toggle zwischen Ansichten
- [ ] **Thumbnail-Grid** zusätzlich zum Flow-Layout
- [ ] **Bounding-Box Visualisierung** verbessern
  - Verschiedene Farben für individuell/vereinigt
  - Dicke und Stil konfigurierbar

### 2.4 Bildformat-Erweiterungen [ADD]
- [ ] Weitere Formate unterstützen
  - TIFF, WebP, BMP, GIF
  - PDF (einzelne Seiten als Bilder)
- [ ] Format-spezifische Import-Optionen
- [ ] Metadata-Erhaltung beim Export

---

## Phase 3: Fortgeschrittene Features (LOW PRIORITY)

### 3.1 Qt6 Vollständige Migration [ADD]
- [ ] **CMake modernisieren**
  - Minimal Version auf 3.16+ erhöhen
  - `qt_standard_project_setup()` nutzen
  - Qt6-spezifische Features aktivieren
- [ ] **C++20 Standard** nutzen
  - Ranges, Concepts, etc.
  - std::format statt QString::arg
- [ ] **Qt6 Module** integrieren
  - QtConcurrent für Threading
  - QtCore6Compat prüfen (falls nötig)
- [ ] **Container-Modernisierung**
  - QVector → QList (Qt6 bevorzugt)
  - std::vector für Non-Qt-Daten
  - Smart Pointers statt QPointer wo sinnvoll

### 3.2 Parallele Verarbeitung [ADD]
- [ ] **QtConcurrent** für Batch-Processing
  ```cpp
  QFuture<void> future = QtConcurrent::map(m_images, processImage);
  ```
- [ ] Thread-Pool für große Bildmengen
- [ ] Async-Export mit Progress-Updates
- [ ] Worker-Threads für Analyse-Phase

### 3.3 CLI-Modus [ADD]
- [ ] **QCommandLineParser** implementieren
  - `-b, --batch`: Headless-Modus
  - `-i, --input`: Eingabedateien/Verzeichnis
  - `-o, --output`: Ausgabeverzeichnis
  - `-t, --tolerance`: Erkennungs-Toleranz
  - `-m, --mode`: Erkennungsmodus
- [ ] Headless-Processing ohne GUI
- [ ] JSON-Konfigurationsdatei-Support
- [ ] Exit-Codes für Scripting

### 3.4 Testing-Infrastruktur [ADD]
- [ ] **Qt Test Framework** einrichten
  - Unit Tests für `getRect()`
  - Tests für Farbenerkennung
  - Tests für vereinigtes Rechteck
- [ ] **CMake Test-Integration**
  ```cmake
  enable_testing()
  add_subdirectory(tests)
  ```
- [ ] Test-Coverage messen
- [ ] Beispielbilder für Tests (fixtures)

---

## Phase 4: Polishing & Distribution (FUTURE)

### 4.1 Dokumentation [ADD]
- [ ] **README.md** erweitern
  - Features-Liste
  - Screenshots
  - Installation & Build-Anleitung
  - Usage-Beispiele (GUI & CLI)
- [ ] **Doxygen-Kommentare** hinzufügen
  - Alle public-Methoden dokumentieren
  - Parameter und Return-Values beschreiben
  - Code-Beispiele in Kommentaren
- [ ] **User-Manual** erstellen (separate .md Datei)
- [ ] **Changelog** führen (CHANGELOG.md)

### 4.2 Professionalisierung [ADD]
- [ ] **Logging-System** implementieren
  - QLoggingCategory für Module
  - Debug/Info/Warning/Error Levels
  - Log-Datei optional
- [ ] **Crash-Reporting** (optional)
- [ ] **Analytics** (opt-in, lokal)
- [ ] **Auto-Update-Mechanismus** (optional)

### 4.3 CI/CD & Build-System [ADD]
- [ ] **GitHub Actions** Workflow
  - Multi-Platform Builds (Linux, Windows, macOS)
  - Automated Testing
  - Release-Artefakte erstellen
- [ ] **CPack** für Installer
  - DEB/RPM für Linux
  - DMG für macOS
  - NSIS für Windows
- [ ] **AppImage/Flatpak/Snap** für Linux
- [ ] Codesigning für Releases

### 4.4 Weitere Features [FUTURE]
- [ ] **Lokalisierung (i18n)**
  - Deutsche Übersetzung
  - Englische Übersetzung
  - TR-System für alle Strings
- [ ] **Dark Mode Support**
  - Palette-basiertes Theming
  - System-Theme respektieren
- [ ] **Plugins/Extensions**
  - Plugin-API für Custom-Algorithmen
  - Filter-Chain-System
- [ ] **Undo/Redo** für Operationen
- [ ] **Batch-Profiles** speichern & laden

---

## Refactoring-Bedarf

### Code-Qualität [WIP]
- [ ] Header-Kommentare vervollständigen
  - Aktuell: "one line to give the program's name..."
  - Aussagekräftige Beschreibungen
- [ ] `qDebug()` Statements entfernen oder mit Logging ersetzen
- [ ] Magic Numbers in Konstanten umwandeln
  - `0.5` → `DEFAULT_PREVIEW_SCALE`
  - `30` → `ZOOM_MULTIPLIER`
- [ ] Längere Methoden aufteilen (`save()`, `getRect()`)

### Architektur [FUTURE]
- [ ] **MVC-Pattern** stärker separieren
  - Model: ImageCollection
  - View: MainWindow + Widgets
  - Controller: Logic-Klassen
- [ ] **Service-Klassen** extrahieren
  - CropService für Algorithmus
  - ExportService für Save-Logic
  - SettingsService für Config
- [ ] **Signals/Slots** erweitern
  - imageAdded, imageRemoved
  - cropRectChanged
  - exportProgress

---

## Known Issues & Bugs

### Current Issues
- [ ] Zoom-Slider ist deaktiviert (mainwindow.cpp:124-128)
- [ ] Keine Fehlerbehandlung bei `QPixmap::save()`
- [ ] Memory-Leak möglich bei `clear()` (Layout-Items)
- [ ] Pixel (0,0) ist möglicherweise kein guter Hintergrund-Detektor
- [ ] Große Bilder können Speicherprobleme verursachen

### Testing Needed
- [ ] Multi-threaded Zugriff auf m_images
- [ ] Verhalten bei sehr vielen Bildern (>1000)
- [ ] Nicht-quadratische Bilder mit verschiedenen Seitenverhältnissen
- [ ] Bilder mit transparentem Hintergrund

---

## Development Notes

### Build-System
- CMake 3.5+ erforderlich
- Qt5 oder Qt6 unterstützt
- C++17 Standard (später auf C++20)
- GNU-Compiler mit strengen Warnings

### Abhängigkeiten
- Qt::Widgets (erforderlich)
- Qt::Concurrent (geplant für Phase 3)
- Qt::Test (geplant für Phase 3)
- Qt::Pdf (optional für PDF-Support)

### Plattformen
- Linux: Primäre Entwicklungsplattform
- Windows: Unterstützt
- macOS: Unterstützt
- Android: CMake-Support vorhanden, nicht getestet

---

## Changelog

### [Unreleased]
- TODO.md Dokumentation erstellt

### [0.1] - 2022
- Initiale Version von Conrad Hübler
- Grundfunktionalität: Load, Analyze, Save, Clear
- FlowLayout Integration
- Qt5/Qt6 Support

---

## Contributing

### Workflow
1. Aufgabe aus TODO auswählen und auf [WIP] setzen
2. Feature-Branch erstellen (`feature/description`)
3. Implementieren + Tests schreiben
4. Status auf [TESTED] setzen
5. Code-Review durchführen
6. Status auf [APPROVED] setzen, mergen
7. Task als ✅ markieren, mit Datum

### Commit-Konventionen
```
type(scope): brief description

- Detailed change 1
- Detailed change 2

type: feat, fix, refactor, docs, test, chore, style
scope: ui, core, export, settings, build, etc.
```

### Testing
Jedes neue Feature sollte begleitet werden von:
- Unit Tests (wo möglich)
- Manuelle Tests auf mind. 2 Plattformen
- Update der Dokumentation

---

**Letzte Aktualisierung**: 2025-01-04
**Version**: 0.1 → 0.2 (in Entwicklung)
**Maintainer**: Conrad Hübler
