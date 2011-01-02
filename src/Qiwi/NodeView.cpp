#include "NodeView.hpp"
#include <QPainter>
#include <QLinearGradient>


NodeView::NodeView()
{
    setFlags(QGraphicsItem::ItemIsMovable|QGraphicsItem::ItemIsSelectable);
    _rect = QRectF(0, 0, 100.0, 120.0);
    _name = QString("a Node");
    _dropShadow.setBlurRadius(16);
    _dropShadow.setXOffset( 0.0 );
    _dropShadow.setYOffset( 5.0 );

    setGraphicsEffect( &_dropShadow );
}

void NodeView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QLinearGradient gradient( 0.0, 0.0, 0.0, _rect.bottom() );
    gradient.setColorAt( 1, Qt::gray );
    gradient.setColorAt( 0, Qt::white );
    painter->setBrush( gradient );
    painter->drawRoundedRect(_rect, 10, 10);
    painter->drawText( QRectF(30, 5, 95, 15), _name );
}

QRectF NodeView::boundingRect() const
{
    return _rect;
}
