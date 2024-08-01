#pragma once

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class ImageView;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_openImgBtn_clicked();
    void on_zoomInBtn_clicked();
    void on_zoomOutBtn_clicked();
    void on_originalBtn_clicked();
    void on_centerImgBtn_clicked();
    void on_adjustImgBtn_clicked();

    void onScaleChanged(double factor);

private:
    Ui::Widget *ui;
    ImageView *gv = nullptr;
};
