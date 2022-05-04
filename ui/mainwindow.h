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

#pragma once

#include <QtCore/QPointer>

#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QGraphicsScene>
#include <QtWidgets/QSlider>
#include <QtWidgets/QPushButton>

#include "ui/tools/flowlayout.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void addFile(const QString &file);
    void load();
    void get();
    void save();
    void clear();

    void setUi();

private:
    void EnableButtons(bool enable);

    QRect getRect(const QVector<QPixmap> &pixmaps);
    QPushButton *m_load, *m_get, *m_save, *m_clear, *m_quit;

    QWidget *m_centralWidget;
    QVector<QPointer<QGraphicsView> > m_image_view;
    QVector<QPointer<QGraphicsScene> > m_image_scene;

    QVector<QPixmap> m_images;
    QStringList m_file_names;
    QSlider *m_zoom;
    FlowLayout *m_flowLayout;
    QRect m_rect;
};
