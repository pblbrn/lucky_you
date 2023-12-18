#ifndef THREADDATA_H
#define THREADDATA_H

#include <systemd/sd-device.h>
#include <systemd/sd-login.h>
#include <systemd/sd-bus.h>
#include <systemd/sd-id128.h>
#include <thread>
#include <atomic>
#include <memory>
#include <condition_variable>

struct ThreadData {

    sd_device *device = NULL;
    std::string current_status = "Charging";
    std::atomic<bool> monitor = false;
    std::unique_ptr<std::thread> pbatteryStatus = nullptr;
    std::condition_variable cv_changeStatus;
};

extern ThreadData threadData;

#endif // THREADDATA_H
