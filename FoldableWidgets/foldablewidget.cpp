#include "foldablewidget.h"
#include <QStyleOption>
#include <QPainter>

FoldableWidget::FoldableWidget(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    ui.toolWidget->installEventFilter(this);
    connect(ui.button, &QPushButton::clicked, this, &FoldableWidget::onButtonClicked);
    connect(ui.checkbox, &QCheckBox::toggled, this, &FoldableWidget::onCheckBoxToggled);
}

FoldableWidget::~FoldableWidget()
{
}

void FoldableWidget::onButtonClicked()
{
    setFolded(!m_isFolded);
    if (m_isFolded)
    {
        ui.checkbox->setChecked(false);
        ui.button->setText(tr("Unfold"));
    }
    else
    {
        ui.checkbox->setChecked(true);
        ui.button->setText(tr("Fold"));
    }
}

void FoldableWidget::onCheckBoxToggled(bool checked)
{
    setFolded(!checked);
    if (m_isFolded)
        ui.button->setText(tr("Unfold"));
    else
        ui.button->setText(tr("Fold"));
}

void FoldableWidget::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

bool FoldableWidget::eventFilter(QObject *obj, QEvent *e)
{
    if (obj == ui.toolWidget)
    {
        if (e->type() == QEvent::MouseButtonRelease)
        {
            onButtonClicked();
            return true;
        }
        return false;
    }
    return QWidget::eventFilter(obj, e);
}
