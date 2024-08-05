#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //打开摄像头
    cap.open(1); //dev/video
    //启动定时器事件
    startTimer(100);

    //导入级联分类器文件
    cascade.load("/Users/areay7/Opencv/haarcascades/haarcascade_frontalface_alt2.xml");

    // QTcpSocket 当断开连接会发送 disconnected 信号，连接成功会发送 connected 信号
    connect(&msocket, &QTcpSocket::disconnected, this, &MainWindow::start_connect);
    connect(&msocket, &QTcpSocket::connected, this, &MainWindow::stop_connect);

    // 连接服务器定时器
    connect(&mtimer, &QTimer::timeout, this, &MainWindow::timer_connect);
    mtimer.start(5000);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timerEvent(QTimerEvent *e)
{
    //采集数据
    Mat srcImage;
    if(cap.grab())
    {
        cap.read(srcImage);//读取一帧数据
    }

    Mat grayImage;
    //转灰度图
    cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);
    //检测人脸数据
    std::vector<Rect> faceRects;
    cascade.detectMultiScale(grayImage,faceRects);
    qDebug()<< "size :" <<faceRects.size();
    if(faceRects.size()>0)
    {
        Rect rect = faceRects.at(0);//第一个人脸的矩形框
        // rectangle(srcImage,rect,Scalar(0,0,255));
        //移动人脸框（图片--QLabel）
        ui->headpicLb->move(rect.x,rect.y);

        // 把Mat数据转化为QbyteArray, 编码成 jpg 格式再发送
        std::vector<uchar> buff;
        cv::imencode(".jpg", srcImage, buff);
        QByteArray byte((const char *)buff.data(), buff.size());

        // 准备发送
        quint64 blockSize = byte.size();
        QByteArray sendData;
        QDataStream stream(&sendData, QIODevice::WriteOnly);
        stream.setVersion(QDataStream::Qt_5_14);
        stream << blockSize << byte;

        //发送
        msocket.write(sendData);

    }else
    {
        //把人脸框移动到中心位置
        ui->headpicLb->move(140,100);
    }


    if(srcImage.data == nullptr) return;
    //把opencv里面的Mat格式数据（BGR）转Qt里面的QImage(RGB)
    cvtColor(srcImage,srcImage, COLOR_BGR2RGB);
    QImage image(srcImage.data,srcImage.cols, srcImage.rows,srcImage.step1(),QImage::Format_RGB888);
    // QPixmap mmp = QPixmap::fromImage(image);
    // 缩放图像使其适应 QLabel 的大小
    QPixmap mmp = QPixmap::fromImage(image).scaled(ui->videoLb->size(), Qt::KeepAspectRatio);
    ui->videoLb->setPixmap(mmp);
}

void MainWindow::timer_connect()
{
    // 连接服务器
    msocket.connectToHost("192.168.1.17", 9999);
    qDebug() << "connecting";
}

void MainWindow::stop_connect()
{
    mtimer.stop();
    qDebug() << "success to connect";
}

void MainWindow::start_connect()
{
    mtimer.start(5000);
    qDebug() << "disconnected";
}
