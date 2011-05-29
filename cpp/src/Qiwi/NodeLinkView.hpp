#ifndef NODELINKVIEW_HPP
#define NODELINKVIEW_HPP

#include <QGraphicsItem>
#include "Commons.hpp"
#include "NodePortView.hpp"

namespace Qiwi{

class NodeLinkView : public QGraphicsItem
{
public:
    NodeLinkView( PortTypeEnum type, NodePortView* out, NodePortView* in );
    ~NodeLinkView();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    PortTypeEnum portType() const { return _type; }
    void updatePosition( PortTypeEnum type, const QPointF& pos );
    NodePortView* inPort() const { return _inPort; }
    NodePortView* outPort() const { return _outPort; }
    void setPorts( NodePortView* in, NodePortView* out);

private:
    PortTypeEnum _type;
    NodePortView* _outPort;
    NodePortView* _inPort;
};


}//namespace

#endif // NODELINKVIEW_HPP
