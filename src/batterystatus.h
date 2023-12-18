#ifndef BATTERYSTATUS_H
#define BATTERYSTATUS_H

#include <iostream>
#include <chrono>
#include <systemd/sd-device.h>
#include <systemd/sd-login.h>
#include <systemd/sd-bus.h>
#include <systemd/sd-id128.h>
#include <atomic>
#include <thread>
#include <memory>


#include "threaddata.h"

class BatteryStatus
{

public:
    BatteryStatus();
    void batteryStatusMonitor();
private:
    const std::string m_charging {"Charging"};
    const std::string m_discharging {"Discharging"};
    const std::string m_notCharging {"Not charging"};


};

#endif // BATTERYSTATUS_H

