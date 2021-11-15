#ifndef DELAYTIMERMANAGER_H
#define DELAYTIMERMANAGER_H


class DelayTimerManager
{
public:
    DelayTimerManager();

    virtual ~DelayTimerManager();

public:
    bool isEnabled();

    void setEnable(bool en);

    double getDelaytime();

    void setDelaytime(double time);

private:
    bool enabled;
    double delaytime;
};

#endif // DELAYTIMERMANAGER_H
