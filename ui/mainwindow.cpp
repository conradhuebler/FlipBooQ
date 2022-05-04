/*
 * <one line to give the program's name and a brief idea of what it does.>
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

void MainWindow::addFile(const QString &file)
{
    QPixmap pix(file);
    m_file_names << file;
    m_images << pix;

    QGraphicsScene *scene = new QGraphicsScene;
    scene->addPixmap(pix);
    m_image_scene << scene;

    QGraphicsView *view = new QGraphicsView(scene);
    m_flowLayout->addWidget(view);
    view->scale(0.5,0.5);
    m_image_view << view;
    EnableButtons(true);
   /*
    connect(m_zoom, &QSlider::valueChanged, view, [view](int value){
        view->resize(30*value, 30*value);
    });
    */
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
    for(int i = 0; i < m_images.size(); ++i)
    {
        QFileInfo f(m_file_names[i]);
        qDebug() << i << "export_" + f.path() +QDir::separator() +"export_" + f.fileName();
        QPixmap tmp = m_images[i].copy(m_rect);
        QFile writeFile(f.path() +QDir::separator() +"export_" + f.fileName());
        writeFile.open(QIODevice::WriteOnly);
        qDebug() << tmp.save(&writeFile);
    }
}

void MainWindow::clear()
{
    m_images.clear();
    m_file_names.clear();
    qDeleteAll(m_image_view);
    m_image_view.clear();
    QLayoutItem *item;
    while ((item = m_flowLayout->takeAt(0)))
        delete item;
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
