#include "TemporaryPortView.hpp"
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include "NodeLinkView.hpp"
#include <iostream>
#include <QPainter>

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
            double distance = (pos() - itm->pos()).manhattanLength();
            if( distance < closestDist ){
                std::cerr << distance <<"\n";
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
            NodePortView* out = _links.front()->outPort();

            toConnect->connect( out );
        }else{
            std::cerr << "this = output\n";
            NodePortView* in = _links.front()->inPort();
            if( !toConnect->connect( in ) ){
                std::cerr << "error: could not connect ports\n";
            }
        }
    }

    delete _links.front();

    scene()->removeItem( this );

}

void TemporaryPortView::updatePosition()
{
    // do nothing
}


void TemporaryPortView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    _closestPort = 0;
    _closestDistance = 100;
    foreach( QGraphicsItem* qItm, collidingItems() ){
        NodePortView* itm = dynamic_cast<NodePortView*>(qItm);
        if( itm && ((itm->portType() & INPUT_OUTPUT_MASK)
            == (this->portType() & INPUT_OUTPUT_MASK)) ){
            double distance = (pos() - itm->pos()).manhattanLength();
            if( distance < _closestDistance ){
                _closestDistance = distance;
                _closestPort = itm;
            }
        }
    }
    if(_closestPort)
    {
        painter->setPen( QPen(QColor(50,50,255, 100),3) );
        painter->drawLine( QPointF(0,0), _closestPort->pos() - pos() );
    }
    //painter->setBrush( Qt::transparent );
    //painter->drawRect( boundingRect() );
}


QRectF TemporaryPortView::boundingRect() const
{
    return QRectF( -30, -30, 60, 60 );
}

}//namespace
