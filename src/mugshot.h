#ifndef MUGSHOT_H
#define MUGSHOT_H

#include <QObject>
#include <QImage>
#include <opencv2/opencv.hpp>

/**
 * @brief The MugShot class captures a image with opencv from the webcam
 */
class MugShot : public QObject
{
    Q_OBJECT
public:
    explicit MugShot(QObject *parent = nullptr);
signals:
    void mugShotTaken(QImage);
public slots:
    int takeMugShot();

};

#endif // MUGSHOT_H
