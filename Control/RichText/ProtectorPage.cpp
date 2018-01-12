#include "ProtectorPage.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
ProtectorPage::ProtectorPage(QWidget* parent) :
    XBasePage(parent)
{
    QWidget* leftWidget = new QWidget;
    leftWidget->setObjectName("left");

    QWidget* rightWidget = new QWidget;
    rightWidget->setObjectName("right");

    QHBoxLayout* main = new QHBoxLayout;
    main->setContentsMargins(32, 68, 32, 25);
    main->setSpacing(18);
    main->addWidget(leftWidget);
    main->addWidget(rightWidget);
    setLayout(main);
}