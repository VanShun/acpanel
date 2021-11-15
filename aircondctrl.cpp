#include "aircondctrl.h"

AirCondCtrl::AirCondCtrl()
{
    m_poweron = true;
    m_curtemp = 28; //init value
    m_settemp = 23; //default value
    m_ctrlmode = AirCondCtrl::AutoMode;
    m_windspeed = AirCondCtrl::WindSpeed_Auto;
    m_winddir = AirCondCtrl::WindDir_Auto;
}

AirCondCtrl::~AirCondCtrl()
{

}

void AirCondCtrl::SwitchPoweron(bool en)
{
    m_poweron = en;
}

bool AirCondCtrl::PowerisOn()
{
    return m_poweron;
}

void AirCondCtrl::SetTemp(const double &temperature)
{
    m_settemp = temperature;
}

double AirCondCtrl::SettedTemp()
{
    return m_settemp;
}

double AirCondCtrl::CurTemp()
{
    return m_curtemp;
}

void AirCondCtrl::SetWindSpeed(const enum AirCondCtrl::WindSpeed &speed)
{
    m_windspeed = speed;
}

enum AirCondCtrl::WindSpeed AirCondCtrl::WindSpeed()
{
    return m_windspeed;
}

void AirCondCtrl::SetWindDir(const enum AirCondCtrl::WindDir &dir)
{
    m_winddir = dir;
}

enum AirCondCtrl::WindDir AirCondCtrl::WindDir()
{
    return m_winddir;
}

void AirCondCtrl::SetCtrlMode(const enum AirCondCtrl::CtrlMode &mode)
{
    m_ctrlmode = mode;
}

enum AirCondCtrl::CtrlMode AirCondCtrl::CtrlMode()
{
    return m_ctrlmode;
}

