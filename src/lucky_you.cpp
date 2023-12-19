#include "lucky_you.h"
#include "mugshot.h"
#include "server.h"
#include "speak.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "threaddata.h"
#include "ui_lucky_you.h"






#define PATH_BATT_CHARGE_NOW "/sys/class/power_supply/BAT0/subsystem/BAT0/status"

Lucky_you::Lucky_you(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Lucky_you)
{

    ui->setupUi(this);

    connect(ui->sendButton,&QPushButton::clicked,this,&Lucky_you::sendClicked);

    server = new Server(this);
    connect(server, QOverload<const QString &>::of(&Server::clientConnected),
            this, &Lucky_you::clientConnected);
    connect(this, &Lucky_you::sendMessage, server, &Server::sendMessage);
    connect(server,&Server::messageReceived,this,&Lucky_you::showMessage);

    server->startServer();

    speak = new Speak(this);
    connect(this, &Lucky_you::talk, speak, &Speak::talk);

    mugShot = new MugShot(this);
    connect(this, &Lucky_you::takeMugShot,mugShot, &MugShot::takeMugShot);
    connect(mugShot, &MugShot::mugShotTaken, this, &Lucky_you::showMugShot);
    ui->mugView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->mugView->setScene(new QGraphicsScene(this));
    ui->mugView->setRenderHint(QPainter::Antialiasing, true);
    ui->mugView->setRenderHint(QPainter::SmoothPixmapTransform, true);


}



Lucky_you::~Lucky_you()
{
    delete ui;
    delete mugShot;
    delete server;
    delete speak;

}


void Lucky_you::sendClicked()
{
    ui->sendButton->setEnabled(false);

    if (!threatMode)
    {
        threatMode = true;
        emit talk("Ready");
        emit sendMessage(QString::fromStdString(threadData.current_status));
        if (!m_clientConnected)
        {
            emit talk ("no client connected!");
        }
        ui->sendButton->setText("Stop");
    }

    else
    {
        threatMode = false;
        emit talk("Stop");
        ui->sendButton->setText("Start");
    }
    ui->sendButton->setEnabled(true);

}

void Lucky_you::clientConnected(const QString &name)
{
    m_clientConnected = true;
    ui->lastMessage->clear();
    ui->lastMessage->insert(QString::fromLatin1("%1").arg(name));

}
void Lucky_you::interpretMsg(const QString &sender, const QString &message)
{
    enum COMMANDS{ChargeStatus, Speak, Mugshot};

    int command = message.at(0).digitValue();
    switch (command) {
    case ChargeStatus:

        emit sendMessage(QString::fromStdString(threadData.current_status));
        break;
    case Speak:

        emit talk(message.mid(1));
        break;
    case Mugshot:
        emit takeMugShot();
        break;
    default:
        break;
    }
}
void Lucky_you::showMessage(const QString &sender, const QString &message)
{
    ui->lastMessage->clear();
    ui->lastMessage->insert(QString::fromLatin1("%1: %2").arg(sender,message));
    interpretMsg(sender, message);
}

void Lucky_you::showMugShot(QImage image)
{
    QString dir {QDir::currentPath()+"/MugShot.jpg"};
    image.save(dir);
    QPixmap pixmap{QPixmap::fromImage(image)};
    ui->mugView->scene()->clear();
    QGraphicsPixmapItem *p = ui->mugView->scene()->addPixmap(pixmap);
        ui->mugView->scene()->setSceneRect(pixmap.rect());
    ui->mugView->fitInView(p,Qt::KeepAspectRatio);
    ui->mugView->update();
}


void Lucky_you::getStatusChanged()
{
        while (threadData.monitor){
            lastStatus = threadData.current_status;
            std::unique_lock<std::mutex> qLocker{m_mu};
            threadData.cv_changeStatus.wait(qLocker,[this](){return (threatMode && !(lastStatus==threadData.current_status)) || exitNow;});
            if(threadData.monitor)
            {
                QString msg {QString::fromStdString("Status of battery changed to "+ threadData.current_status)};
                emit sendMessage(msg);
                if (threadData.current_status == "Discharging"){
                    emit takeMugShot();
                }
            }
        }
}



