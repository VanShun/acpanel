#ifndef AIRCONDCTRL_H
#define AIRCONDCTRL_H

#include <QObject>
class AirCondCtrl
{
public:
    AirCondCtrl();

    virtual ~AirCondCtrl();

public:
    enum WindSpeed {
        WindSpeed_Auto = 0,
        WindSpeed_Gear1,
        WindSpeed_Gear2,
        WindSpeed_Gear3,
        WindSpeed_GearMax
    };

    enum WindDir {
        WindDir_Auto = 0,
        WindDir_UpDown,
        WindDir_LeftRight,
        WindDir_Max
    };

    enum CtrlMode {
        AutoMode = 0,
        Cold,
        Dehumid,
        Blow,
        Heat,
        CtrlMode_Max
    };

    void SwitchPoweron(bool en);

    bool PowerisOn();

    void SetTemp(const double &temperature);

    double SettedTemp();

    double CurTemp();

    void SetWindSpeed(const enum WindSpeed &speed);

    WindSpeed WindSpeed();

    void SetWindDir(const enum WindDir &dir);

    WindDir WindDir();

    void SetCtrlMode(const enum CtrlMode &mode);

    CtrlMode CtrlMode();

private:
    bool m_poweron;
    double m_curtemp;
    double m_settemp;
    enum WindSpeed m_windspeed;
    enum WindDir m_winddir;
    enum CtrlMode m_ctrlmode;
};

#endif // AIRCONDCTRL_H
