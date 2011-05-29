#include "NodeView.hpp"
#include <QPainter>
#include <QLinearGradient>

#include "NodePortView.hpp"
#include <QGraphicsScene>

#include <iostream>

namespace Qiwi{

NodeView::NodeView( const QPointF& position
                , const QString& name
                , unsigned int nbReaderInputs
                , unsigned int nbReaderOutputs
                , unsigned int nbWriterInputs
                , unsigned int nbWriterOutputs )
{
    initNode(position, name, nbReaderInputs, nbReaderOutputs, nbWriterInputs, nbWriterOutputs);
}

void NodeView::initNode( const QPointF& position
                , const QString& name
                , unsigned int nbReaderInputs
                , unsigned int nbReaderOutputs
                , unsigned int nbWriterInputs
                , unsigned int nbWriterOutputs )
{
    setFlags(QGraphicsItem::ItemIsMovable /*|QGraphicsItem::ItemIsSelectable*/);
    setPos( position );
    _rect = QRectF( 0, 0, 100.0, 120.0 );
    _name = name;
    _dropShadow.setBlurRadius( 16 );
    _dropShadow.setXOffset( 0.0 );
    _dropShadow.setYOffset( 5.0 );

    setGraphicsEffect( &_dropShadow );

    initPorts(nbReaderInputs, nbReaderOutputs, nbWriterInputs, nbWriterOutputs);
}

void NodeView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QLinearGradient gradient( 0.0, 0.0, 0.0, _rect.bottom() );
    gradient.setColorAt( 1, Qt::gray );
    gradient.setColorAt( 0, Qt::white );
    painter->setBrush( gradient );
    painter->setPen( QPen( Qt::transparent ) );
    painter->drawRoundedRect( _rect, 10, 10 );
    painter->setPen( QPen( Qt::gray ) );
    painter->drawText( QRectF(30, 5, 95, 15), _name );
}

QRectF NodeView::boundingRect() const
{
    return _rect;
}


QPointF NodeView::PortPosition( PortTypeEnum type, unsigned int index)
{
    QPointF result( pos() );
    result += QPointF( _rect.left(), 40.0 + index * 15 );
    return result;
}

void NodeView::initPorts( unsigned int nbReaderInputs
                       , unsigned int nbReaderOutputs
                       , unsigned int nbWriterInputs
                       , unsigned int nbWriterOutputs )
{
    for( unsigned int i = 0; i < nbReaderInputs; ++i){
        _readerInputPorts.append( new NodePortView( this, READER_INPUT, i ) );
    }

    for( unsigned int i = 0; i < nbReaderOutputs; ++i){
        _readerOutputPorts.append( new NodePortView( this, READER_OUTPUT, i  ) );
    }

    for( unsigned int i = 0; i < nbWriterInputs; ++i){
        _writerInputPorts.append( new NodePortView( this, WRITER_INPUT, i  ) );
    }

    for( unsigned int i = 0; i < nbWriterOutputs; ++i){
        _writerOutputPorts.append( new NodePortView( this, WRITER_OUTPUT, i  ) );
    }
}

void NodeView::mouseMoveEvent( QGraphicsSceneMouseEvent* event )
{
    //std::cerr << "NodeView::mouseMoveEvent\n";
    // call the parent implementation to keep the drag behavior
    QGraphicsItem::mouseMoveEvent( event );

    //update each port's position
    for( unsigned int i = 0; i < _readerInputPorts.size(); ++i){
        _readerInputPorts[i]->updatePosition();
    }

    for( unsigned int i = 0; i < _readerOutputPorts.size(); ++i){
        _readerOutputPorts[i]->updatePosition();
    }

    for( unsigned int i = 0; i < _writerInputPorts.size(); ++i){
        _writerInputPorts[i]->updatePosition();
    }

    for( unsigned int i = 0; i < _writerOutputPorts.size(); ++i){
        _writerOutputPorts[i]->updatePosition();
    }
}

void NodeView::addToScene( QGraphicsScene* scene )
{
    scene->addItem(this);
    for( unsigned int i = 0; i < _readerInputPorts.size(); ++i){
        scene->addItem( _readerInputPorts[i] );
    }

    for( unsigned int i = 0; i < _readerOutputPorts.size(); ++i){
        scene->addItem( _readerOutputPorts[i] );
    }

    for( unsigned int i = 0; i < _writerInputPorts.size(); ++i){
        scene->addItem( _writerInputPorts[i] );
    }

    for( unsigned int i = 0; i < _writerOutputPorts.size(); ++i){
        scene->addItem( _writerOutputPorts[i] );
    }
}

NodePortView* NodeView::port(PortTypeEnum type, unsigned int index)
{
    switch(type){
    case READER_INPUT: return _readerInputPorts[index];
    case READER_OUTPUT: return _readerOutputPorts[index];
    case WRITER_INPUT: return _writerInputPorts[index];
    case WRITER_OUTPUT: return _writerOutputPorts[index];
    default: return 0;
    }
}

}//namespace
