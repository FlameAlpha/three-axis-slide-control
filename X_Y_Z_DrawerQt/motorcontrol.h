void on_pushButton_clicked();
void on_Play_Circle_clicked();
void on_pushButton_clicked();
#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

#include <QWidget>

class MotorData
{
public:
    int Motor_number;
    bool Motor_state;
    bool Motor_Ward;

};

class MotorDataAll
{
public:
    MotorData Motor_0;
    MotorData Motor_1;
    MotorData Motor_2;
};

namespace Ui {
class MotorControl;
}

class MotorControl : public QWidget
{
    Q_OBJECT

public:
    explicit MotorControl(QWidget *parent = 0);
    ~MotorControl();

private slots:
    void on_Start_clicked();

    void on_Forward_clicked();

    void on_BackWard_clicked();

    void on_Stop_clicked();

    void on_Start_2_clicked();

    void on_Forward_2_clicked();

    void on_BackWard_2_clicked();

    void on_Stop_2_clicked();

    void on_Start_3_clicked();

    void on_Forward_3_clicked();

    void on_BackWard_3_clicked();

    void on_Stop_3_clicked();

    void on_pushButton_2_clicked();

    void on_Close_Play_clicked();

    void on_Play_Square_clicked();

    void on_PosButton_clicked();

    void on_Close_Play_C_clicked();

    void on_Play_Circle_clicked();

    void on_pushButton_clicked();

signals:
    /* Motornumber 电机数
     * Ward 方向 0前 1后
     * state 状态 1开 0关*/
    void MotorDataChange(int Motornumber,bool Ward,bool State);

private:
    Ui::MotorControl *ui;
    MotorDataAll *motordata;

};

#endif // MOTORCONTROL_H
