#include "MenuItem.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QIcon>
#include <QDebug>

MenuItem::MenuItem(const QString& text, QWidget* parent):
    QFrame(parent)
{
    QLabel* iconLabel = new QLabel;
    iconLabel->setObjectName("icon");
    
    //QPixmap pixmap;
    //bool ret = pixmap.load("icon_about_normal.png");
    //if (!ret)
    //{
    //    qDebug() << "load icon fail";
    //}
    //iconLabel->setPixmap(pixmap);

    QLabel* textLabel = new QLabel(text);
    textLabel->setObjectName("text");

    QHBoxLayout* main = new QHBoxLayout;
    main->setContentsMargins(0, 0, 0, 0);
    main->setSpacing(0);
    main->addWidget(iconLabel,0,Qt::AlignVCenter);
    main->addWidget(textLabel, 0, Qt::AlignVCenter);
    setLayout(main);
}