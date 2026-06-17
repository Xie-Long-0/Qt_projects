#include "widget.h"
#include "ui_widget.h"
#include <QScroller>
#include <QListWidgetItem>
#include <QPixmap>
#include <QDir>
#include <QDateTime>
#include <QMessageBox>
#include <QDebug>

#include "CustomListItemWidget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui->listWidget->setAttribute(Qt::WA_AcceptTouchEvents);
    QScroller::grabGesture(ui->listWidget->viewport(), QScroller::TouchGesture);
    QScroller::grabGesture(ui->listWidget->viewport(), QScroller::LeftMouseButtonGesture);

    connect(ui->btn_load, &QPushButton::clicked, this, &Widget::onLoad);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::onLoad()
{
    ui->listWidget->clear();

    QDir dir;
    dir.cd("source");
    if (!dir.exists())
    {
        QMessageBox::warning(this, tr("提示"), tr("内容不存在！"));
        qWarning() << "path:" << dir.absolutePath();
        return;
    }

    auto filelist = dir.entryInfoList({"*.png", "*.jpg", "*.bmp"}, QDir::Files);
    if (filelist.isEmpty())
    {
        QMessageBox::warning(this, tr("提示"), tr("内容不存在！"));
        qWarning() << "no any files in" << dir.absolutePath();
        return;
    }

    for (auto &fileinfo : filelist)
    {
        QPixmap pix(fileinfo.filePath());
        auto w = new CustomListItemWidget(pix, fileinfo.baseName(),
                                          fileinfo.completeSuffix(),
                                          fileinfo.fileTime(QFile::FileModificationTime).toString(),
                                          QString::number(fileinfo.size()));
        QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
        item->setSizeHint(w->sizeHint());
        ui->listWidget->setItemWidget(item, w);
    }
}
