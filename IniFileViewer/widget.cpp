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
    connect(ui->findiniKeyBtn, &QPushButton::clicked, this, &Widget::onFindiniKeyBtnClick);
    connect(ui->setiniValueBtn, &QPushButton::clicked, this, &Widget::onSetiniValueBtnClick);
    connect(ui->deliniValueBtn, &QPushButton::clicked, this, &Widget::onDeliniValueBtnClick);
    connect(ui->delEmailBtn, &QPushButton::clicked, this, &Widget::onDelEmailBtnClick);
    connect(ui->findHashKeyBtn, &QPushButton::clicked, this, &Widget::onFindHashKeyBtnClick);
    connect(ui->setHashValueBtn, &QPushButton::clicked, this, &Widget::onSetHashValueBtnClick);
    connect(ui->delHashValueBtn, &QPushButton::clicked, this, &Widget::onDelHashValueBtnClick);
    ui->treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->treeWidget, &QWidget::customContextMenuRequested, this, &Widget::onMenuRequest);
    ui->hashFrame->hide();
    setToolWidgetsEnabled(false);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::onOpenFileBtnClick()
{
    if (!ui->fileLineEdit->text().isEmpty())
    {
        auto fileName = ui->fileLineEdit->text();
        QFile file(fileName);
        if (!file.exists() || !file.open(QIODevice::ReadWrite))
        {
            QMessageBox::critical(this, tr("错误"), tr("文件[%1]不存在或打开失败！").arg(fileName));
            return;
        }
        file.close();
        if (fileName.right(4) != ".ini")
        {
            QMessageBox::critical(this, tr("错误"), tr("只支持打开.ini文件。"));
            return;
        }
        onCloseFileBtnClick();

        // 加载ini文件
        m_ini = new QSettings(fileName, QSettings::IniFormat, this);
        auto ini_keys = m_ini->allKeys();
        for (auto &ini_key : ini_keys)
        {
            // 读取ini文件设置的值
            auto ini_value = m_ini->value(ini_key);
            QTreeWidgetItem *rootNode = new QTreeWidgetItem(ui->treeWidget);
            rootNode->setData(0, 0, ini_key);
            rootNode->setData(1, 0, ini_value.typeName());

            // 判断值的存储类型
#if QT_VERSION < QT_VERSION_CHECK(6,0,0)
            switch (ini_value.type())
#else
            switch (ini_value.typeId())
#endif
            {
            case QMetaType::QVariantHash:
            {
                m_hash = ini_value.toHash();
                rootNode->setData(2, 0, m_hash);

                // 列出QHash容器的键值对
                auto hash_keys = m_hash.keys();
                for (auto &hkey : hash_keys)
                {
                    auto hvalue = m_hash.value(hkey);
                    QTreeWidgetItem *node = new QTreeWidgetItem(rootNode);
                    node->setData(0, 0, hkey);
                    node->setData(1, 0, hvalue.typeName());
                    node->setData(2, 0, hvalue);
                    // 找到存储Qt账号的键
                    if (hkey == "origemail")
                    {
                        ui->emailEdit->setText(hvalue.toString());
                    }
                }
                if (ini_key == "Variables")
                {
                    ui->hashFrame->show();
                }
                break;
            }

            case QMetaType::QVariantMap:
            {
                auto map = ini_value.toMap();
                rootNode->setData(2, 0, map);

                // 列出QMap容器的值
                auto map_keys = map.keys();
                for (auto &mkey : map_keys)
                {
                    auto mvalue = map.value(mkey);
                    QTreeWidgetItem *node = new QTreeWidgetItem(rootNode);
                    node->setData(0, 0, mkey);
                    node->setData(1, 0, mvalue.typeName());
                    node->setData(2, 0, mvalue);
                }
                break;
            }

            case QMetaType::QStringList:
            {
                auto str_list = ini_value.toStringList();
                rootNode->setData(2, 0, str_list);

                for (qsizetype i = 0; i < str_list.size(); i++)
                {
                    QTreeWidgetItem *node = new QTreeWidgetItem(rootNode, {QString::number(i), "QString", str_list[i]});
                    Q_UNUSED(node)
                }
                break;
            }

            default:
            {
                rootNode->setData(2, 0, ini_value);
                break;
            }
            } // !switch
        } // !for
        setToolWidgetsEnabled(true);
    }
    else
    {
        QMessageBox::warning(this, tr("错误"), tr("请输入文件路径！"));
    }
}

void Widget::onCloseFileBtnClick()
{
    ui->treeWidget->clear();
    if (m_ini)
        m_ini->deleteLater();
    m_ini = nullptr;
    m_hash.clear();

    setToolWidgetsEnabled(false);
    ui->hashFrame->hide();
}

void Widget::onFileDialogBtnClick()
{
    QString file_name = QFileDialog::getOpenFileName(this, tr("选择ini文件"), QString(), "INI Files(*.ini)");
    if (!file_name.isEmpty())
    {
        ui->fileLineEdit->setText(file_name);
        onOpenFileBtnClick();
    }
}

void Widget::onFindiniKeyBtnClick()
{
    if (m_ini)
    {
        auto key = ui->iniKeyLineEdit->text();
        if (key.isEmpty())
        {
            QMessageBox::warning(this, tr("警告"), tr("请输入Key值！"));
            return;
        }

        if (m_ini->contains(key))
        {
            ui->iniValueLineEdit->setText(m_ini->value(key).toString());
            ui->iniValueLineEdit->setFocus();
            return;
        }
        QMessageBox::warning(this, tr("警告"), tr("未找到%1").arg(key));
    }
}

void Widget::onSetiniValueBtnClick()
{
    if (m_ini)
    {
        auto key = ui->iniKeyLineEdit->text();
        if (key.isEmpty())
        {
            QMessageBox::warning(this, tr("警告"), tr("请输入Key值！"));
            return;
        }

        m_ini->setValue(key, ui->iniValueLineEdit->text());
        QMessageBox::information(this, tr("提示"), tr("%1设置成功。").arg(key));
        onOpenFileBtnClick();
    }
}

void Widget::onDeliniValueBtnClick()
{
    if (m_ini)
    {
        auto key = ui->iniKeyLineEdit->text();
        if (key.isEmpty())
        {
            QMessageBox::warning(this, tr("警告"), tr("请输入Key值！"));
            return;
        }

        if (m_ini->contains(key))
        {
            m_ini->remove(key);
            QMessageBox::information(this, tr("提示"), tr("%1删除成功。").arg(key));
            onOpenFileBtnClick();
            return;
        }
        QMessageBox::warning(this, tr("警告"), tr("未找到%1").arg(key));
    }
}

void Widget::onDelEmailBtnClick()
{
    if (m_ini && !m_hash.isEmpty())
    {
        if (m_hash.contains("origemail") || m_hash.contains("origuuid"))
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
        QMessageBox::warning(this, tr("警告"), tr("未找到账号信息。"));
    }
}

void Widget::onFindHashKeyBtnClick()
{
    if (!m_hash.isEmpty())
    {
        auto key = ui->hashKeyLineEdit->text();
        if (key.isEmpty())
        {
            QMessageBox::warning(this, tr("警告"), tr("请输入Key值！"));
            return;
        }

        if (m_hash.contains(key))
        {
            ui->hashValueLineEdit->setText(m_hash.value(key).toString());
            ui->hashValueLineEdit->setFocus();
            return;
        }
        QMessageBox::warning(this, tr("警告"), tr("未找到%1").arg(key));
        return;
    }
    QMessageBox::warning(this, tr("警告"), tr("QHash容器无效！"));
}

void Widget::onSetHashValueBtnClick()
{
    if (!m_hash.isEmpty())
    {
        auto key = ui->hashKeyLineEdit->text();
        if (key.isEmpty())
        {
            QMessageBox::warning(this, tr("警告"), tr("请输入Key值！"));
            return;
        }

        if (m_hash.insert(key, ui->hashValueLineEdit->text())->isValid())
        {
            // 保存到ini文件
            m_ini->setValue("Variables", m_hash);
            QMessageBox::information(this, tr("提示"), tr("%1设置成功。").arg(key));
            onOpenFileBtnClick();
        }
        else
        {
            QMessageBox::warning(this, tr("错误"), tr("%1设置失败！").arg(key));
        }
        return;
    }
    QMessageBox::warning(this, tr("警告"), tr("QHash容器无效！"));
}

void Widget::onDelHashValueBtnClick()
{
    if (!m_hash.isEmpty())
    {
        auto key = ui->hashKeyLineEdit->text();
        if (key.isEmpty())
        {
            QMessageBox::warning(this, tr("警告"), tr("请输入Key值！"));
            return;
        }

        if (m_hash.contains(key))
        {
            m_hash.remove(key);
            // 保存到ini文件
            m_ini->setValue("Variables", m_hash);
            QMessageBox::information(this, tr("提示"), tr("%1已删除。").arg(key));
            onOpenFileBtnClick();
        }
        else
        {
            QMessageBox::warning(this, tr("警告"), tr("未找到%1").arg(key));
        }
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
    connect(action1, &QAction::triggered, this, &Widget::onActionCopyKey);
    menu.addAction(action1);

    if (!item->data(2, 0).isNull())
    {
        QAction *action2 = new QAction(tr("复制Value"), ui->treeWidget);
        connect(action2, &QAction::triggered, this, &Widget::onActionCopyValue);
        menu.addAction(action2);
    }

    // ini变量，位于顶级节点，且没有子节点
    if (item->parent() == nullptr && item->childCount() == 0)
    {
        QAction *action3 = new QAction(tr("编辑..."), ui->treeWidget);
        connect(action3, &QAction::triggered, this, &Widget::onActionEditIniValue);
        menu.addAction(action3);
    }
    // hash变量，父节点为Variables值
    else if (!m_hash.isEmpty() && item->parent() && item->parent()->data(0, 0).toString() == "Variables")
    {
        QAction *action4 = new QAction(tr("编辑..."), ui->treeWidget);
        connect(action4, &QAction::triggered, this, &Widget::onActionEditHashValue);
        menu.addAction(action4);
    }

    menu.exec(QCursor::pos());
}

void Widget::onActionCopyKey()
{
    auto item = ui->treeWidget->currentItem();
    if (item == nullptr)
        return;

    // 复制到系统剪贴板
    QApplication::clipboard()->setText(item->text(0));
}

void Widget::onActionCopyValue()
{
    auto item = ui->treeWidget->currentItem();
    if (item == nullptr)
        return;

    // 复制到系统剪贴板
    QApplication::clipboard()->setText(item->text(2));
}

void Widget::onActionEditIniValue()
{
    auto item = ui->treeWidget->currentItem();
    if (item == nullptr)
        return;

    setToolWidgetsEnabled(true);
    ui->iniKeyLineEdit->setText(item->data(0, 0).toString());
    ui->iniValueLineEdit->setText(item->data(2, 0).toString());
}

void Widget::onActionEditHashValue()
{
    auto item = ui->treeWidget->currentItem();
    if (item == nullptr)
        return;

    setToolWidgetsEnabled(true);
    ui->hashKeyLineEdit->setText(item->data(0, 0).toString());
    ui->hashValueLineEdit->setText(item->data(2, 0).toString());
}

void Widget::setToolWidgetsEnabled(bool enable)
{
    ui->iniKeyLineEdit->setEnabled(enable);
    ui->iniValueLineEdit->setEnabled(enable);
    ui->findiniKeyBtn->setEnabled(enable);
    ui->setiniValueBtn->setEnabled(enable);
    ui->deliniValueBtn->setEnabled(enable);
}
