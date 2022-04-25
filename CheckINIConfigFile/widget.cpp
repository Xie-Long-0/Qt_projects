#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QTreeWidgetItem>
#include <QMenu>
#include <QClipboard>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->fileDialogBtn, &QPushButton::clicked, this, &Widget::onFileDialogBtnClick);
    connect(ui->openFileBtn, &QPushButton::clicked, this, &Widget::onOpenFileBtnClick);
    connect(ui->closeFileBtn, &QPushButton::clicked, this, &Widget::onCloseFileBtnClick);
    connect(ui->delEmailBtn, &QPushButton::clicked, this, &Widget::onDelEmailBtnClick);
    connect(ui->findKeyBtn, &QPushButton::clicked, this, &Widget::onFindKeyBtnClick);
    connect(ui->setValueBtn, &QPushButton::clicked, this, &Widget::onSetValueBtnClick);
    connect(ui->delValueBtn, &QPushButton::clicked, this, &Widget::onDelValueBtnClick);
    hideToolWidgets();
    ui->treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->treeWidget, &QWidget::customContextMenuRequested, this, &Widget::onMenuRequest);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::onOpenFileBtnClick()
{
    if (!ui->fileLineEdit->text().isEmpty())
    {
        QFile file(ui->fileLineEdit->text());
        if (!file.exists() || !file.open(QIODevice::ReadWrite))
        {
            QMessageBox::critical(this, tr("错误"), tr("文件[%1]不存在或打开失败！").arg(ui->fileLineEdit->text()));
            return;
        }
        file.close();
        onCloseFileBtnClick();

        m_ini = new QSettings(ui->fileLineEdit->text(), QSettings::IniFormat, this);
        auto keys = m_ini->allKeys();
        for (auto &key : keys)
        {
            // 读取ini文件设置的值
            auto value = m_ini->value(key);
            QTreeWidgetItem *rootNode = new QTreeWidgetItem(ui->treeWidget, {key, QString("[%1]").arg(value.typeName())});

            // 判断值的存储类型
#if QT_VERSION < QT_VERSION_CHECK(6,0,0)
            switch (value.type())
#else
            switch (value.typeId())
#endif
            {
            case QMetaType::QVariantHash:
            {
                // 列出QHash容器的键值对
                m_hash = value.toHash();
                auto hashkeys = m_hash.keys();
                for (auto &hkey : hashkeys)
                {
                    auto hvalue = m_hash.value(hkey).toString();
                    QTreeWidgetItem *node = new QTreeWidgetItem(rootNode, {hkey, hvalue});
                    Q_UNUSED(node)
                    // 找到存储Qt账号的键
                    if (hkey == "origemail")
                    {
                        ui->emailEdit->setText(hvalue);
                    }
                }
                showToolWidgets();
                break;
            }

            case QMetaType::QVariantMap:
            {
                // 列出QMap容器的值
                auto map = value.toMap();
                auto mapkeys = map.keys();
                for (auto &mkey : mapkeys)
                {
                    auto mvalue = map.value(mkey);
                    QTreeWidgetItem *node = new QTreeWidgetItem(rootNode, {mkey, mvalue.toString()});
                    Q_UNUSED(node)
                }
                break;
            }

            case QMetaType::QStringList:
            {
                auto strlist = value.toStringList();
                for (qsizetype i = 0; i < strlist.size(); i++)
                {
                    QTreeWidgetItem *node = new QTreeWidgetItem(rootNode, {QString("[%1]").arg(i), strlist[i]});
                    Q_UNUSED(node)
                }
                break;
            }

            default:
            {
                QTreeWidgetItem *node = new QTreeWidgetItem(rootNode, { QString("[%1]").arg(value.typeName()), value.toString()});
                Q_UNUSED(node)
                break;
            }
            } // !switch
        } // !for
    }
}

void Widget::onCloseFileBtnClick()
{
    ui->treeWidget->clear();
    if (m_ini)
        m_ini->deleteLater();
    m_ini = nullptr;
    m_hash.clear();

    hideToolWidgets();
}

void Widget::onFileDialogBtnClick()
{
    QString file_name = QFileDialog::getOpenFileName(this, tr("选择ini文件"), QDir::homePath(), "INI Files(*.ini)");
    if (!file_name.isEmpty())
    {
        ui->fileLineEdit->setText(file_name);
        onOpenFileBtnClick();
    }
}

void Widget::onDelEmailBtnClick()
{
    if (!m_hash.isEmpty() && m_ini)
    {
        if (m_hash.contains("origemail"))
        {
            // 删除标识符和邮箱
            m_hash.remove("origemail");
            m_hash.remove("origuuid");
            // 保存到ini文件
            m_ini->setValue("Variables", m_hash);

            QMessageBox::information(this, tr("提示"), tr("账号信息删除成功。"));

            // 删除qtaccount.ini文件
            QFile file(QDir::homePath() + "/AppData/Roaming/Qt/qtaccount.ini");
            if (!file.exists() || file.remove())
            {
                QMessageBox::information(this, tr("提示"), tr("qtaccount.ini文件已删除。"));
            }
            else
            {
                QMessageBox::warning(this, tr("警告"), tr("qtaccount.ini文件删除失败！"));
            }

            onOpenFileBtnClick();
            return;
        }
    }
    QMessageBox::warning(this, tr("警告"), tr("文件内容不匹配！"));
}

void Widget::onFindKeyBtnClick()
{
    if (!m_hash.isEmpty())
    {
        if (ui->keyLineEdit->text().isEmpty())
        {
            QMessageBox::warning(this, tr("警告"), tr("请输入Key值！"));
            return;
        }

        auto value = m_hash.value(ui->keyLineEdit->text()).toString();
        if (value.isEmpty())
        {
            QMessageBox::warning(this, tr("警告"), tr("找不到Key对应的值！"));
            return;
        }
        ui->valueLineEdit->setText(value);
        ui->valueLineEdit->setFocus();
        return;
    }
    QMessageBox::warning(this, tr("警告"), tr("QHash容器无效！"));
}

void Widget::onSetValueBtnClick()
{
    if (!m_hash.isEmpty())
    {
        if (ui->keyLineEdit->text().isEmpty())
        {
            QMessageBox::warning(this, tr("警告"), tr("请输入Key值！"));
            return;
        }

        if (m_hash.insert(ui->keyLineEdit->text(), ui->valueLineEdit->text())->isValid())
        {
            QMessageBox::information(this, tr("提示"), tr("设置成功。"));
            // 保存到ini文件
            m_ini->setValue("Variables", m_hash);
        }
        else
        {
            QMessageBox::warning(this, tr("错误"), tr("设置失败！"));
        }
        return;
    }
    QMessageBox::warning(this, tr("警告"), tr("QHash容器无效！"));
}

void Widget::onDelValueBtnClick()
{
    if (!m_hash.isEmpty())
    {
        if (ui->keyLineEdit->text().isEmpty())
        {
            QMessageBox::warning(this, tr("警告"), tr("请输入Key值！"));
            return;
        }

        m_hash.remove(ui->keyLineEdit->text());
        QMessageBox::information(this, tr("提示"), tr("%1键值对已删除。").arg(ui->keyLineEdit->text()));
        // 保存到ini文件
        m_ini->setValue("Variables", m_hash);
        return;
    }
    QMessageBox::warning(this, tr("警告"), tr("QHash容器无效！"));
}

void Widget::onMenuRequest(const QPoint &)
{
    auto item = ui->treeWidget->currentItem();
    if (item == nullptr)
        return;

    QMenu menu(ui->treeWidget);
    QAction *action1 = new QAction(tr("复制Key"), ui->treeWidget);
    QAction *action2 = new QAction(tr("复制Value"), ui->treeWidget);
    connect(action1, &QAction::triggered, this, &Widget::onActionCopyKey);
    connect(action2, &QAction::triggered, this, &Widget::onActionCopyValue);
    menu.addAction(action1);
    menu.addAction(action2);
    menu.exec(QCursor::pos());
}

void Widget::onActionCopyValue()
{
    auto item = ui->treeWidget->currentItem();
    if (item == nullptr)
        return;

    // 复制到系统剪贴板
    QApplication::clipboard()->setText(item->text(1));
}

void Widget::onActionCopyKey()
{
    auto item = ui->treeWidget->currentItem();
    if (item == nullptr)
        return;

    // 复制到系统剪贴板
    QApplication::clipboard()->setText(item->text(0));
}

void Widget::showToolWidgets()
{
    ui->emailLabel->show();
    ui->emailEdit->show();
    ui->delEmailBtn->show();

    ui->keyLabel->show();
    ui->valueLabel->show();
    ui->keyLineEdit->show();
    ui->valueLineEdit->show();
    ui->findKeyBtn->show();
    ui->setValueBtn->show();
    ui->delValueBtn->show();
}

void Widget::hideToolWidgets()
{
    ui->emailLabel->hide();
    ui->emailEdit->hide();
    ui->delEmailBtn->hide();

    ui->keyLabel->hide();
    ui->valueLabel->hide();
    ui->keyLineEdit->hide();
    ui->valueLineEdit->hide();
    ui->findKeyBtn->hide();
    ui->setValueBtn->hide();
    ui->delValueBtn->hide();
}
