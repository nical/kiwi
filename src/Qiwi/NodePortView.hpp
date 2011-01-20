#ifndef NODEPORTVIEW_HPP
#define NODEPORTVIEW_HPP

#include <QGraphicsItem>
#include <QPointF>

#include "Commons.hpp"

namespace Qiwi{
class NodeView;
class NodeLinkView;

class NodePortView : public QGraphicsItem
{
friend class NodeLinkView;
public:
    NodePortView( NodeView* node, PortTypeEnum type, unsigned int index );
    void disconnect( NodeLinkView* link = 0 );

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    PortTypeEnum portType() const { return _type; }
    unsigned int index() const { return _index; }
    virtual void updatePosition();
    bool connect( NodePortView* p );
    bool isCompatible( PortTypeEnum pType ) const;
    bool isConnected() const;


protected:
    NodePortView( PortTypeEnum type ){ _type = type; }
    void mousePressEvent( QGraphicsSceneMouseEvent * event );
    virtual void dragMoveEvent( QGraphicsSceneDragDropEvent * event );

    unsigned char _alpha;
    QPointF _pos;
    NodeView* _node;
    //NodeLinkView* _link;
    QList<NodeLinkView*> _links;
    PortTypeEnum _type;
    unsigned int _index;
};

}//namespace

#endif // NODEPORTVIEW_HPP
