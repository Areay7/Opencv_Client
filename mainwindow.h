#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <opencv2/opencv.hpp>
#include <QTcpSocket>
#include <QTimer>
#include <QDebug>

using namespace cv;
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //定时器事件
    void timerEvent(QTimerEvent *e);


private slots:
    void timer_connect();
    void stop_connect();
    void start_connect();

    void recv_data();

private:
    Ui::MainWindow *ui;

    //摄像头
    VideoCapture cap;
    //haar--级联分类器
    cv::CascadeClassifier cascade;

    // 创建网络套接字， 定时器
    QTcpSocket msocket;
    QTimer mtimer;
};
#endif // MAINWINDOW_H
