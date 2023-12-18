#include "mugshot.h"

MugShot::MugShot(QObject *parent):QObject(parent)
{

}

int MugShot::takeMugShot()
{
    // Open the default camera (usually camera index 0)
    cv::VideoCapture cap(0);

    // Check if the camera opened successfully
    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open camera." << std::endl;
        return -1;
    }

    // Capture one frame from the camera
    cv::Mat frame;
    cap >> frame;

    // Check if the frame was captured successfully
    if (frame.empty()) {
        std::cerr << "Error: Could not capture frame." << std::endl;
        return -1;
    }


    cap.release();

        cv::cvtColor(frame, frame,cv::COLOR_BGR2RGB);
    emit mugShotTaken(QImage(frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888));
    return 0;
}
