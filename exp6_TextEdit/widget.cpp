#include "widget.h"
#include "ui_widget.h"

#include <QDebug>
#include <QFont>
#include <QColorDialog>
#include <QBrush>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //设置二态按钮
    ui->pushButton_Bold->setCheckable(true);
    ui->pushButton_Italic->setCheckable(true);
    ui->pushButton_Underline->setCheckable(true);

    ui->spinBox->setRange(0,72);
    ui->spinBox->setValue(11);
    ui->textEdit->setFontPointSize(11);

    //丰富文本编辑框初始内容
    ui->textEdit->setHtml("<b>粗体字的行<br></b>"
                          "<i>斜体字的行<br></i>"
                          "<u>下划线的行<br></u>"
                          "<font style=\"color: red;\">文本前景色<br></font>"
                          "<font style=\"background: yellow;\">文字背景色<br></font>"
                          "<font style=\"font-size: 18pt;\">字号大小变化的行<br></font>"
                          "<font style=\"font-family: 黑体;\">字体家族变化的行<br></font>"
                          );
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_Bold_clicked(bool checked)
{
    if (checked)
        ui->textEdit->setFontWeight(QFont::Bold);
    else
        ui->textEdit->setFontWeight(QFont::Normal);
    ui->textEdit->setFocus();
}

void Widget::on_pushButton_Italic_clicked(bool checked)
{
    ui->textEdit->setFontItalic(checked);
    ui->textEdit->setFocus();
}

void Widget::on_pushButton_Underline_clicked(bool checked)
{
    ui->textEdit->setFontUnderline(checked);
    ui->textEdit->setFocus();
}

void Widget::on_pushButton_FGColor_clicked()
{
    //调用颜色选择框
    QColor color = QColorDialog::getColor(Qt::black, this, tr("前景色"));
    if (color.isValid()) {
        ui->textEdit->setTextColor(color);
        //填充一个纯色图标
        QPixmap pix(20, 20);
        pix.fill(color);
        ui->pushButton_FGColor->setIcon(pix);
    }
    ui->textEdit->setFocus();
}

void Widget::on_pushButton_BGColor_clicked()
{
    QColor color = QColorDialog::getColor(Qt::black, this, tr("背景色"));
    if (color.isValid()) {
        ui->textEdit->setTextBackgroundColor(color);
        QPixmap pix(20, 20);
        pix.fill(color);
        ui->pushButton_BGColor->setIcon(QIcon(pix));
    }
    ui->textEdit->setFocus();
}

//根据光标位置或选中文本感知字体格式
void Widget::on_textEdit_currentCharFormatChanged(const QTextCharFormat &format)
{
    //检测粗体
    if (format.fontWeight() == QFont::Bold)
        ui->pushButton_Bold->setChecked(true);
    else
        ui->pushButton_Bold->setChecked(false);

    //检测斜体和下划线
    ui->pushButton_Italic->setChecked(format.fontItalic());
    ui->pushButton_Underline->setChecked(format.fontUnderline());

    //前景色
    QBrush brush = format.foreground();
    if (brush != Qt::NoBrush) {
        QPixmap pix(20, 20);
        pix.fill(brush.color());
        ui->pushButton_FGColor->setIcon(pix);
    }
    else {
        ui->pushButton_FGColor->setIcon(QIcon());
    }

    //背景色
    brush = format.background();
    if (brush != Qt::NoBrush) {
        QPixmap pix(20, 20);
        pix.fill(brush.color());
        ui->pushButton_BGColor->setIcon(pix);
    }
    else {
        ui->pushButton_BGColor->setIcon(QIcon());
    }

    //字号
    int fontsize = format.font().pointSize();
    if (fontsize == -1) //判断是否是pixel size
        fontsize = (int)(format.font().pixelSize() * 9.0 / 12.0);
    //ui->lineEdit_FontSize->setText(QString("").setNum(fontsize));
    ui->spinBox->setValue(fontsize);

    //字体族
    ui->fontComboBox->setCurrentText(format.font().family());
}

void Widget::on_spinBox_valueChanged(int arg1)
{
    ui->textEdit->setFontPointSize(arg1);
}

void Widget::on_fontComboBox_currentIndexChanged(const QString &arg1)
{
    ui->textEdit->setFontFamily(arg1);
    ui->textEdit->setFocus();
}

void Widget::on_textEdit_textChanged()
{
    qDebug() << ui->textEdit->toHtml() << endl;
    qDebug() << ui->textEdit->toPlainText() << endl;
}
