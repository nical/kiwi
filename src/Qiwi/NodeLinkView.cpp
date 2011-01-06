#include "NodeLinkView.hpp"
#include <QPainter>
#include <QGraphicsScene>

namespace Qiwi{


NodeLinkView::NodeLinkView(PortTypeEnum type, NodePortView* out, NodePortView* in)
{
    _type = type;
    _inPort = in;
    _outPort = out;
}



void NodeLinkView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPainterPath path( _outPort->pos() );
    path.cubicTo( (_inPort->pos().x()+_outPort->pos().x() )/2.0, _outPort->pos().y()
                 ,(_inPort->pos().x()+_outPort->pos().x() )/2.0, _inPort->pos().y()
                 , _inPort->pos().x(), _inPort->pos().y()  );
    painter->setPen( QPen(Qt::blue, 3) );
    painter->drawPath( path );

    //debug
   /*
    painter->setBrush( Qt::transparent );
    painter->setPen( Qt::red );
    painter->drawRect( boundingRect() );
    */

}

QRectF NodeLinkView::boundingRect() const
{
    return QRectF( _outPort->pos(), _inPort->pos());
}

void NodeLinkView::updatePosition( PortTypeEnum type, const QPointF& position )
{
    if(type & Qiwi::OUTPUT){
        setPos( position );
    }else{
        // nothing to do
        // check that the item is redrawn maybe ...
    }
}


void NodeLinkView::setPorts( NodePortView* in, NodePortView* out)
{
    _inPort = in;
    _outPort = out;
}

NodeLinkView::~NodeLinkView()
{
    _inPort->disconnect();
    _outPort->disconnect( this );
    if( scene() ) scene()->removeItem( this );
}

}//namespace
