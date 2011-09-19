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

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    PortTypeEnum portType() const { return _type; }
    unsigned int index() const { return _index; }
    virtual void updatePosition();
    bool connect( NodePortView* p);
    bool isCompatible( NodePortView* port );
    bool isCompatible( PortTypeEnum type );
    QList<NodeLinkView*>::Iterator firstLink() { return _links.begin(); }
    QList<NodeLinkView*>::Iterator EndLink() { return _links.end(); }

    void disconnect( NodeLinkView* link = 0 );

    ~NodePortView();

protected:
    void mouseMoveEvent( QGraphicsSceneMouseEvent * event );
    void mouseReleaseEvent ( QGraphicsSceneMouseEvent * event );

    void linkDisconnect( NodeLinkView* link = 0 );

    QPointF _pos;
    NodeView* _node;
    QList<NodeLinkView*> _links;
    PortTypeEnum _type;
    unsigned int _index;
    bool _dragging;
};

}//namespace

#endif // NODEPORTVIEW_HPP
