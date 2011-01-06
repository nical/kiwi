#include "QiwiMainWindow.hpp"
#include "ui_QiwiMainWindow.h"
#include "NodeView.hpp"
#include "NodePortView.hpp"

using namespace Qiwi;


QiwiMainWindow::QiwiMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QiwiMainWindow)
{
    ui->setupUi(this);

    ui->graphicsView->setScene( &_scene );
    ui->graphicsView->setRenderHints( QPainter::Antialiasing );
    ui->graphicsView->setViewportUpdateMode( QGraphicsView::FullViewportUpdate );



    NodeView* n1 = new NodeView( QPointF(0,0), "node 1", 4, 3, 1, 0);
    n1->addToScene(&_scene);

    NodeView* n2 = new NodeView( QPointF(200,0), "node 2", 3, 4, 1, 0);
    n2->addToScene(&_scene);

    NodeView* n3 = new NodeView( QPointF(400,0), "node 3", 3, 4, 1, 0);
    n3->addToScene(&_scene);

    n1->port(READER_OUTPUT, 0)->connect( n2->port(READER_INPUT, 0) );
    n1->port(READER_OUTPUT, 0)->connect( n2->port(READER_INPUT, 1) );
}

QiwiMainWindow::~QiwiMainWindow()
{
    delete ui;
}
