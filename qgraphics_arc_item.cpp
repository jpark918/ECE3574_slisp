#include "qgraphics_arc_item.hpp"

#include <cmath>

#include <QDebug>
#include <QPainter>

QGraphicsArcItem::QGraphicsArcItem(qreal x, qreal y, qreal width, qreal height,
    QGraphicsItem* parent) : QGraphicsEllipseItem(x, y, width, height, parent)
{
    // TODO: your code here ...

    //convert to degrees and multiply by 16
}
void QGraphicsArcItem::paint(QPainter* painter,
    const QStyleOptionGraphicsItem* option,
    QWidget* widget) {
    // TODO: your code here ...
    painter->drawArc(rect(), startAngle(), spanAngle());
    OPTION(option);
    WIDGET(widget);
}

void QGraphicsArcItem::OPTION(const QStyleOptionGraphicsItem* option) {
    (void)option;
}

void QGraphicsArcItem::WIDGET(QWidget* widget) {
    (void)widget;
}
//void QGraphicsArcItem::paint(QPainter* painter) {
//    painter->drawArc(rect(), startAngle(), spanAngle());
//}