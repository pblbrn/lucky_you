#ifndef THREADDATA_H
#define THREADDATA_H

#include <systemd/sd-device.h>
#include <thread>
#include <atomic>
#include <memory>
#include <condition_variable>

/**
 * @brief The ThreadData struct holds several variables to get the batterystatus and if the status is changed
 * @var *device: placeholder to communicate with systemd
 * @var current_status: string with the current battery status
 * @var pbatteryStatus: unique_ptr to the batteryStatus thread
 * @var cv_changeStatus: condition variable to notify other threads when the battery status changed
 */
struct ThreadData {

    sd_device *device = NULL;
    std::string current_status = "Charging";
    std::atomic<bool> monitor = false;
    std::unique_ptr<std::thread> pbatteryStatus = nullptr;
    std::condition_variable cv_changeStatus;
};

extern ThreadData threadData;

#endif // THREADDATA_H
