#ifndef NODELINKVIEW_HPP
#define NODELINKVIEW_HPP

#include <QGraphicsItem>
#include "Commons.hpp"
#include "NodePortView.hpp"

namespace Qiwi{

class NodeLinkView : public QGraphicsItem
{
public:
    NodeLinkView(int type, NodePortView* out, NodePortView* in );

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    int portType() const { return _type; }
    void updatePosition( int type, const QPointF& pos );

private:
    int _type;
    NodePortView* _outPort;
    NodePortView* _inPort;
};


}//namespace

#endif // NODELINKVIEW_HPP
