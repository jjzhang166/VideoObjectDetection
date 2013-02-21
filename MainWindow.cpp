#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QtDebug>
#include <QSettings>
#include <QImage>
#include <QLabel>
#include <QTimer>

const QString SETTING_LAST_VID_DIR = "lastVidDir";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resetMenus();
    _label = QSharedPointer<QLabel>(new QLabel());
}

MainWindow::~MainWindow()
{
    delete ui;
}

//private slot
void MainWindow::resetMenus()
{
    bool gotValidVideo = true;

    if (_stream.isNull())
        gotValidVideo = false;
    else if (_stream->get(CV_CAP_PROP_POS_AVI_RATIO) == 1.0)
        gotValidVideo = false;

    this->ui->actionTest->setEnabled(gotValidVideo);
}

//private slot
void MainWindow::on_actionOpen_Video_triggered()
{
    QSettings settings;
    QString lastOpenDir;
    if (settings.contains(SETTING_LAST_VID_DIR))
        lastOpenDir = settings.value(SETTING_LAST_VID_DIR).toString();

    const QString filePath = QFileDialog::getOpenFileName(this,
                                                          "Select Video File");
    if (filePath.isEmpty())
        return;

    settings.setValue(SETTING_LAST_VID_DIR, filePath);

    _stream = QSharedPointer<cv::VideoCapture>(new cv::VideoCapture(filePath.toStdString()));

    if (!_stream->isOpened())
    {
        QMessageBox::warning(this, "Error", "Failed to open video");
        return;
    }

    _bgFinder = QSharedPointer<BackgroundFinder>(new BackgroundFinder());

    qDebug() << "Opened file" << filePath;
    this->resetMenus();
}

//private slot
void MainWindow::on_actionTest_triggered()
{
    //    const double fps = _stream->get(CV_CAP_PROP_FPS);
    //    const double frameCount = _stream->get(CV_CAP_PROP_FRAME_COUNT);

    //qDebug() << frameCount << "frames at" << fps << "fps.";

    cv::Mat frame;

    if (!_stream->read(frame))
    {
        qWarning() << "Failed to read frame";
        return;
    }

    QImage img = mat2QImage(frame);
    img = img.scaled(500, 500, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    _bgFinder->addFrame(img);
    const QImage& bgImg = _bgFinder->background();

    QImage diff(img.size(), img.format());
    for (int y = 0; y < img.height(); y++)
    {
        for (int x = 0; x < img.width(); x++)
        {
            const QRgb bg = bgImg.pixel(x,y);
            const int r1 = qRed(bg);
            const int g1 = qGreen(bg);
            const int b1 = qBlue(bg);

            const QRgb f = img.pixel(x,y);
            const int r2 = qRed(f);
            const int g2 = qGreen(f);
            const int b2 = qBlue(f);

            const int totalDiff = qAbs<int>(r1 - r2) + qAbs<int>(g1 - g2) + qAbs<int>(b1 - b2);
            if (totalDiff > 15)
                diff.setPixel(x,y, img.pixel(x,y));
        }
    }

    _label->setPixmap(QPixmap::fromImage(diff));
    _label->show();
    QTimer::singleShot(1, this, SLOT(on_actionTest_triggered()));

    frame.release();

    //qDebug() << "Do it";
}

QImage mat2QImage(const cv::Mat3b &src) {
    QImage dest(src.cols, src.rows, QImage::Format_ARGB32);
    for (int y = 0; y < src.rows; ++y)
    {
        const cv::Vec3b *srcrow = src[y];
        QRgb *destrow = (QRgb*)dest.scanLine(y);
        for (int x = 0; x < src.cols; ++x)
        {
            destrow[x] = qRgba(srcrow[x][2], srcrow[x][1], srcrow[x][0], 255);
        }
    }
    return dest;
}

