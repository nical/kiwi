#include "TemporaryPortView.hpp"
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include "NodeLinkView.hpp"
#include <iostream>

namespace Qiwi{


TemporaryPortView::TemporaryPortView( PortTypeEnum type, const QPointF& position )
    : NodePortView( type )
{
    setFlag( QGraphicsItem::ItemIsMovable );
    setPos( position );

}


void TemporaryPortView::mouseReleaseEvent( QGraphicsSceneMouseEvent* event )
{
    QGraphicsItem::mouseReleaseEvent( event );
    this->ungrabMouse();
    std::cout << "TemporaryPortView::mouseReleaseEvent\n";
    QList<QGraphicsItem*> collisions = scene()->collidingItems( this );

    NodePortView* toConnect = 0;
    double closestDist = 100;
    for(int i = 0; i < collisions.size(); ++i){
        std::cerr << "for(..)\n closest: " << closestDist << "\n";
        NodePortView* itm = dynamic_cast<NodePortView*>( collisions.front() );
        if( (itm) && ((itm->portType() & INPUT_OUTPUT_MASK)
            == (this->portType() & INPUT_OUTPUT_MASK)) ){
            std::cerr << printNodeType( _type ).toStdString() << "     "
                    << printNodeType( itm->portType() ).toStdString() << "\n";
            double distance = (pos() - itm->pos()).manhattanLength() ;
            if( distance < closestDist ){
                std::cerr << "plop\n";
                closestDist = distance;
                toConnect = itm;
            }
        }else{
            std::cerr << "x\n";
        }
        collisions.pop_front();
    }

    if( toConnect){
        if( _type & INPUT ){
            std::cerr << "this = input\n";
            NodePortView* out = _link->outPort();

            toConnect->connect( out );
        }else{
            std::cerr << "this = output\n";
            NodePortView* in = _link->inPort();
            if(_link) std::cerr << "nil ptr\n";
            if( !toConnect->connect( in ) ){
                std::cerr << "error: could not connect ports\n";
            }
        }
    }

    delete _link;

    scene()->removeItem( this );

}

void TemporaryPortView::updatePosition()
{
    // do nothing
}


}//namespace
