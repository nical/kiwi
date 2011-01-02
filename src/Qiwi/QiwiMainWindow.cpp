#include "QiwiMainWindow.hpp"
#include "ui_QiwiMainWindow.h"
#include "NodeView.hpp"


QiwiMainWindow::QiwiMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QiwiMainWindow)
{
    ui->setupUi(this);
    NodeView* n1 = new NodeView();

    ui->graphicsView->setScene( &_scene );

    _scene.addItem( n1 );
}

QiwiMainWindow::~QiwiMainWindow()
{
    delete ui;
}
