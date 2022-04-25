#pragma once

#include <QWidget>
#include <QSettings>
#include <QHash>
#include <QAction>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    // 打开文件
    void onOpenFileBtnClick();
    // 关闭文件
    void onCloseFileBtnClick();
    // 弹出选择文件窗口
    void onFileDialogBtnClick();
    // 删除账号信息
    void onDelEmailBtnClick();
    // 查找Key
    void onFindKeyBtnClick();
    // 设置Value
    void onSetValueBtnClick();
    // 删除Value
    void onDelValueBtnClick();
    // 弹出菜单
    void onMenuRequest(const QPoint &pos);
    // 复制操作
    void onActionCopyKey();
    void onActionCopyValue();

    void showToolWidgets();
    void hideToolWidgets();

private:
    Ui::Widget *ui;
    QSettings *m_ini = nullptr;
    QHash<QString, QVariant> m_hash;
};
