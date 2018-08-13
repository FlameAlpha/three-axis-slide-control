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

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "console.h"
#include "settingsdialog.h"

#include <QMessageBox>
#include <QLabel>
#include <QtSerialPort/QSerialPort>

//! [0]
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
//! [0]
    ui->setupUi(this);
    ScaleRange=1.0f;
    console = new Console;
    console->setEnabled(false);
    setCentralWidget(console);
//! [1]
    serial = new QSerialPort(this);
//! [1]
    settings = new SettingsDialog;

    ui->actionConnect->setEnabled(true);
    ui->actionDisconnect->setEnabled(false);
    ui->actionQuit->setEnabled(true);
    ui->actionConfigure->setEnabled(true);
    ui->actionOpenDrawer->setEnabled(true);
    motorcontrol=new MotorControl;
    status = new QLabel;
    scatter=new Q3DScatter;
    scatter->setFlags(scatter->flags() ^ Qt::FramelessWindowHint);
    scatter->axisX()->setRange(-3000.0,3000.0);
    scatter->axisY()->setRange(-3000.0,3000.0);
    scatter->axisZ()->setRange(-3000.0,3000.0);
    scatter->axisX()->setSegmentCount(20);
    scatter->axisY()->setSegmentCount(20);
    scatter->axisY()->setSegmentCount(20);

    scatter->axisX()->setSubSegmentCount(2);
    scatter->axisY()->setSubSegmentCount(2);
    scatter->axisY()->setSubSegmentCount(2);

    series = new QScatter3DSeries;

    series->dataProxy()->addItems(data);
    scatter->addSeries(series);
    container = QWidget::createWindowContainer(scatter);
    container->setWindowTitle("X-Y坐标立体显示");
    container->resize(600,600);
    scatter->resize(600, 600);

    motorcontrol->setWindowTitle("Postion Displayer");

    //3D 实物显示

    X=0; Y=0; Z=3;

    Qt3DExtras::Qt3DWindow *view = new Qt3DExtras::Qt3DWindow();
    view->defaultFrameGraph()->setClearColor(QColor(QRgb(0x4d4d4f)));
    QWidget *container = QWidget::createWindowContainer(view);
    QSize screenSize = view->screen()->size();
    container->setMinimumSize(QSize(200, 100));
    container->setMaximumSize(screenSize);

    widget = new QWidget();
    hLayout = new QHBoxLayout(widget);
    vLayout = new QVBoxLayout();
    vLayout->setAlignment(Qt::AlignTop);
    hLayout->addWidget(container, 1);
    hLayout->addLayout(vLayout);

    widget->setWindowTitle(QStringLiteral("3D 模型实时显示"));

    Qt3DInput::QInputAspect *input = new Qt3DInput::QInputAspect;
    view->registerAspect(input);

    // Root entity
    Qt3DCore::QEntity *rootEntity = new Qt3DCore::QEntity();

    // Camera
    cameraEntity = view->camera();

    cameraEntity->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 0.1f, 1000.0f);
    cameraEntity->setPosition(QVector3D(15.0f, 15.0f, 15.0f));
    cameraEntity->setUpVector(QVector3D(0,0,1));
    cameraEntity->setViewCenter(QVector3D(0, 0, 0));

    Qt3DCore::QEntity *lightEntity = new Qt3DCore::QEntity(rootEntity);
    Qt3DRender::QPointLight *light = new Qt3DRender::QPointLight(lightEntity);
    light->setColor("white");
    light->setIntensity(1);
    lightEntity->addComponent(light);
    Qt3DCore::QTransform *lightTransform = new Qt3DCore::QTransform(lightEntity);
    lightTransform->setTranslation(cameraEntity->position());
    lightEntity->addComponent(lightTransform);

    // For camera controls
    Qt3DExtras::QFirstPersonCameraController *camController = new Qt3DExtras::QFirstPersonCameraController(rootEntity);
    camController->setCamera(cameraEntity);

    // Cylinder shape data 圆柱状
    //First Motor
    Qt3DExtras::QCylinderMesh *cylinder = new Qt3DExtras::QCylinderMesh();
    cylinder->setRadius(0.1);
    cylinder->setLength(10);
    cylinder->setRings(100);
    cylinder->setSlices(20);

    Qt3DExtras::QCylinderMesh *cylinder_small = new Qt3DExtras::QCylinderMesh();
    cylinder_small->setRadius(0.07);
    cylinder_small->setLength(10);
    cylinder_small->setRings(100);
    cylinder_small->setSlices(20);

    //Second Motor
    Qt3DExtras::QCylinderMesh *cylinder_2 = new Qt3DExtras::QCylinderMesh();
    cylinder_2->setRadius(0.1);
    cylinder_2->setLength(7);
    cylinder_2->setRings(100);
    cylinder_2->setSlices(20);

    Qt3DExtras::QCylinderMesh *cylinder_small_2= new Qt3DExtras::QCylinderMesh();
    cylinder_small_2->setRadius(0.07);
    cylinder_small_2->setLength(7);
    cylinder_small_2->setRings(100);
    cylinder_small_2->setSlices(20);

    //Third Motor
    Qt3DExtras::QCylinderMesh *cylinder_3 = new Qt3DExtras::QCylinderMesh();
    cylinder_3->setRadius(0.07);
    cylinder_3->setLength(5);
    cylinder_3->setRings(100);
    cylinder_3->setSlices(20);

    Qt3DExtras::QCylinderMesh *cylinder_small_3= new Qt3DExtras::QCylinderMesh();
    cylinder_small_3->setRadius(0.035);
    cylinder_small_3->setLength(5);
    cylinder_small_3->setRings(100);
    cylinder_small_3->setSlices(20);

    // Cylinder Material
    Qt3DExtras::QPhongMaterial *cylinderMaterial = new Qt3DExtras::QPhongMaterial();
    cylinderMaterial->setDiffuse(QColor(QRgb(0xDBDBDB)));

    // CylinderMesh Transform
    //First Motor
    Qt3DCore::QTransform *cylinderTransform = new Qt3DCore::QTransform();
    cylinderTransform->setScale(ScaleRange);
    cylinderTransform->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 0.0f, 1.0f), 90.0f));
    cylinderTransform->setTranslation(QVector3D(0.0f, -0.5f, 0));

    Qt3DCore::QTransform *cylinderTransform2 = new Qt3DCore::QTransform();
    cylinderTransform2->setScale(ScaleRange);
    cylinderTransform2->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 0.0f, 1.0f), 90.0f));
    cylinderTransform2->setTranslation(QVector3D(0.0f, 0.5f, 0.0));

    Qt3DCore::QTransform *cylinderTransform3 = new Qt3DCore::QTransform();
    cylinderTransform3->setScale(ScaleRange);
    cylinderTransform3->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 0.0f, 1.0f), 90.0f));
    cylinderTransform3->setTranslation(QVector3D(0.0f, 0.0f, 0.0));
    //Second Motor
    cylinderTransform_2 = new Qt3DCore::QTransform();
    cylinderTransform_2->setScale(ScaleRange);
    cylinderTransform_2->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(1.0f, 0.0f, 0.0f), 90.0f));
    cylinderTransform_2->setTranslation(QVector3D(X, -0.4f, 0.65f+3.5f));

    cylinderTransform2_2 = new Qt3DCore::QTransform();
    cylinderTransform2_2->setScale(ScaleRange);
    cylinderTransform2_2->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(1.0f, 0.0f, 0.0f), 90.0f));
    cylinderTransform2_2->setTranslation(QVector3D(X, 0.4f, 0.65f+3.5f));

    cylinderTransform3_2 = new Qt3DCore::QTransform();
    cylinderTransform3_2->setScale(ScaleRange);
    cylinderTransform3_2->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(1.0f, 0.0f, 0.0f), 90.0f));
    cylinderTransform3_2->setTranslation(QVector3D(X, 0.0f, 0.65f+3.5f));
    //Third Motor
    cylinderTransform_3 = new Qt3DCore::QTransform();
    cylinderTransform_3->setScale(ScaleRange);
    cylinderTransform_3->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 0.0f, 0.0f), 90.0f));
    cylinderTransform_3->setTranslation(QVector3D(X+0.6, 0.0f, -0.3+0.55+Z+0.5));

    cylinderTransform2_3 = new Qt3DCore::QTransform();
    cylinderTransform2_3->setScale(ScaleRange);
    cylinderTransform2_3->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 0.0f, 0.0f), 90.0f));
    cylinderTransform2_3->setTranslation(QVector3D(X+0.6, 0.0f, 0.5f+0.55+Z));

    cylinderTransform3_3 = new Qt3DCore::QTransform();
    cylinderTransform3_3->setScale(ScaleRange);
    cylinderTransform3_3->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 0.0f, 0.0f), 90.0f));
    cylinderTransform3_3->setTranslation(QVector3D(X+0.6, 0.0f, 0.55+Z+0.5+0.3));

    // Cylinder
    //First Motor
    m_cylinderEntity = new Qt3DCore::QEntity(rootEntity);
    m_cylinderEntity->addComponent(cylinder);
    m_cylinderEntity->addComponent(cylinderMaterial);
    m_cylinderEntity->addComponent(cylinderTransform);

    m_cylinderEntity_1 = new Qt3DCore::QEntity(rootEntity);
    m_cylinderEntity_1->addComponent(cylinder);
    m_cylinderEntity_1->addComponent(cylinderMaterial);
    m_cylinderEntity_1->addComponent(cylinderTransform2);

    m_cylinderEntity_2 = new Qt3DCore::QEntity(rootEntity);
    m_cylinderEntity_2->addComponent(cylinder_small);
    m_cylinderEntity_2->addComponent(cylinderMaterial);
    m_cylinderEntity_2->addComponent(cylinderTransform3);
    //Second Motor
    m_cylinderEntity_0_2 = new Qt3DCore::QEntity(rootEntity);
    m_cylinderEntity_0_2->addComponent(cylinder_2);
    m_cylinderEntity_0_2->addComponent(cylinderMaterial);
    m_cylinderEntity_0_2->addComponent(cylinderTransform_2);

    m_cylinderEntity_1_2 = new Qt3DCore::QEntity(rootEntity);
    m_cylinderEntity_1_2->addComponent(cylinder_2);
    m_cylinderEntity_1_2->addComponent(cylinderMaterial);
    m_cylinderEntity_1_2->addComponent(cylinderTransform2_2);

    m_cylinderEntity_2_2 = new Qt3DCore::QEntity(rootEntity);
    m_cylinderEntity_2_2->addComponent(cylinder_small_2);
    m_cylinderEntity_2_2->addComponent(cylinderMaterial);
    m_cylinderEntity_2_2->addComponent(cylinderTransform3_2);
    //Third Motor
    m_cylinderEntity_0_3 = new Qt3DCore::QEntity(rootEntity);
    m_cylinderEntity_0_3->addComponent(cylinder_3);
    m_cylinderEntity_0_3->addComponent(cylinderMaterial);
    m_cylinderEntity_0_3->addComponent(cylinderTransform3_3);

    m_cylinderEntity_1_3 = new Qt3DCore::QEntity(rootEntity);
    m_cylinderEntity_1_3->addComponent(cylinder_3);
    m_cylinderEntity_1_3->addComponent(cylinderMaterial);
    m_cylinderEntity_1_3->addComponent(cylinderTransform_3);

    m_cylinderEntity_2_3 = new Qt3DCore::QEntity(rootEntity);
    m_cylinderEntity_2_3->addComponent(cylinder_small_3);
    m_cylinderEntity_2_3->addComponent(cylinderMaterial);
    m_cylinderEntity_2_3->addComponent(cylinderTransform2_3);
    // Cuboid shape data 长方体
    //First Motor
    Qt3DExtras::QCuboidMesh *cuboid = new Qt3DExtras::QCuboidMesh();
    cuboid->setXExtent(1.5);
    cuboid->setYExtent(1.5);
    cuboid->setZExtent(1.5);

    Qt3DExtras::QCuboidMesh *cuboid_mid = new Qt3DExtras::QCuboidMesh();
    cuboid_mid->setXExtent(0.5);
    cuboid_mid->setYExtent(1.5);
    cuboid_mid->setZExtent(1.5);

    Qt3DExtras::QCuboidMesh *cuboid_Move = new Qt3DExtras::QCuboidMesh();
    cuboid_Move->setXExtent(1.4);
    cuboid_Move->setYExtent(1.4);
    cuboid_Move->setZExtent(1.0);

    Qt3DExtras::QCuboidMesh *cuboid_B = new Qt3DExtras::QCuboidMesh();
    cuboid_B->setXExtent(12);
    cuboid_B->setYExtent(1.5);
    cuboid_B->setZExtent(0.3);

    //Second Motor
    Qt3DExtras::QCuboidMesh *cuboid_2 = new Qt3DExtras::QCuboidMesh();
    cuboid_2->setXExtent(1.2);
    cuboid_2->setYExtent(1.2);
    cuboid_2->setZExtent(1.0);

    Qt3DExtras::QCuboidMesh *cuboid_Move_2 = new Qt3DExtras::QCuboidMesh();
    cuboid_Move_2->setXExtent(0.4);
    cuboid_Move_2->setYExtent(1.1);
    cuboid_Move_2->setZExtent(1.1);

    Qt3DExtras::QCuboidMesh *cuboid_Move_b = new Qt3DExtras::QCuboidMesh();
    cuboid_Move_b->setXExtent(0.2);
    cuboid_Move_b->setYExtent(1.2);
    cuboid_Move_b->setZExtent(8);

    //Third Motor

    Qt3DExtras::QCuboidMesh *cuboid_3 = new Qt3DExtras::QCuboidMesh();
    cuboid_3->setXExtent(1.0);
    cuboid_3->setYExtent(0.9);
    cuboid_3->setZExtent(1.0);

    Qt3DExtras::QCuboidMesh *cuboid_small_3 = new Qt3DExtras::QCuboidMesh();
    cuboid_small_3->setXExtent(1.0);
    cuboid_small_3->setYExtent(0.3);
    cuboid_small_3->setZExtent(1.0);

    Qt3DExtras::QCuboidMesh *cuboid_Move_b_3 = new Qt3DExtras::QCuboidMesh();
    cuboid_Move_b_3->setXExtent(0.1);
    cuboid_Move_b_3->setYExtent(0.9+5+0.3);
    cuboid_Move_b_3->setZExtent(1.0);

    Qt3DExtras::QCuboidMesh *cuboid_Move_3 = new Qt3DExtras::QCuboidMesh();
    cuboid_Move_3->setXExtent(0.3);
    cuboid_Move_3->setYExtent(0.8);
    cuboid_Move_3->setZExtent(0.8);

    // CuboidMesh Transform
    //First Motor
    Qt3DCore::QTransform *cuboidTransform = new Qt3DCore::QTransform();
    cuboidTransform->setScale(ScaleRange);
    cuboidTransform->setTranslation(QVector3D(5.0f+0.25, 0.0f, 0.0f));

    Qt3DCore::QTransform *cuboidTransform2 = new Qt3DCore::QTransform();
    cuboidTransform2->setScale(ScaleRange);
    cuboidTransform2->setTranslation(QVector3D(-5.0f-0.75, 0.0f, 0.0f));

    cuboidTransform_Move = new Qt3DCore::QTransform();
    cuboidTransform_Move->setScale(ScaleRange);
    cuboidTransform_Move->setTranslation(QVector3D(X, 0.0f, 0.0f));

    Qt3DCore::QTransform *cuboidTransform_b = new Qt3DCore::QTransform();
    cuboidTransform_b->setScale(ScaleRange);
    cuboidTransform_b->setTranslation(QVector3D(-0.5f, 0.0f, -1.5/2-0.15));
    //Second Motor
    cuboidTransform_2 = new Qt3DCore::QTransform();
    cuboidTransform_2->setScale(ScaleRange);
    cuboidTransform_2->setTranslation(QVector3D(X, 0.0f, 0.5f+7+0.55));

    cuboidTransform_Move_2 = new Qt3DCore::QTransform();
    cuboidTransform_Move_2->setScale(ScaleRange);
    cuboidTransform_Move_2->setTranslation(QVector3D(X, 0.0f ,0.5f+0.55+Z));

    cuboidTransform_Move_2_2 = new Qt3DCore::QTransform();
    cuboidTransform_Move_2_2->setScale(ScaleRange);
    cuboidTransform_Move_2_2->setTranslation(QVector3D(X-0.6-0.1, 0.0f ,0.5f+4));
    //Third Motor
    cuboidTransform_3 = new Qt3DCore::QTransform();
    cuboidTransform_3->setScale(ScaleRange);
    cuboidTransform_3->setTranslation(QVector3D(X+0.2+0.5+0.1, -2.5f-0.15,0.5f+0.55+Z));

    cuboidTransform_Move_3 = new Qt3DCore::QTransform();
    cuboidTransform_Move_3->setScale(ScaleRange);
    cuboidTransform_Move_3->setTranslation(QVector3D(X+0.2+0.5+0.1, 2.5f+0.45 ,0.5f+0.55+Z));

    cuboidTransform_Move_2_3 = new Qt3DCore::QTransform();
    cuboidTransform_Move_2_3->setScale(ScaleRange);
    cuboidTransform_Move_2_3->setTranslation(QVector3D(X+0.2+0.05, 0.0f+0.3 ,0.5f+0.55+Z));

    cuboidTransform_Move_3_3 = new Qt3DCore::QTransform();
    cuboidTransform_Move_3_3->setScale(ScaleRange);
    cuboidTransform_Move_3_3->setTranslation(QVector3D(X+0.2+0.5, 2.5f-Y-0.4 ,0.5f+0.55+Z));

    //Cuboid Material
    Qt3DExtras::QPhongMaterial *cuboidMaterial = new Qt3DExtras::QPhongMaterial();
    cuboidMaterial->setAmbient(QColor(QRgb(0x0A0A0A)));
    cuboidMaterial->setSpecular(QColor(QRgb(0xFFFFFF)));
    cuboidMaterial->setDiffuse(QColor(QRgb(0x0A0A0A)));
    cuboidMaterial->setShininess(100);

    Qt3DExtras::QPhongMaterial *cuboidMaterial_b = new Qt3DExtras::QPhongMaterial();
    cuboidMaterial_b->setDiffuse(QColor(QRgb(0xDBDBDB)));
    cuboidMaterial_b->setShininess(100);
    //Cuboid
    //First Motor
    m_cuboidEntity_Move = new Qt3DCore::QEntity(rootEntity);
    m_cuboidEntity_Move->addComponent(cuboid_Move);
    m_cuboidEntity_Move->addComponent(cuboidMaterial);
    m_cuboidEntity_Move->addComponent(cuboidTransform_Move);

    m_cuboidEntity = new Qt3DCore::QEntity(rootEntity);
    m_cuboidEntity->addComponent(cuboid_mid);
    m_cuboidEntity->addComponent(cuboidMaterial);
    m_cuboidEntity->addComponent(cuboidTransform);

    m_cuboidEntity_1 = new Qt3DCore::QEntity(rootEntity);
    m_cuboidEntity_1->addComponent(cuboid_mid);
    m_cuboidEntity_1->addComponent(cuboidMaterial);
    m_cuboidEntity_1->addComponent(cuboidTransform);

    m_cuboidEntity_2 = new Qt3DCore::QEntity(rootEntity);
    m_cuboidEntity_2->addComponent(cuboid);
    m_cuboidEntity_2->addComponent(cuboidMaterial);
    m_cuboidEntity_2->addComponent(cuboidTransform2);

    m_cuboidEntity_b = new Qt3DCore::QEntity(rootEntity);
    m_cuboidEntity_b->addComponent(cuboid_B);
    m_cuboidEntity_b->addComponent(cuboidMaterial_b);
    m_cuboidEntity_b->addComponent(cuboidTransform_b);
    //Second Motor
    m_cuboidEntity_0_2 = new Qt3DCore::QEntity(rootEntity);
    m_cuboidEntity_0_2->addComponent(cuboid_2);
    m_cuboidEntity_0_2->addComponent(cuboidMaterial);
    m_cuboidEntity_0_2->addComponent(cuboidTransform_2);

    m_cuboidEntity_1_2 = new Qt3DCore::QEntity(rootEntity);
    m_cuboidEntity_1_2->addComponent(cuboid_Move_2);
    m_cuboidEntity_1_2->addComponent(cuboidMaterial);
    m_cuboidEntity_1_2->addComponent(cuboidTransform_Move_2);

    m_cuboidEntity_b_2 = new Qt3DCore::QEntity(rootEntity);
    m_cuboidEntity_b_2->addComponent(cuboid_Move_b);
    m_cuboidEntity_b_2->addComponent(cuboidMaterial_b);
    m_cuboidEntity_b_2->addComponent(cuboidTransform_Move_2_2);
    //Third Motor
    m_cuboidEntity_0_3 = new Qt3DCore::QEntity(rootEntity);
    m_cuboidEntity_0_3->addComponent(cuboid_3);
    m_cuboidEntity_0_3->addComponent(cuboidMaterial);
    m_cuboidEntity_0_3->addComponent(cuboidTransform_Move_3);

    m_cuboidEntity_1_3 = new Qt3DCore::QEntity(rootEntity);
    m_cuboidEntity_1_3->addComponent(cuboid_small_3);
    m_cuboidEntity_1_3->addComponent(cuboidMaterial);
    m_cuboidEntity_1_3->addComponent(cuboidTransform_3);

    m_cuboidEntity_b_3 = new Qt3DCore::QEntity(rootEntity);
    m_cuboidEntity_b_3->addComponent(cuboid_Move_b_3);
    m_cuboidEntity_b_3->addComponent(cuboidMaterial_b);
    m_cuboidEntity_b_3->addComponent(cuboidTransform_Move_2_3);

    m_cuboidEntity_Move_3 = new Qt3DCore::QEntity(rootEntity);
    m_cuboidEntity_Move_3->addComponent(cuboid_Move_3);
    m_cuboidEntity_Move_3->addComponent(cuboidMaterial);
    m_cuboidEntity_Move_3->addComponent(cuboidTransform_Move_3_3);

    // Set root object of the scene
    view->setRootEntity(rootEntity);
    // Create control widgets


    //QCheckBox *torusCB = new QCheckBox(widget);
    label_TR_SW_1 = new QLabel(widget);
    label_TR_SW_2 = new QLabel(widget);
    label_TR_SW_3 = new QLabel(widget);
    label_TR_SW_4 = new QLabel(widget);
    label_TR_SW_5 = new QLabel(widget);
    label_TR_SW_6 = new QLabel(widget);
    label_TR_SW_7 = new QLabel(widget);
    label_TR_SW_8 = new QLabel(widget);
    label_TR_SW_9 = new QLabel(widget);

    label_TR_SW_1->setText("TR_SW_1 : ON（大电机靠电机）");
    label_TR_SW_2->setText("TR_SW_2 : OFF（大电机远离电机）");
    label_TR_SW_3->setText("TR_SW_3 : OFF（中电机靠电机）");
    label_TR_SW_4->setText("TR_SW_4 : ON（中电机远离电机）");
    label_TR_SW_5->setText("TR_SW_5 : ON（小电机靠电机）");
    label_TR_SW_6->setText("TR_SW_6 : OFF（小电机远离电机）");
    label_TR_SW_7->setText(QString("X Step/Postion ："));
    label_TR_SW_8->setText(QString("Y Step/Postion ："));
    label_TR_SW_9->setText(QString("Z Step/Postion ："));
    QLabel *label_TR_SW_Van = new QLabel(widget);
    label_TR_SW_Van->setText("");
    vLayout->addWidget(label_TR_SW_1);
    vLayout->addWidget(label_TR_SW_2);
    vLayout->addWidget(label_TR_SW_3);
    vLayout->addWidget(label_TR_SW_4);
    vLayout->addWidget(label_TR_SW_5);
    vLayout->addWidget(label_TR_SW_6);
    vLayout->addWidget(label_TR_SW_Van);
    vLayout->addWidget(label_TR_SW_7);
    vLayout->addWidget(label_TR_SW_8);
    vLayout->addWidget(label_TR_SW_9);

    // Show window
    widget->resize(600, 600);
    //end
    initActionsConnections();

    connect(serial, static_cast<void (QSerialPort::*)(QSerialPort::SerialPortError)>(&QSerialPort::error),
            this, &MainWindow::handleError);
//! [2]
    connect(serial, &QSerialPort::readyRead, this, &MainWindow::readData);
//! [2]
    connect(console, &Console::getData, this, &MainWindow::writeData);
//! [3]
}
//! [3]

MainWindow::~MainWindow()
{
    delete settings;
    delete ui;
}

//! [4]
void MainWindow::openSerialPort()
{
    SettingsDialog::Settings p = settings->settings();
    serial->setPortName(p.name);
    serial->setBaudRate(p.baudRate);
    serial->setDataBits(p.dataBits);
    serial->setParity(p.parity);
    serial->setStopBits(p.stopBits);
    serial->setFlowControl(p.flowControl);
    if (serial->open(QIODevice::ReadWrite)) {
        console->setEnabled(true);
        console->setLocalEchoEnabled(p.localEchoEnabled);
        ui->actionConnect->setEnabled(false);
        ui->actionDisconnect->setEnabled(true);
        ui->actionConfigure->setEnabled(false);
        showStatusMessage(tr("Connected to %1 : %2, %3, %4, %5, %6")
                          .arg(p.name).arg(p.stringBaudRate).arg(p.stringDataBits)
                          .arg(p.stringParity).arg(p.stringStopBits).arg(p.stringFlowControl));
    } else {
        QMessageBox::critical(this, tr("Error"), serial->errorString());

        showStatusMessage(tr("Open error"));
    }
}
//! [4]

//! [5]
void MainWindow::closeSerialPort()
{
    if (serial->isOpen())
        serial->close();
    console->setEnabled(false);
    ui->actionConnect->setEnabled(true);
    ui->actionDisconnect->setEnabled(false);
    ui->actionConfigure->setEnabled(true);
    showStatusMessage(tr("Disconnected"));
}
//! [5]

void MainWindow::about()
{
    QMessageBox::about(this, tr("About"),
                       tr("About Simple Terminal & X_Y_Z_Drawer -- Flame"));
}

//! [6]
void MainWindow::writeData(const QByteArray &data)
{
    static QByteArray datanew;
    if(data=="\n")
    {
        serial->write(datanew.append("#"));
        datanew.clear();
    }
    if(data!="\n")
    datanew.append(data);
}
//! [6]
double x_wave_filter(int filter_num)
{
    static int wave[4]={0,0,0,0};
    int m; double count=0; int f;
    for(m=0;m<=2;m++) wave[m]=wave[m+1];
    wave[3]=filter_num;
    int a=wave[0],b=wave[1],c=wave[2],d=wave[3];
    if(a<b){f=a; a=b; b=f;}
    if(a<c){f=a; a=c; c=b; b=f;}
    if(a<d){f=a; a=d; d=c; c=b; b=f;}
    if(b<c){f=b;b=c;c=f;}
    if(b<d){f=b;b=d;d=c;c=f;}
    if(c<d){f=c;c=d;d=f;}

    count=b;
    return count;
}
double y_wave_filter(int filter_num)
{
    static int wave[4]={0,0,0,0};
    int m; double count=0; int f;
    for(m=0;m<=2;m++) wave[m]=wave[m+1];
    wave[3]=filter_num;
    int a=wave[0],b=wave[1],c=wave[2],d=wave[3];
    if(a<b){f=a; a=b; b=f;}
    if(a<c){f=a; a=c; c=b; b=f;}
    if(a<d){f=a; a=d; d=c; c=b; b=f;}
    if(b<c){f=b;b=c;c=f;}
    if(b<d){f=b;b=d;d=c;c=f;}
    if(c<d){f=c;c=d;d=f;}

    count=b;
    return count;
}
double z_wave_filter(int filter_num)
{
    static int wave[4]={0,0,0,0};
    int m; double count=0; int f;
    for(m=0;m<=2;m++) wave[m]=wave[m+1];
    wave[3]=filter_num;
    int a=wave[0],b=wave[1],c=wave[2],d=wave[3];
    if(a<b){f=a; a=b; b=f;}
    if(a<c){f=a; a=c; c=b; b=f;}
    if(a<d){f=a; a=d; d=c; c=b; b=f;}
    if(b<c){f=b;b=c;c=f;}
    if(b<d){f=b;b=d;d=c;c=f;}
    if(c<d){f=c;c=d;d=f;}

    count=b;
    return count;
}
//! [7]
void MainWindow::readData()
{
    //6.5 y 7.7 z 19.7 x
    int x=0,y=0,z=0;
    int x_max=12672,y_max=7646,z_max=39181;
    float x_real_max=6.5,y_real_max=7.7,z_real_max=19.7;
    QByteArray data = serial->readAll();
    console->putData(data);
    QString string=data;
    if(data.mid(0,1)==QString("p"))
    {
        x=string.mid(1,string.indexOf("x")-1).toInt();
        y=string.mid(string.indexOf("x")+1,string.indexOf("y")-string.indexOf("x")-1).toInt();
        z=string.mid(string.indexOf("y")+1,string.indexOf("z")-string.indexOf("y")-1).toInt();

        X=z_wave_filter(z);
        Z=y_wave_filter(y);
        Y=x_wave_filter(x);

        label_TR_SW_7->setText(QString("X Step/Position ：").append(QString::number(X).append("/")).append(QString::number(X/z_max*z_real_max)));
        label_TR_SW_8->setText(QString("Y Step/Position ：").append(QString::number(Y).append("/")).append(QString::number(Y/x_max*x_real_max)));;
        label_TR_SW_9->setText(QString("Z Step/Position ：").append(QString::number(Z).append("/")).append(QString::number(Z/y_max*y_real_max)));;

        X=X/z_max;
        Z=Z/y_max;
        Y=Y/x_max;

        emit datachange(X*2000,Y*2000,Z*2000);

        X=X*8.6-4.3;
        Y=Y*4.2;
        Z=Z*5.9;

        cylinderTransform_2->setTranslation(QVector3D(X, -0.4f, 0.65f+3.5f));
        cylinderTransform2_2->setTranslation(QVector3D(X, 0.4f, 0.65f+3.5f));
        cylinderTransform3_2->setTranslation(QVector3D(X, 0.0f, 0.65f+3.5f));
        cylinderTransform_3->setTranslation(QVector3D(X+0.6, 0.0f, -0.3+0.55+Z+0.5));
        cylinderTransform2_3->setTranslation(QVector3D(X+0.6, 0.0f, 0.5f+0.55+Z));
        cylinderTransform3_3->setTranslation(QVector3D(X+0.6, 0.0f, 0.55+Z+0.5+0.3));
        cuboidTransform_Move->setTranslation(QVector3D(X, 0.0f, 0.0f));
        cuboidTransform_2->setTranslation(QVector3D(X, 0.0f, 0.5f+7+0.55));
        cuboidTransform_Move_2->setTranslation(QVector3D(X, 0.0f ,0.5f+0.55+Z));
        cuboidTransform_Move_2_2->setTranslation(QVector3D(X-0.6-0.1, 0.0f ,0.5f+4));
        cuboidTransform_3->setTranslation(QVector3D(X+0.2+0.5+0.1, -2.5f-0.15,0.5f+0.55+Z));
        cuboidTransform_Move_3->setTranslation(QVector3D(X+0.2+0.5+0.1, 2.5f+0.45 ,0.5f+0.55+Z));
        cuboidTransform_Move_2_3->setTranslation(QVector3D(X+0.2+0.05, 0.0f+0.3 ,0.5f+0.55+Z));
        cuboidTransform_Move_3_3->setTranslation(QVector3D(X+0.2+0.5, 2.5f-Y-0.4 ,0.5f+0.55+Z));
    }
    if(data.mid(0,1)==QString("g"))
    {
        //x_max=string.mid(1,string.indexOf("x")-1).toInt();
        //y_max=string.mid(string.indexOf("x")+1,string.indexOf("y")-string.indexOf("x")-1).toInt();
        //z_max=string.mid(string.indexOf("y")+1,string.indexOf("z")-string.indexOf("y")-1).toInt();
        //if((x_max>0)&&(y_max>0)&&(z_max>0)){
        //label_TR_SW_7->setText(QString("X speed ：").append(QString::number(20000/z_max)));
        //label_TR_SW_8->setText(QString("Y speed ：").append(QString::number(7000/x_max)));
        //label_TR_SW_9->setText(QString("Z speed ：").append(QString::number(8000/y_max)));
        //}
    }
    if((data.mid(0,1)==QString("S"))&&(data.length()==7))
    {
        if(data.mid(1,1)==QString("0")) label_TR_SW_1->setText("TR_SW_1 : OFF（大电机靠电机）"); else label_TR_SW_1->setText("TR_SW_1 : ON（大电机靠电机）");
        if(data.mid(2,1)==QString("0")) label_TR_SW_2->setText("TR_SW_2 : OFF（大电机远离电机）"); else label_TR_SW_2->setText("TR_SW_2 : ON（大电机远离电机）");
        if(data.mid(3,1)==QString("0")) label_TR_SW_3->setText("TR_SW_3 : OFF（中电机靠电机）"); else label_TR_SW_3->setText("TR_SW_3 : ON（中电机靠电机）");
        if(data.mid(4,1)==QString("0")) label_TR_SW_4->setText("TR_SW_4 : OFF（中电机远离电机）"); else label_TR_SW_4->setText("TR_SW_4 : ON（中电机远离电机）");
        if(data.mid(5,1)==QString("0")) label_TR_SW_5->setText("TR_SW_5 : OFF（小电机靠电机）"); else label_TR_SW_5->setText("TR_SW_5 : ON（小电机靠电机）");
        if(data.mid(6,1)==QString("0")) label_TR_SW_6->setText("TR_SW_6 : OFF（小电机远离电机）"); else label_TR_SW_6->setText("TR_SW_6 : ON（小电机远离电机）");
    }
}
//! [7]

//! [8]
void MainWindow::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        QMessageBox::critical(this, tr("Critical Error"), serial->errorString());
        closeSerialPort();
    }
}
//! [8]

void MainWindow::initActionsConnections()
{
    connect(ui->actionConnect, &QAction::triggered, this, &MainWindow::openSerialPort);
    connect(ui->actionDisconnect, &QAction::triggered, this, &MainWindow::closeSerialPort);
    connect(ui->actionQuit, &QAction::triggered, this, &MainWindow::close);
    connect(ui->actionConfigure, &QAction::triggered, settings, &MainWindow::show);
    connect(ui->actionClear, &QAction::triggered, console, &Console::clear);
    connect(ui->actionAbout, &QAction::triggered, this, &MainWindow::about);
    connect(ui->actionAboutQt, &QAction::triggered, qApp, &QApplication::aboutQt);
    connect(ui->actionAboutQt, &QAction::triggered, qApp, &QApplication::aboutQt);
    connect(ui->actionOpenDrawer,&QAction::triggered,container,&QWidget::show);
    connect(ui->actionCloseDrawer,&QAction::triggered,container,&QWidget::close);
    connect(ui->actionDatachange,&QAction::triggered,this,&MainWindow::scatterChangeData);
    connect(ui->actionOpen,&QAction::triggered,this->motorcontrol,&MotorControl::show);
    connect(ui->actionClose,&QAction::triggered,this->motorcontrol,&MotorControl::close);
    connect(ui->action3DShow,&QAction::triggered,this->widget,&QWidget::show);
    connect(ui->action3DClose,&QAction::triggered,this->widget,&QWidget::close);
    connect(this,SIGNAL(datachange(int,int,int)),this,SLOT(scatterDataChange(int,int,int)));
    connect(this->motorcontrol,SIGNAL(MotorDataChange(int,bool,bool)),this,SLOT(motorDataSend(int,bool,bool)));

}

void MainWindow::showStatusMessage(const QString &message)
{
    status->setText(message);
}

void MainWindow::scatterDataChange(int x, int y, int z)
{

    series->dataProxy()->removeItems(0,1);
    data.clear();
    data <<QVector3D(x, y, z);
    series->dataProxy()->addItems(data);
}

void MainWindow::scatterChangeData()
{
    //static int x=10,y=10,z=10;
    //emit datachange(x++,y++,z++);
}

void MainWindow::motorDataSend(int Motornumber, bool Ward, bool State)
{
    QString string;
    switch(Motornumber)
    {
        case 0: string='0'; break;
        case 1: string='1'; break;
        case 2: string='2'; break;
        case 4: string='m'; break;
        case 5: string='5'; break;
        case 6: string='6'; break;
        case 7: string='g'; break;
        default : string=' '; break;
    }
    switch(Ward==true)
    {
        case 1: string.append('1'); break;
        case 0: string.append('0'); break;
    }
    switch(State==true)
    {
        case 1: string.append('1'); break;
        case 0: string.append('0'); break;
    }
    string.append('#');
    serial->write(string.toUtf8());
}
