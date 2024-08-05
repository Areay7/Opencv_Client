#include "mainwindow.h"

#include <QApplication>
#include <opencv2/opencv.hpp>
// #include "FaceDetector.h"
#include <FaceDetector.h>

using namespace cv;
using namespace seeta::v2;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    // cv::namedWindow("frame");
    // Mat mt = imread("/Users/areay7/Downloads/logo.png");
    // imshow("frmae", mt);



    // seeta::ModelSetting::Device device = seeta::ModelSetting::CPU;
    // int id = 0;
    // seeta::ModelSetting FD_model("/Users/areay7/Opencv/SeetaFace2/build/bin/fd_2_00.dat", device, id);
    // seeta::FaceDetector FD(FD_model);

    return a.exec();
}
