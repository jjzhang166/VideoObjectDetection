#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSharedPointer>

#include "opencv2/opencv.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void resetMenus();
    void on_actionOpen_Video_triggered();

    void on_actionTest_triggered();

private:
    Ui::MainWindow *ui;

    QSharedPointer<cv::VideoCapture> _stream;
};

QImage Mat2QImage(const cv::Mat3b &src);

#endif // MAINWINDOW_H
