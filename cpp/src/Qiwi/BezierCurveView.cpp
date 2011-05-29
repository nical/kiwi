#include "BezierCurveView.hpp"
#include <QPainter>

namespace Qiwi{



BezierCurveView::BezierCurveView(const QPointF& startPosition, const QPointF& endPosition)
{
    _end = endPosition;
    setPos( startPosition);
}




void BezierCurveView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPainterPath path( pos() );
    path.cubicTo( (_end.x() + pos().x() )/2.0, pos().y()
                 ,(_end.x() + pos().x() )/2.0, _end.y()
                 , _end.x(), _end.y()  );
    painter->setPen( QPen(Qt::blue, 3) );
    painter->drawPath( path );

    //debug
    painter->setBrush( Qt::transparent );
    painter->setPen( Qt::red );
    painter->drawRect( boundingRect() );

}

QRectF BezierCurveView::boundingRect() const
{
    return QRectF( pos(), _end );
}


}
