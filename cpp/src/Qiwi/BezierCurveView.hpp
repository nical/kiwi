#ifndef BEZIERCURVEVIEW_HPP
#define BEZIERCURVEVIEW_HPP

#include <QGraphicsItem>


namespace Qiwi{

class BezierCurveView : public QGraphicsItem
{
public:
    BezierCurveView(const QPointF& startPosition, const QPointF& endPosition );
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

protected:
    QPointF _end;
};


}

#endif // BEZIERCURVEVIEW_HPP
