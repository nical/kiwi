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
    std::cout << "TemporaryPortView::mouseReleaseEvent\n";
    QList<QGraphicsItem*> collisions = scene()->collidingItems( this );

    for(int i = 0; i < collisions.size(); ++i){
        std::cerr << "for(..)\n";
        NodePortView* itm = dynamic_cast<NodePortView*>( collisions.front() );
        if( (itm) ){
            std::cerr << printNodeType( _type ).toStdString() << "\n"
                    << printNodeType( itm->portType() ).toStdString() << "\n";

            if(itm->portType() == this->portType() ){
                if( _type & INPUT ){
                    std::cerr << "this = input\n";
                    NodePortView* out = _link->outPort();
                    out->setSelected(true);
                    connect( out );
                }else{
                    std::cerr << "this = output\n";
                    NodePortView* in = _link->inPort();
                    in->setSelected(true);
                    in->connect( this );
                }
                break;
            }

        }else{
            std::cerr << "x\n";
        }
        collisions.pop_front();
    }

    delete _link;
    this->ungrabMouse();
    scene()->removeItem( this );

}

void TemporaryPortView::updatePosition()
{
    // do nothing
}


}//namespace
