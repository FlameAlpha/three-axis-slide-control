/****************************************************************************
**
** Copyright (C) 2012 Denis Shienkov <denis.shienkov@gmail.com>
** Copyright (C) 2012 Laszlo Papp <lpapp@kde.org>
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtSerialPort module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore/QtGlobal>
#include <QtCore/QObject>
#include <QtCore/QDebug>
#include <Qt3DCore/qentity.h>
#include <Qt3DCore/qtransform.h>

#include <Qt3DExtras/QTorusMesh>
#include <Qt3DExtras/QConeMesh>
#include <Qt3DExtras/QCylinderMesh>
#include <Qt3DExtras/QCuboidMesh>
#include <Qt3DExtras/QPlaneMesh>
#include <Qt3DExtras/QSphereMesh>
#include <Qt3DExtras/QPhongMaterial>
#include <QMainWindow>

#include <QtSerialPort/QSerialPort>

#include <QtDataVisualization/qscatterdataproxy.h>
#include <QtDataVisualization/qvalue3daxis.h>
#include <QtDataVisualization/q3dscene.h>
#include <QtDataVisualization/q3dcamera.h>
#include <QtDataVisualization/qscatter3dseries.h>
#include <QtDataVisualization/q3dtheme.h>
#include <QtCore/qmath.h>
#include <QtWidgets/QComboBox>
#include <QtDataVisualization/q3dscatter.h>
#include <QtDataVisualization/qabstract3dseries.h>
#include <QtGui/QFont>

#include <QtCore/QObject>

#include <Qt3DCore/qentity.h>
#include <Qt3DCore/qtransform.h>

#include <Qt3DExtras/QTorusMesh>
#include <Qt3DExtras/QConeMesh>
#include <Qt3DExtras/QCylinderMesh>
#include <Qt3DExtras/QCuboidMesh>
#include <Qt3DExtras/QPlaneMesh>
#include <Qt3DExtras/QSphereMesh>
#include <Qt3DExtras/QPhongMaterial>

#include <QGuiApplication>

#include <Qt3DRender/qcamera.h>
#include <Qt3DCore/qentity.h>
#include <Qt3DRender/qcameralens.h>

#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QCommandLinkButton>
#include <QtGui/QScreen>

#include <Qt3DInput/QInputAspect>

#include <Qt3DExtras/qtorusmesh.h>
#include <Qt3DRender/qmesh.h>
#include <Qt3DRender/qtechnique.h>
#include <Qt3DRender/qmaterial.h>
#include <Qt3DRender/qeffect.h>
#include <Qt3DRender/qtexture.h>
#include <Qt3DRender/qrenderpass.h>
#include <Qt3DRender/qsceneloader.h>
#include <Qt3DRender/qpointlight.h>

#include <Qt3DCore/qtransform.h>
#include <Qt3DCore/qaspectengine.h>

#include <Qt3DRender/qrenderaspect.h>
#include <Qt3DExtras/qforwardrenderer.h>

#include <Qt3DExtras/qt3dwindow.h>
#include <Qt3DExtras/qfirstpersoncameracontroller.h>

#include "motorcontrol.h"

using namespace QtDataVisualization;

QT_BEGIN_NAMESPACE

class QLabel;

namespace Ui {
class MainWindow;
}

QT_END_NAMESPACE

class Console;
class SettingsDialog;
class scattershow;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void openSerialPort();
    void closeSerialPort();
    void about();
    void writeData(const QByteArray &data);
    void readData();

    void handleError(QSerialPort::SerialPortError error);
    void scatterDataChange(int x,int y,int z);
    void scatterChangeData();

    void motorDataSend(int Motornumber,bool Ward,bool State);

private:
    void initActionsConnections();

signals:
    void datachange(int x,int y,int z);

private:
    void showStatusMessage(const QString &message);

    Ui::MainWindow *ui;
    QLabel *status;
    Console *console;
    SettingsDialog *settings;
    QSerialPort *serial;
    Q3DScatter *scatter;
    QScatter3DSeries *series;
    QWidget *container;
    QScatterDataArray data;
    MotorControl *motorcontrol;
    QString string_circle;

    double X;
    double Y;
    double Z;

    QWidget *widget;
    Qt3DRender::QCamera *cameraEntity;
    float ScaleRange;
    Qt3DCore::QEntity *m_rootEntity;
    Qt3DExtras::QTorusMesh *m_torus;
    Qt3DCore::QEntity *m_coneEntity;
    Qt3DCore::QEntity *m_cylinderEntity;
    Qt3DCore::QEntity *m_cylinderEntity_2;
    Qt3DCore::QEntity *m_cylinderEntity_1;
    Qt3DCore::QEntity *m_cylinderEntity_0_2;
    Qt3DCore::QEntity *m_cylinderEntity_2_2;
    Qt3DCore::QEntity *m_cylinderEntity_1_2;
    Qt3DCore::QEntity *m_cylinderEntity_0_3;
    Qt3DCore::QEntity *m_cylinderEntity_2_3;
    Qt3DCore::QEntity *m_cylinderEntity_1_3;
    Qt3DCore::QEntity *m_torusEntity;
    Qt3DCore::QEntity *m_cuboidEntity;
    Qt3DCore::QEntity *m_cuboidEntity_1;
    Qt3DCore::QEntity *m_cuboidEntity_2;
    Qt3DCore::QEntity *m_cuboidEntity_b;
    Qt3DCore::QEntity *m_cuboidEntity_0_2;
    Qt3DCore::QEntity *m_cuboidEntity_1_2;
    Qt3DCore::QEntity *m_cuboidEntity_b_2;
    Qt3DCore::QEntity *m_cuboidEntity_Move;
    Qt3DCore::QEntity *m_cuboidEntity_0_3;
    Qt3DCore::QEntity *m_cuboidEntity_1_3;
    Qt3DCore::QEntity *m_cuboidEntity_b_3;
    Qt3DCore::QEntity *m_cuboidEntity_Move_3;
    Qt3DCore::QEntity *m_planeEntity;
    Qt3DCore::QEntity *m_sphereEntity;

    Qt3DCore::QTransform *cylinderTransform_2;
    Qt3DCore::QTransform *cylinderTransform2_2;
    Qt3DCore::QTransform *cylinderTransform3_2;
    Qt3DCore::QTransform *cylinderTransform2_3;
    Qt3DCore::QTransform *cylinderTransform3_3;
    Qt3DCore::QTransform *cylinderTransform_3;
    Qt3DCore::QTransform *cuboidTransform_Move;
    Qt3DCore::QTransform *cuboidTransform_2;
    Qt3DCore::QTransform *cuboidTransform_Move_2;
    Qt3DCore::QTransform *cuboidTransform_Move_2_2;
    Qt3DCore::QTransform *cuboidTransform_3;
    Qt3DCore::QTransform *cuboidTransform_Move_3;
    Qt3DCore::QTransform *cuboidTransform_Move_2_3;
    Qt3DCore::QTransform *cuboidTransform_Move_3_3;

    QVBoxLayout *vLayout;
    QHBoxLayout *hLayout;

    QLabel *label_TR_SW_1;
    QLabel *label_TR_SW_2;
    QLabel *label_TR_SW_3;
    QLabel *label_TR_SW_4;
    QLabel *label_TR_SW_5;
    QLabel *label_TR_SW_6;
    QLabel *label_TR_SW_7;
    QLabel *label_TR_SW_8;
    QLabel *label_TR_SW_9;

};

#endif // MAINWINDOW_H
