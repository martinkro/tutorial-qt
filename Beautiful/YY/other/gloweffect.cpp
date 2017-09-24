#include "gloweffect.h"
#include <qpainter.h>
#include <QPixmap>
#include <QDebug>

GlowEffect::GlowEffect(QObject *parent) :
    QGraphicsEffect(parent), radius(0), color(255, 255, 255, 255)
{
}

void GlowEffect::setRadius(int radius)
{
    this->radius = radius;
    updateBoundingRect();
    update();
}

void GlowEffect::setGlowColor(const QColor &color)
{
    this->color = color;
    update();
}

QRectF GlowEffect::boundingRectFor(const QRectF &sourceRect) const
{
    QRectF tmp(sourceRect);
    tmp.setBottomRight(tmp.bottomRight() + QPointF(radius * 2, radius * 2));
    return tmp;
}

void GlowEffect::draw(QPainter *painter)
{
    if (!radius)
    {
        drawSource(painter);
        return;
    }
    QPixmap source = sourcePixmap();
    QImage sourceBlured(source.size() + QSize(radius * 2, radius * 2), QImage::Format_ARGB32_Premultiplied);
    sourceBlured.fill(0);
    QPainter tmpPainter(&sourceBlured);
    tmpPainter.drawPixmap(radius, radius, source);
    tmpPainter.setCompositionMode(QPainter::CompositionMode_SourceIn);
    tmpPainter.fillRect(sourceBlured.rect(), color);
    tmpPainter.end();
    qt_blurImage(sourceBlured, radius, true);
    painter->drawImage(0, 0, sourceBlured);
    painter->drawImage(0, 0, sourceBlured);
    painter->drawPixmap(radius, radius, source);
}

void GlowEffect::sourceChanged(ChangeFlags flags)
{
    updateBoundingRect();
    update();
}
