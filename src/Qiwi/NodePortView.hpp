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
public:
    explicit NodePortView( NodeView* node, int type, unsigned int index );
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    int portType() const { return _type; }
    unsigned int index() const { return _type; }
    void updatePosition();
    bool connect( NodePortView* p);

protected:

    QPointF _pos;
    NodeView* _node;
    NodeLinkView* _link;
    int _type;
    unsigned int _index;
};

}//namespace

#endif // NODEPORTVIEW_HPP
