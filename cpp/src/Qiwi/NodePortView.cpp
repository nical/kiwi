#include "NodePortView.hpp"

#include "NodeView.hpp"
#include "NodeLinkView.hpp"
#include "TemporaryPortView.hpp"

#include <QPainter>
#include <QLinearGradient>
#include <QGraphicsScene>
#include <assert.h>
#include <iostream>

namespace Qiwi{

NodePortView::NodePortView( NodeView* node, PortTypeEnum type, unsigned int index )
{
    _dragging = false;
    _type = type;
    _index = index;
    _node = node;
    updatePosition();
    setFlags( /*QGraphicsItem::ItemIsSelectable|*/QGraphicsItem::ItemIsMovable );
}


void NodePortView::disconnect( NodeLinkView* link )
{
    if( link == 0 ){
        foreach(NodeLinkView* i, _links){
            std::cerr << "deleting all links..\n";
            delete i;
        }
        _links.clear();
    }else{
        std::cerr << "deleting a link..\n";
        QList<NodeLinkView*>::Iterator it = _links.begin();
        QList<NodeLinkView*>::Iterator stop = _links.end();
        for( ; it != stop; ++it){
            if( (*it) == link){
                std::cerr << "found it\n";
                delete (*it);
                _links.erase( it );
                return;
            }
        }
    }
}

void NodePortView::linkDisconnect( NodeLinkView* link )
{
    int test = _links.size();
    std::cerr << "NodePortView::linkDisconnect\n";
    if( link == 0 ){
        _links.clear();
        std::cerr << "erase all links\n";
    }else{
        for(QList<NodeLinkView*>::Iterator it = _links.begin()
            ; it != _links.end()
            ; ++it ){
                if( *it == link ){
                    std::cerr << "erase link\n";
                    _links.erase( it );
                }
        }
    }
    assert((test != _links.size()) || (test==0));
}


void NodePortView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    int lr = 0;
    int lg = 0;
    int lb = 0;
    int la = 255;

    int r = 255;
    int g = 255;
    int b = 255;
    int a = 255;



    NodePortView* grabber = dynamic_cast<NodePortView*>( scene()->mouseGrabberItem() );
    if( (grabber) && ( !isCompatible(grabber) ) ){
        a = 100;
        la = 100;
    }


    if( isSelected() ){
        lr = 50;
        lg = 100;
        lb = 255;
    }else{
        lr = 150;
        lg = 150;
        lb = 150;
    }
    painter->setPen( QPen( QColor(lr,lg,lb,la),2) );
    painter->setBrush( QColor(r,g,b,a) );
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
    }

    NodeLinkView* it;
    foreach( it, _links){
        it->updatePosition(_type , pos() );
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

    NodeLinkView* link = new NodeLinkView( _type & Qiwi::READER_WRITER_MASK, this, p );
    _links.append( link );
    p->_links.append(link );

    scene()->addItem( link );

}

void NodePortView::mouseMoveEvent( QGraphicsSceneMouseEvent * event )
{
    if( !_dragging ){
        _dragging = true;
        std::cerr << "NodePortView::enterMoveEvent\n";
    }
    QGraphicsItem::mouseMoveEvent( event );
}

void NodePortView::mouseReleaseEvent( QGraphicsSceneMouseEvent * event )
{
    std::cerr << "NodePortView::mouseReleaseEvent\n";
   _dragging = false;
   QGraphicsItem::mouseReleaseEvent( event );
   QList<QGraphicsItem*> collisions = scene()->collidingItems( this );
   QList<QGraphicsItem*>::Iterator it = collisions.begin();
   QList<QGraphicsItem*>::Iterator stop = collisions.end();
   float distance = 30.0;
   NodePortView* closestPort = 0;
   for( ;it != stop; ++it ){
       std::cerr << "for...\n";
       NodePortView* collidingPort = dynamic_cast<NodePortView*>(*it);
       if(collidingPort){
           float tempDistance = (collidingPort->pos() - pos()).manhattanLength();
           if( tempDistance < distance ){
               distance = tempDistance;
               closestPort = collidingPort;
           }
       }
   }



   if((closestPort) && (closestPort->isCompatible(this) ) ){
       connect( closestPort );
   }else{
       disconnect( 0 );
   }

   updatePosition();
}

/*
mouseMoveEvent( QGraphicsSceneMouseEvent * event )
{
}
*/

bool NodePortView::isCompatible( NodePortView* port )
{
    return isCompatible( port->portType() );
}

bool NodePortView::isCompatible( Qiwi::PortTypeEnum type )
{
    if( (type & READER_WRITER_MASK) != (_type & READER_WRITER_MASK) ) return false;
    if( (type & INPUT_OUTPUT_MASK) == (_type & INPUT_OUTPUT_MASK) ) return false;
    return true;
}

NodePortView::~NodePortView()
{
    std::cerr << "NodePortView::destructor\n";
    if( scene() ) scene()->removeItem( this );
}

}//namespace
