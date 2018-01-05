#include "MenuItem.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QIcon>
#include <QDebug>
#include <QBitmap>
#include <QCheckBox>

MenuItem::MenuItem(const QString& text, QWidget* parent):
    QFrame(parent)
{
    QLabel* iconLabel = new QLabel;
    iconLabel->setObjectName("icon");
    
    //QPixmap pixmap("icon_home_normal.png");
    ////pixmap.fill(Qt::transparent);
    //iconLabel->setPixmap(pixmap);
    ////iconLabel->setMask(pixmap.mask());
    //iconLabel->setWindowFlags(Qt::WindowStaysOnTopHint);
    //iconLabel->setAttribute(Qt::WA_TranslucentBackground);

    QImage image;
    image = QImage(17, 17, QImage::Format_ARGB32);
    image.fill(qRgb(0, 100, 100));
    //iconLabel->setPicture(image);
    
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

void MenuItem::paintEvent(QPaintEvent* event)
{
    //QWidget::paintEvent(event);
}