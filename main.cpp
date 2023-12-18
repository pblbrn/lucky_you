// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause


#include "threaddata.h"
#include "lucky_you.h"
#include "batterystatus.h"
#include <thread>
#include <QtWidgets/qapplication.h>
#include <QtCore/QLoggingCategory>

ThreadData threadData;

BatteryStatus bs;


void monitorBattery(void)
{
    bs.batteryStatusMonitor();
}
void get(Lucky_you *app)
{
    app->getStatusChanged();
}


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    threadData.monitor  = true;
    threadData.pbatteryStatus = std::make_unique<std::thread>(monitorBattery);
    Lucky_you d;
    d.show();
    std::thread taker(get, &d);

    app.exec();

    threadData.monitor = false;
    threadData.pbatteryStatus->join();
    taker.join();

    return 0;
}
/**
Instanz von bt generieren
widget generieren
überwachung als thread implementieren
bei event and widget und an bt weitergeben
bei message status abfragen dann and bt weitergeben.
**/
