#ifndef TEMPORARYPORTVIEW_HPP
#define TEMPORARYPORTVIEW_HPP

#include "NodePortView.hpp"

namespace Qiwi{

class TemporaryPortView : public NodePortView
{
public:
    TemporaryPortView( PortTypeEnum type, const QPointF& position );
    void updatePosition();

protected:
    void mouseReleaseEvent( QGraphicsSceneMouseEvent* event );
};

}//namespace

#endif // TEMPORARYPORTVIEW_HPP
