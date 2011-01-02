#ifndef QIWI_NODEVIEW_HPP
#define QIWI_NODEVIEW_HPP

#include <QGraphicsItem>
#include <QRectF>
#include <QGraphicsDropShadowEffect>

class NodeView : public QGraphicsItem
{
public:
    explicit NodeView();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

protected:
    QRectF _rect;
    QString _name;
    QGraphicsDropShadowEffect _dropShadow;
};

#endif // NODEVIEW_HPP
