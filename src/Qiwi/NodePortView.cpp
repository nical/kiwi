#include "NodePortView.hpp"

#include "NodeView.hpp"
#include "NodeLinkView.hpp"
#include "TemporaryPortView.hpp"

#include <QPainter>
#include <QLinearGradient>
#include <QGraphicsScene>

#include <iostream>

namespace Qiwi{

NodePortView::NodePortView( NodeView* node, PortTypeEnum type, unsigned int index )
{
    _link = 0;
    _type = type;
    _index = index;
    _node = node;
    updatePosition();
    setFlags( QGraphicsItem::ItemIsSelectable );
}

void NodePortView::disconnect( NodeLinkView* link )
{
    _link = 0;
}


void NodePortView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if( isSelected() ){
        painter->setPen( QPen(Qt::blue,2) );
    }else{
        painter->setPen( QPen(Qt::gray,2) );
    }
    painter->setBrush( Qt::white );
    painter->drawEllipse( -5, -5, 10, 10 );
}

QRectF NodePortView::boundingRect() const
{
    return QRectF( -5, -5, 20, 20 );
}

void NodePortView::updatePosition(){
    switch(_type){
        case Qiwi::READER_OUTPUT: {
                setPos(    _node->pos().x() + _node->boundingRect().right()
                   ,_node->pos().y() + _node->boundingRect().top() + 40 + 20*_index );
                break;
        }
        case Qiwi::READER_INPUT: {
                setPos(    _node->pos().x() + _node->boundingRect().left()
                   ,_node->pos().y() + _node->boundingRect().top() + 40 + 20*_index );
                break;
        }
        case Qiwi::WRITER_INPUT: {
                setPos(    _node->pos().x() + 35 + 20*_index
                   ,_node->pos().y() + _node->boundingRect().bottom() );
                break;
        }
        case Qiwi::WRITER_OUTPUT: {
                setPos(    _node->pos().x() + 35 + 20*_index
                   ,_node->pos().y() + _node->boundingRect().top() );
                break;
        }
           if( _link) _link->updatePosition(_type , pos() );
    }
}

bool NodePortView::connect( NodePortView* p)
{
    if(p == 0){
        // TODO disconnect;
        return true;
    }

    if( (_type & Qiwi::INPUT_OUTPUT_MASK) == (p->portType() & Qiwi::INPUT_OUTPUT_MASK) )
        return false; // input -> input or output -> output
    if( (_type & Qiwi::READER_WRITER_MASK) != (p->portType() & Qiwi::READER_WRITER_MASK) )
        return false; // reader -> writer or writer -> reader

    if(_link != 0){
        // disconnect
    }

    _link = new NodeLinkView( _type & Qiwi::READER_WRITER_MASK, this, p );
    p->_link = _link;
    scene()->addItem( _link );

}

void NodePortView::mousePressEvent( QGraphicsSceneMouseEvent * event )
{
    //TODO if ctrl not pressed...
    Qiwi::PortTypeEnum ntype;
    switch( _type )
    {
    case READER_INPUT: {ntype = READER_OUTPUT; break;}
    case READER_OUTPUT:{ntype = READER_INPUT; break;}
    case WRITER_INPUT: {ntype = WRITER_OUTPUT; break;}
    case WRITER_OUTPUT: {ntype = WRITER_INPUT; break;}
    }

    TemporaryPortView* tpv = new TemporaryPortView( ntype, pos() );
    scene()->addItem( tpv );
    tpv->grabMouse();
    connect( tpv );
}


}//namespace
