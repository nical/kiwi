#ifndef QIWI_NODEVIEW_HPP
#define QIWI_NODEVIEW_HPP

#include <QGraphicsItem>
#include <QRectF>
#include <QGraphicsDropShadowEffect>
#include <QVector>

#include "Commons.hpp"

namespace Qiwi{
class NodePortView;

class NodeView : public QGraphicsItem
{
public:
    // RWIO

    explicit NodeView( const QPointF& position
                     , const QString& name
                     , unsigned int nbReaderInputs = 0
                     , unsigned int nbReaderOutputs = 0
                     , unsigned int nbWriterInputs = 0
                     , unsigned int nbWriterOutputs = 0 );


    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    QPointF PortPosition( PortTypeEnum type, unsigned int index );
    void initPorts(  unsigned int nbReaderInputs = 0
                   , unsigned int nbReaderOutputs = 0
                   , unsigned int nbWriterInputs = 0
                   , unsigned int nbWriterOutputs = 0 );

    void addToScene( QGraphicsScene* scene );

    NodePortView* port(PortTypeEnum type, unsigned int index);

protected:
    void mouseMoveEvent( QGraphicsSceneMouseEvent * event );

    void initNode( const QPointF& position
                   , const QString& name
                   , unsigned int nbReaderInputs = 0
                   , unsigned int nbReaderOutputs = 0
                   , unsigned int nbWriterInputs = 0
                   , unsigned int nbWriterOutputs = 0 );

    QRectF _rect;
    QString _name;
    QGraphicsDropShadowEffect _dropShadow;
    QVector<NodePortView*> _readerInputPorts;
    QVector<NodePortView*> _readerOutputPorts;
    QVector<NodePortView*> _writerInputPorts;
    QVector<NodePortView*> _writerOutputPorts;

};

}//namespace

#endif // NODEVIEW_HPP
