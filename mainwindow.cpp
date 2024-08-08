#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //打开摄像头
    cap.open(0); //dev/video
    //启动定时器事件
    startTimer(100);

    //导入级联分类器文件
    cascade.load("/Users/areay7/Opencv/haarcascades/haarcascade_frontalface_alt2.xml");

    // QTcpSocket 当断开连接会发送 disconnected 信号，连接成功会发送 connected 信号
    connect(&msocket, &QTcpSocket::disconnected, this, &MainWindow::start_connect);
    connect(&msocket, &QTcpSocket::connected, this, &MainWindow::stop_connect);

    // 关联数据接受的函数
    connect(&msocket, &QTcpSocket::readyRead, this, &MainWindow::recv_data);

    // 连接服务器定时器
    connect(&mtimer, &QTimer::timeout, this, &MainWindow::timer_connect);
    mtimer.start(5000);

    flag = 0;

    ui->widgetLb->hide();

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

    // 把图片大小设置与窗口大小一样
    cv::resize(srcImage, srcImage, Size(480,480));

    Mat grayImage;
    //转灰度图
    cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);
    //检测人脸数据
    std::vector<Rect> faceRects;
    cascade.detectMultiScale(grayImage,faceRects);
    // qDebug()<< "size :" <<faceRects.size();
    if(faceRects.size()>0 && flag >= 0)
    {
        Rect rect = faceRects.at(0);//第一个人脸的矩形框
        // rectangle(srcImage,rect,Scalar(0,0,255));
        //移动人脸框（图片--QLabel）
        ui->headpicLb->move(rect.x,rect.y);

        if(flag > 2)
        {
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
        flag = -2;


        faceMat = srcImage(rect);
        // 保存
        imwrite("./face.jpg",faceMat);
        }

        flag++;

    }
    if(faceRects.size() == 0)
    {
        //把人脸框移动到中心位置
        ui->headpicLb->move(140,100);
        flag = 0;
    }


    if(srcImage.data == nullptr) return;
    //把opencv里面的Mat格式数据（BGR）转Qt里面的QImage(RGB)
    cvtColor(srcImage,srcImage, COLOR_BGR2RGB);
    QImage image(srcImage.data,srcImage.cols, srcImage.rows,srcImage.step1(),QImage::Format_RGB888);
    // QPixmap mmp = QPixmap::fromImage(image);
    // 缩放图像使其适应 QLabel 的大小
    // QPixmap mmp = QPixmap::fromImage(image).scaled(ui->videoLb->size(), Qt::KeepAspectRatio);

    QPixmap mmp = QPixmap::fromImage(image);

    ui->videoLb->setPixmap(mmp);
}

void MainWindow::recv_data()
{
    QByteArray array = msocket.readAll();

    // {EmployeeID:%1, name:%2, department:物联网工程, time:%3}
    // JSON 数据解析
    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(array, &err);
    if(err.error != QJsonParseError::NoError)
    {
        qDebug() << "JSON 数据错误";
        return;
    }
    else
    {
        QJsonObject obj = doc.object();
        QString EmployeeID = obj.value("EmployeeID").toString();
        QString name = obj.value("name").toString();
        QString department = obj.value("department").toString();
        QString time = obj.value("time").toString();

        ui->numberEdit->setText(EmployeeID);
        ui->nameEdit->setText(name);
        ui->departmentEdit->setText(department);
        ui->timeEdit->setText(time);

        // 通过样式显示图片
        ui->headLb->setStyleSheet("border-radius:75px; background-image: url(./face.jpg);");
        ui->widgetLb->show();
    }


}

void MainWindow::timer_connect()
{
    // 连接服务器
    // msocket.connectToHost("192.168.1.17", 9999);
    msocket.connectToHost("127.0.0.1", 9999);
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
