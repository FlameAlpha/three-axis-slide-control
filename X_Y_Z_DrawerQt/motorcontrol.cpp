#include "motorcontrol.h"
#include "ui_motorcontrol.h"

MotorControl::MotorControl(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MotorControl)
{
    motordata=new MotorDataAll;
    motordata->Motor_0.Motor_number=0;
    motordata->Motor_1.Motor_number=1;
    motordata->Motor_2.Motor_number=2;
    ui->setupUi(this);
}

MotorControl::~MotorControl()
{
    delete ui;
}
//[1]
void MotorControl::on_Start_clicked()
{
    if(motordata->Motor_0.Motor_state!=1)
    {
        motordata->Motor_0.Motor_state=1;
    }
    emit(MotorDataChange(motordata->Motor_0.Motor_number,motordata->Motor_0.Motor_Ward,motordata->Motor_0.Motor_state));

}
void MotorControl::on_Forward_clicked()
{
    if(motordata->Motor_0.Motor_Ward!=0)
    {
        motordata->Motor_0.Motor_Ward=0;
    }
    emit(MotorDataChange(motordata->Motor_0.Motor_number,motordata->Motor_0.Motor_Ward,motordata->Motor_0.Motor_state));
}


void MotorControl::on_BackWard_clicked()
{
    if(motordata->Motor_0.Motor_Ward!=1)
    {
        motordata->Motor_0.Motor_Ward=1;
    }
    emit(MotorDataChange(motordata->Motor_0.Motor_number,motordata->Motor_0.Motor_Ward,motordata->Motor_0.Motor_state));

}


void MotorControl::on_Stop_clicked()
{
    if(motordata->Motor_0.Motor_state!=0)
    {
        motordata->Motor_0.Motor_state=0;
    }
    emit(MotorDataChange(motordata->Motor_0.Motor_number,motordata->Motor_0.Motor_Ward,motordata->Motor_0.Motor_state));

}
//[2]
void MotorControl::on_Start_2_clicked()
{
    if(motordata->Motor_1.Motor_state!=1)
    {
        motordata->Motor_1.Motor_state=1;
    }
    emit(MotorDataChange(motordata->Motor_1.Motor_number,motordata->Motor_1.Motor_Ward,motordata->Motor_1.Motor_state));

}
void MotorControl::on_Forward_2_clicked()
{
    if(motordata->Motor_1.Motor_Ward!=0)
    {
        motordata->Motor_1.Motor_Ward=0;
    }
    emit(MotorDataChange(motordata->Motor_1.Motor_number,motordata->Motor_1.Motor_Ward,motordata->Motor_1.Motor_state));

}


void MotorControl::on_BackWard_2_clicked()
{
    if(motordata->Motor_1.Motor_Ward!=1)
    {
        motordata->Motor_1.Motor_Ward=1;
    }
    emit(MotorDataChange(motordata->Motor_1.Motor_number,motordata->Motor_1.Motor_Ward,motordata->Motor_1.Motor_state));

}


void MotorControl::on_Stop_2_clicked()
{
    if(motordata->Motor_1.Motor_state!=0)
    {
        motordata->Motor_1.Motor_state=0;
    }
    emit(MotorDataChange(motordata->Motor_1.Motor_number,motordata->Motor_1.Motor_Ward,motordata->Motor_1.Motor_state));

}
//[3]
void MotorControl::on_Start_3_clicked()
{
    if(motordata->Motor_2.Motor_state!=1)
    {
        motordata->Motor_2.Motor_state=1;
    }
    emit(MotorDataChange(motordata->Motor_2.Motor_number,motordata->Motor_2.Motor_Ward,motordata->Motor_2.Motor_state));

}
void MotorControl::on_Forward_3_clicked()
{
    if(motordata->Motor_2.Motor_Ward!=0)
    {
        motordata->Motor_2.Motor_Ward=0;
    }
    emit(MotorDataChange(motordata->Motor_2.Motor_number,motordata->Motor_2.Motor_Ward,motordata->Motor_2.Motor_state));

}


void MotorControl::on_BackWard_3_clicked()
{
    if(motordata->Motor_2.Motor_Ward!=1)
    {
        motordata->Motor_2.Motor_Ward=1;
    }
    emit(MotorDataChange(motordata->Motor_2.Motor_number,motordata->Motor_2.Motor_Ward,motordata->Motor_2.Motor_state));

}


void MotorControl::on_Stop_3_clicked()
{
    if(motordata->Motor_2.Motor_state!=0)
    {
        motordata->Motor_2.Motor_state=0;
    }
          emit(MotorDataChange(motordata->Motor_2.Motor_number,motordata->Motor_2.Motor_Ward,motordata->Motor_2.Motor_state));
}

void MotorControl::on_pushButton_2_clicked()
{
    this->close();
}

void MotorControl::on_Close_Play_clicked()
{
    emit(MotorDataChange(5,false,false));
}

void MotorControl::on_Play_Square_clicked()
{
    emit(MotorDataChange(5,true,false));
}

void MotorControl::on_PosButton_clicked()
{
    emit(MotorDataChange(7,false,false));
}

void MotorControl::on_Play_Circle_clicked()
{
    emit(MotorDataChange(6,true,false));
}

void MotorControl::on_Close_Play_C_clicked()
{
    emit(MotorDataChange(6,false,false));
}


void MotorControl::on_pushButton_clicked()
{
    emit(MotorDataChange(4,false,false));
}

