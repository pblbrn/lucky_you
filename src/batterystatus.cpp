#include "batterystatus.h"
#include "threaddata.h"

BatteryStatus::BatteryStatus()
{
    threadData.device = nullptr;

    sd_device_new_from_syspath(&threadData.device, "/sys/class/power_supply/BAT0");

    const char *currentStatus;
    sd_device_get_property_value(threadData.device, "POWER_SUPPLY_STATUS", &currentStatus);
    threadData.current_status = currentStatus;

}



void BatteryStatus::batteryStatusMonitor() {
    while (threadData.monitor) {
        // Get current battery status
        const char *new_status;     //
        sd_device_new_from_syspath(&threadData.device, "/sys/class/power_supply/BAT0");

        int ret = sd_device_get_property_value(threadData.device, "POWER_SUPPLY_STATUS",  &new_status);
       if (ret < 0) {
            std::cerr << "Unable to get current battery status: " << strerror(-ret) << std::endl;
            break;
        }

        // Check for a change to discharging
        if (threadData.current_status.compare(m_discharging) != 0 && m_discharging.compare(new_status) == 0) {
            std::cout << "Battery is now discharging!" << std::endl;
            threadData.cv_changeStatus.notify_one();

        }
        if (threadData.current_status.compare(m_charging) != 0 && m_charging.compare(new_status) == 0) {
            std::cout << "Battery is now charging! all good" << std::endl;
            threadData.cv_changeStatus.notify_one();
        }
        if (threadData.current_status.compare(m_notCharging) != 0 && m_notCharging.compare(new_status) == 0) {
            std::cout << "Battery is now full! all good" << std::endl;
            threadData.cv_changeStatus.notify_one();
        }


        // Update current status
       threadData.current_status = new_status;

        // Sleep for a while before checking again
       std::this_thread::sleep_for(std::chrono::milliseconds(100));

    }
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

}


