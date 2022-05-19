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
    // 查找ini Key
    void onFindiniKeyBtnClick();
    // 设置ini Value
    void onSetiniValueBtnClick();
    // 删除ini Value
    void onDeliniValueBtnClick();
    // 删除账号信息
    void onDelEmailBtnClick();
    // 查找HashKey
    void onFindHashKeyBtnClick();
    // 设置HashValue
    void onSetHashValueBtnClick();
    // 删除HashValue
    void onDelHashValueBtnClick();
    // 弹出菜单
    void onMenuRequest(const QPoint &pos);
    // 复制操作
    void onActionCopyKey();
    void onActionCopyValue();
    // 编辑ini值
    void onActionEditIniValue();
    // 编辑hash值
    void onActionEditHashValue();

    void setToolWidgetsEnabled(bool enable);

private:
    Ui::Widget *ui;
    QSettings *m_ini = nullptr;
    QHash<QString, QVariant> m_hash;
};
