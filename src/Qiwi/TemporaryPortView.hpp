#ifndef TEMPORARYPORTVIEW_HPP
#define TEMPORARYPORTVIEW_HPP

#include "NodePortView.hpp"

namespace Qiwi{

class TemporaryPortView : public NodePortView
{
public:
    TemporaryPortView( PortTypeEnum type, const QPointF& position );
    void updatePosition();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
protected:
    void mouseReleaseEvent( QGraphicsSceneMouseEvent* event );

    double _closestDistance;
    NodePortView* _closestPort;
};

}//namespace

#endif // TEMPORARYPORTVIEW_HPP
