#include "NodeLinkView.hpp"
#include <QPainter>
#include <QGraphicsScene>

namespace Qiwi{


NodeLinkView::NodeLinkView(PortTypeEnum type, NodePortView* p1, NodePortView* p2)
{
    if(!p1){std::cerr << "NodeLinkView::constructor warning p1 = nil ptr\n";}
    if(!p2){std::cerr << "NodeLinkView::constructor warning p2 = nil ptr\n";}
    _type = type;
    if( p1->portType() & INPUT ){
        _inPort = p1;
        _outPort = p2;
    }else{
        _inPort = p2;
        _outPort = p1;
    }

}



void NodeLinkView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPainterPath path( _outPort->pos() );
    path.cubicTo( (_inPort->pos().x()+_outPort->pos().x() )/2.0, _outPort->pos().y()
                 ,(_inPort->pos().x()+_outPort->pos().x() )/2.0, _inPort->pos().y()
                 , _inPort->pos().x(), _inPort->pos().y()  );
    painter->setPen( QPen(Qt::blue, 3) );
    painter->drawPath( path );

}

QRectF NodeLinkView::boundingRect() const
{
    return QRectF( _outPort->pos(), _inPort->pos());
}

void NodeLinkView::updatePosition( PortTypeEnum type, const QPointF& position )
{
    if(type & Qiwi::OUTPUT){
        setPos( position );
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
