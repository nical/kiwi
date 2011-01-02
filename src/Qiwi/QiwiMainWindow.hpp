#ifndef QIWIMAINWINDOW_HPP
#define QIWIMAINWINDOW_HPP

#include <QMainWindow>
#include <QGraphicsScene>

namespace Ui {
    class QiwiMainWindow;
}

class QiwiMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit QiwiMainWindow(QWidget *parent = 0);
    ~QiwiMainWindow();

private:
    Ui::QiwiMainWindow *ui;
    QGraphicsScene _scene;
};

#endif // QIWIMAINWINDOW_HPP
