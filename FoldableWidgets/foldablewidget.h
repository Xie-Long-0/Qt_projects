/**
 * This FoldableWidget is consisted of two parts:
 * +---------------------------+
 * |         ToolWidget        |
 * +---------------------------+
 * |        ContentWidget      |
 * |          (Hidable)        |
 * +---------------------------+
 *
 * The ToolWidget includes these components:
 * +------------------------+-----------------------+-----------------------+---------------------------+------------------------+
 * | QCheckBox(id:checkbox) | QLabel(id:icon_label) | QLabel(id:text_label) | QLabel(id:alt_icon_label) | QPushButton(id:button) |
 * +------------------------+-----------------------+-----------------------+---------------------------+------------------------+
 *
 * The ContentWidget is empty.
 *
 * To add widgets to the ContentWidget, see this example:
 *
 *   auto contentWidget = this->contentWidget();
 *   auto contentLayout = this->contentBoxLayout();
 *   auto item = new QWidget(contentWidget);
 *   contentLayout->addWidget(item);
 *
 * Or use this function to do the things above:
 *   this->addWidget(item);
*/

#pragma once

#include <QWidget>
#include "ui_foldablewidget.h"

class FoldableWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FoldableWidget(QWidget *parent = nullptr);
    virtual ~FoldableWidget();

    inline void setIcon(const QPixmap &icon);
    inline void setAltIcon(const QPixmap &icon);
    inline void setButtonText(const QString &text);
    inline void setText(const QString &text);
    inline void setTextAlign(Qt::Alignment align);
    inline void setTextIndent(int indent);
    inline void setToolWidgetStyleSheet(const QString &styleSheet);
    inline void setContentWidgetStyleSheet(const QString &styleSheet);

    QWidget* contentWidget() const { return ui.contentWidget; }
    QVBoxLayout* contentBoxLayout() const { return ui.content_vLayout; }
    inline void addWidget(QWidget *item, int stretch = 0, Qt::Alignment align = Qt::Alignment());

public slots:
    inline void setFolded(bool folded);
    inline void fold() { setFolded(true); }
    inline void unfold() { setFolded(false); }
    inline void setIconVisible(bool visible);
    inline void setButtonVisible(bool visible);
    inline void setAltIconVisible(bool visible);
    inline void setCheckBoxVisible(bool visible);
    inline void setTextVisible(bool visible);

protected slots:
    virtual void onButtonClicked();
    virtual void onCheckBoxToggled(bool checked);

signals:
    void foldChanged(bool folded);

protected:
    void paintEvent(QPaintEvent *) override;
    bool eventFilter(QObject *obj, QEvent *e) override;

    Ui::FoldableWidget ui;
    bool m_isFolded = false;
};

inline void FoldableWidget::setIcon(const QPixmap &icon)
{
    ui.icon_label->show();
    ui.icon_label->setPixmap(icon);
}

inline void FoldableWidget::setAltIcon(const QPixmap &icon)
{
    ui.alt_icon_label->show();
    ui.alt_icon_label->setPixmap(icon);
}

inline void FoldableWidget::setButtonText(const QString &text)
{
    ui.button->show();
    ui.button->setText(text);
}

inline void FoldableWidget::setText(const QString &text)
{
    ui.text_label->show();
    ui.text_label->setText(text);
}

inline void FoldableWidget::setTextAlign(Qt::Alignment align)
{
    ui.text_label->setAlignment(align);
}

inline void FoldableWidget::setTextIndent(int indent)
{
    ui.text_label->setIndent(indent);
}

inline void FoldableWidget::setToolWidgetStyleSheet(const QString &styleSheet)
{
    ui.toolWidget->setStyleSheet(styleSheet);
}

inline void FoldableWidget::setContentWidgetStyleSheet(const QString &styleSheet)
{
    ui.contentWidget->setStyleSheet(styleSheet);
}

inline void FoldableWidget::addWidget(QWidget *item, int stretch, Qt::Alignment align)
{
    item->setParent(ui.contentWidget);
    ui.content_vLayout->addWidget(item, stretch, align);
}

inline void FoldableWidget::setFolded(bool fold)
{
    ui.scrollArea->setVisible(!fold);
    if (fold != m_isFolded)
        emit foldChanged(fold);
    m_isFolded = fold;
}

inline void FoldableWidget::setIconVisible(bool visible)
{
    ui.icon_label->setVisible(visible);
}

inline void FoldableWidget::setButtonVisible(bool visible)
{
    ui.button->setVisible(visible);
}

inline void FoldableWidget::setAltIconVisible(bool visible)
{
    ui.alt_icon_label->setVisible(visible);
}

inline void FoldableWidget::setCheckBoxVisible(bool visible)
{
    ui.checkbox->setVisible(visible);
}

inline void FoldableWidget::setTextVisible(bool visible)
{
    ui.text_label->setVisible(visible);
}
