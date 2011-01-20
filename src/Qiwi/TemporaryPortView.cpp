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

    for(int i = 0; i < collisions.size(); ++i){
        std::cerr << "for(..)\n";
        NodePortView* itm = dynamic_cast<NodePortView*>( collisions.front() );
        if( (itm) ){
            std::cerr << printNodeType( _type ).toStdString() << "     "
                    << printNodeType( itm->portType() ).toStdString() << "\n";

            if((itm->portType() & INPUT_OUTPUT_MASK) == (this->portType() & INPUT_OUTPUT_MASK) ){
                if( _type & INPUT ){
                    std::cerr << "this = input\n";
                    NodePortView* out = _link->outPort();

                    itm->connect( out );
                }else{
                    std::cerr << "this = output\n";
                    NodePortView* in = _link->inPort();

                    itm->connect( in );
                }
                break;
            }

        }else{
            std::cerr << "x\n";
        }
        collisions.pop_front();
    }

    delete _link;

    scene()->removeItem( this );

}

void TemporaryPortView::updatePosition()
{
    // do nothing
}


}//namespace
