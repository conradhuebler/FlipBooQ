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
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "ui/tools/flowlayout.h"

#include <QtCore/QFile>

#include <QtGui/QPixmap>

#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QMessageBox>

#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGraphicsPixmapItem>
#include <QtWidgets/QGraphicsScene>

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setUi();
    resize(1280,960);
}

MainWindow::~MainWindow()
{
}

void MainWindow::setUi()
{
    m_centralWidget = new QWidget;

    m_load = new QPushButton(tr("Load Image Files"));
    connect(m_load, &QPushButton::clicked, this, &MainWindow::load);

    m_get = new QPushButton(tr("Analyse Images"));
    connect(m_get, &QPushButton::clicked, this, &MainWindow::get);

    m_save = new QPushButton(tr("Save Images"));
    connect(m_save, &QPushButton::clicked, this, &MainWindow::save);

    m_clear = new QPushButton(tr("Clear Images"));
    connect(m_clear, &QPushButton::clicked, this, &MainWindow::clear);

    m_quit = new QPushButton(tr("Quit"));
    connect(m_quit, &QPushButton::clicked, qApp, &QApplication::quit);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(m_load);
    layout->addWidget(m_get);
    layout->addWidget(m_save);
    layout->addWidget(m_clear);
    layout->addWidget(m_quit);

    m_flowLayout = new FlowLayout;

    m_zoom = new QSlider(Qt::Horizontal);
    m_zoom->setMinimum(0);
    m_zoom->setMaximum(100);
    m_zoom->setTickInterval(1);
    m_zoom->setValue(10);

    QWidget *layoutWidget = new QWidget;
    layoutWidget->setLayout(m_flowLayout);

    QScrollArea *scrollArea = new QScrollArea;
    scrollArea->setWidget(layoutWidget);
    scrollArea->setWidgetResizable(true);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(layout);
    //mainLayout->addWidget(m_zoom);
    mainLayout->addWidget(scrollArea);

    m_centralWidget->setLayout(mainLayout);

    setCentralWidget(m_centralWidget);
    EnableButtons(false);
}

void MainWindow::EnableButtons(bool enable)
{
    m_get->setEnabled(enable);
    m_save->setEnabled(enable);
    m_clear->setEnabled(enable);
}

bool MainWindow::addFile(const QString &file)
{
    // Validate file existence
    if (!QFile::exists(file)) {
        QMessageBox::warning(this, tr("Error"),
                           tr("File not found: %1").arg(file));
        return false;
    }

    // Load pixmap and validate
    QPixmap pix(file);
    if (pix.isNull()) {
        QMessageBox::warning(this, tr("Error"),
                           tr("Cannot load image: %1\nFile may be corrupted or format not supported.").arg(file));
        return false;
    }

    // Check image size limits
    const int maxDimension = 10000;
    if (pix.width() > maxDimension || pix.height() > maxDimension) {
        auto reply = QMessageBox::question(this, tr("Large Image"),
                                          tr("Image is very large (%1x%2).\nThis may consume significant memory.\n\nContinue?")
                                          .arg(pix.width()).arg(pix.height()),
                                          QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::No) {
            return false;
        }
    }

    // Add to internal storage
    m_file_names << file;
    m_images << pix;

    // Create scene and view
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->addPixmap(pix);
    m_image_scene << scene;

    QGraphicsView *view = new QGraphicsView(scene);
    m_flowLayout->addWidget(view);
    view->scale(0.5, 0.5);
    m_image_view << view;

    EnableButtons(true);
   /*
    connect(m_zoom, &QSlider::valueChanged, view, [view](int value){
        view->resize(30*value, 30*value);
    });
    */

    return true;
}

void MainWindow::load()
{
    QStringList files = QFileDialog::getOpenFileNames(
                            this,
                            "Select one or more files to open",
                            QDir::homePath(),
                            "Images (*.png *.xpm *.jpg)");
    for(const QString &file : files)
        addFile(file);
}

void MainWindow::get()
{
    QPen pen;
    pen.setColor(Qt::black);
    pen.setWidth(1);
    m_rect = getRect(m_images);
    for(QPointer<QGraphicsScene> scene : m_image_scene)
        scene->addRect(m_rect, pen);
}


void MainWindow::save()
{
    if (m_images.isEmpty()) {
        QMessageBox::warning(this, tr("Error"),
                           tr("No images to save."));
        return;
    }

    if (m_rect.isEmpty()) {
        QMessageBox::warning(this, tr("Error"),
                           tr("No crop area defined. Please analyze images first."));
        return;
    }

    int successCount = 0;
    int failCount = 0;
    QStringList failedFiles;

    for (int i = 0; i < m_images.size(); ++i) {
        QFileInfo f(m_file_names[i]);
        QString outputPath = f.path() + QDir::separator() + "export_" + f.fileName();

        // Check if directory is writable
        QFileInfo dirInfo(f.path());
        if (!dirInfo.isWritable()) {
            failedFiles << f.fileName() + tr(" (directory not writable)");
            failCount++;
            continue;
        }

        // Copy crop area
        QPixmap tmp = m_images[i].copy(m_rect);
        if (tmp.isNull()) {
            failedFiles << f.fileName() + tr(" (invalid crop area)");
            failCount++;
            continue;
        }

        // Open file for writing
        QFile writeFile(outputPath);
        if (!writeFile.open(QIODevice::WriteOnly)) {
            failedFiles << f.fileName() + tr(" (cannot create file)");
            failCount++;
            continue;
        }

        // Save image
        if (!tmp.save(&writeFile)) {
            failedFiles << f.fileName() + tr(" (save failed)");
            failCount++;
            writeFile.close();
            continue;
        }

        writeFile.close();
        successCount++;
    }

    // Show results to user
    QString message;
    if (failCount == 0) {
        message = tr("Successfully exported %1 image(s).").arg(successCount);
        QMessageBox::information(this, tr("Export Complete"), message);
    } else {
        message = tr("Exported %1 image(s) successfully.\n%2 image(s) failed:\n\n%3")
                      .arg(successCount)
                      .arg(failCount)
                      .arg(failedFiles.join("\n"));
        QMessageBox::warning(this, tr("Export Completed with Errors"), message);
    }
}

void MainWindow::clear()
{
    // Clear image data
    m_images.clear();
    m_file_names.clear();
    m_rect = QRect();

    // Delete scenes first
    qDeleteAll(m_image_scene);
    m_image_scene.clear();

    // Delete views
    qDeleteAll(m_image_view);
    m_image_view.clear();

    // Clear layout items (views are already deleted, just delete layout items)
    QLayoutItem *item;
    while ((item = m_flowLayout->takeAt(0))) {
        // Widget is already deleted via qDeleteAll above
        delete item;
    }

    EnableButtons(false);
}

QRect MainWindow::getRect(const QVector<QPixmap> &pixmaps)
{
    QVector<QRect> rects;
    for(const QPixmap &pix : pixmaps)
    {
        QImage image = pix.toImage();
        rects << QRegion(QBitmap::fromImage(image.createMaskFromColor(image.pixel(0,0)))).boundingRect();
    }
    QRect final;
    for(const QRect &rect : rects)
        final = final.united(rect);
    return final;
}
