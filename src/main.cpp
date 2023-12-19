// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause


#include "threaddata.h"
#include "lucky_you.h"
#include "batterystatus.h"
#include <thread>
#include <QtWidgets/qapplication.h>
#include <QtCore/QLoggingCategory>

ThreadData threadData;

//BatteryStatus bs;


void monitorBattery(BatteryStatus *bs)
{
    bs->batteryStatusMonitor();
}
void getChange(Lucky_you *app)
{
    app->getStatusChanged();
}


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    BatteryStatus bs;

    threadData.monitor  = true;
    threadData.pbatteryStatus = std::make_unique<std::thread>(monitorBattery, &bs);
    Lucky_you d;
    d.show();
    std::thread statusChange(getChange, &d);

    app.exec();

    threadData.monitor = false;
    threadData.pbatteryStatus->join();
    threadData.cv_changeStatus.notify_all();
    statusChange.join();

    return 0;
}
