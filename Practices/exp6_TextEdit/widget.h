#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTextCharFormat>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_pushButton_Bold_clicked(bool checked);
    void on_pushButton_Italic_clicked(bool checked);
    void on_pushButton_Underline_clicked(bool checked);
    void on_pushButton_FGColor_clicked();
    void on_pushButton_BGColor_clicked();
    void on_spinBox_valueChanged(int arg1);
    void on_fontComboBox_currentIndexChanged(const QString &arg1);
    void on_textEdit_currentCharFormatChanged(const QTextCharFormat &format);

    void on_textEdit_textChanged();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
