#include "LoginPage.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

LoginPage::LoginPage(QWidget* parent) :
    XBasePage(parent)
{
    QWidget* leftWidget = new QWidget;
    leftWidget->setObjectName("left");

    QWidget* rightWidget = new QWidget;
    rightWidget->setObjectName("right");

    QHBoxLayout* main = new QHBoxLayout;
    main->setContentsMargins(62, 98, 62, 45);
    main->setSpacing(26);
    main->addWidget(leftWidget);
    main->addWidget(rightWidget);
    setLayout(main);
}