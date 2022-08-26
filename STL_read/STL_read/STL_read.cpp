#include "STL_read.h"
#include <QDebug>
#include <QFile>
#include <QDataStream>
#include <QFileDialog>
#include <QMessageBox>

STL_read::STL_read(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    connect(ui.openBtn, &QPushButton::clicked, this, &STL_read::onOpenBtn);
}

STL_read::~STL_read()
{
}

void STL_read::onOpenBtn()
{
    auto file_name = QFileDialog::getOpenFileName(this, tr("打开STL文件"), "E:/", "STL files (*.stl)");
    if (file_name.isEmpty())
        return;

    QFile stl_file(file_name);
    if (!stl_file.open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(this, tr("错误"), tr("无法打开文件！"));
        return;
    }

    ui.pathEdit->setText(file_name);

    // 使用数据流读取
    QDataStream ds(&stl_file);

    // STL文件头，80字节，保存Solid file name
    char header[80] = {};
    qDebug() << "Read header bytes:" << ds.readRawData(header, 80);
    // 确保字符串结尾有空字符
    if (header[79] != '\0')
        header[79] = '\0';
    ui.headerLabel->setText(QString::fromLocal8Bit(header));

    bool is_binary = false;
    // 预读64字节判断是否是ASCII类型
    if (auto d = stl_file.peek(64); d.size() == 64)
    {
        for (int i = 0; i < 64; i++)
        {
            if (d[i] < 0 || d[i] > 127)
            {
                is_binary = true;
                break;
            }
        }
    }
    if (!is_binary)
    {
        QMessageBox::warning(this, tr("警告"), tr("该STL文件为ASCII类型，无法用本程序读取。"));
        return;
    }

    // 三角面片数
    char nubuf[4] = {};
    qDebug() << "Read number bytes:" << ds.readRawData(nubuf, 4);
    int *number = reinterpret_cast<int *>(nubuf);
    ui.numberLabel->setText(QByteArray::number(*number));

    char nodebuf[50] = {};
    float *nor[3] = {};
    float *p1[3] = {};
    float *p2[3] = {};
    float *p3[3] = {};

    // 读取前15个三角面信息，每个三角面占50字节
    for (uint i = 0; i < *number && i < 15; i++)
    {
        int ps = 0;
        ds.readRawData(nodebuf, 50);
        ui.itemList->insertRow(i);

        // 法向量
        nor[0] = reinterpret_cast<float *>(nodebuf + ps); ps += 4;
        nor[1] = reinterpret_cast<float *>(nodebuf + ps); ps += 4;
        nor[2] = reinterpret_cast<float *>(nodebuf + ps); ps += 4;
        auto twi0 = new QTableWidgetItem(QString("(%1, %2, %3)").arg(*nor[0]).arg(*nor[1]).arg(*nor[2]));
        ui.itemList->setItem(i, 0, twi0);

        // 顶点1
        p1[0] = reinterpret_cast<float *>(nodebuf + ps); ps += 4;
        p1[1] = reinterpret_cast<float *>(nodebuf + ps); ps += 4;
        p1[2] = reinterpret_cast<float *>(nodebuf + ps); ps += 4;
        auto twi1 = new QTableWidgetItem(QString("(%1, %2, %3)").arg(*p1[0]).arg(*p1[1]).arg(*p1[2]));
        ui.itemList->setItem(i, 1, twi1);

        // 顶点2
        p2[0] = reinterpret_cast<float *>(nodebuf + ps); ps += 4;
        p2[1] = reinterpret_cast<float *>(nodebuf + ps); ps += 4;
        p2[2] = reinterpret_cast<float *>(nodebuf + ps); ps += 4;
        auto twi2 = new QTableWidgetItem(QString("(%1, %2, %3)").arg(*p2[0]).arg(*p2[1]).arg(*p2[2]));
        ui.itemList->setItem(i, 2, twi2);

        // 顶点3
        p3[0] = reinterpret_cast<float *>(nodebuf + ps); ps += 4;
        p3[1] = reinterpret_cast<float *>(nodebuf + ps); ps += 4;
        p3[2] = reinterpret_cast<float *>(nodebuf + ps); ps += 4;
        auto twi3 = new QTableWidgetItem(QString("(%1, %2, %3)").arg(*p3[0]).arg(*p1[1]).arg(*p1[2]));
        ui.itemList->setItem(i, 3, twi3);
    }
}
