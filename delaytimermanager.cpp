#include "delaytimermanager.h"

DelayTimerManager::DelayTimerManager()
{
    enabled = false;
    delaytime = 0.0;
}

DelayTimerManager::~DelayTimerManager()
{

}

bool DelayTimerManager::isEnabled()
{
    return enabled;
}

void DelayTimerManager::setEnable(bool en)
{
    enabled = en;
}

double DelayTimerManager::getDelaytime()
{
    return delaytime;
}

void DelayTimerManager::setDelaytime(double time)
{
    delaytime = time;
}
