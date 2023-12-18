#ifndef LUCKY_YOU_H
#define LUCKY_YOU_H

#include <QWidget>
#include <thread>
#include <condition_variable>
#include <fstream>

#include <QGraphicsScene>
#include <QImage>
#include <QPixmap>
#include <QGraphicsPixmapItem>
class Server;
class Speak;
class MugShot;
namespace Ui {
class Lucky_you;
}

class Lucky_you : public QWidget
{
    Q_OBJECT

public:
    explicit Lucky_you(QWidget *parent = nullptr);
    ~Lucky_you();
    void getStatusChanged();


signals:
    void sendMessage(const QString &message);
    void talk(const QString &text);
    void takeMugShot();

private slots:
    void sendClicked();
    void clientConnected(const QString &name);
    void showMessage(const QString &sender, const QString &message);
    void showMugShot(QImage image);


private:
    Ui::Lucky_you *ui;
    Server *server;
    Speak *speak;
    MugShot *mugShot;

    std::condition_variable cv_getStatus;
    std::mutex m_mu;
    std::string lastStatus;

    void interpretMsg(const QString &sender, const QString &message);
    bool m_clientConnected {false};
    bool threatMode{false};

};

#endif // LUCKY_YOU_H
