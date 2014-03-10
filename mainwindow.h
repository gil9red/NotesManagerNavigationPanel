#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

#include "hierarchicalview.h"
#include "noteeditor.h"

class MainWindow: public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow * ui;    

public slots:
    void openItem( BaseModelItem * item );
    void closeItem( int index );

protected:
    void closeEvent(QCloseEvent *);
};

#endif // MAINWINDOW_H
