#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

#include "notesmodel/hierarchicalmodel.h"

class MainWindow: public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow * ui;
    HierarchicalModel model;

protected:
    void closeEvent(QCloseEvent *);

private slots:
    void on_tButtonAddFolder_clicked();
    void on_tButtonAddNote_clicked();
    void on_tButtonRemove_clicked();
    void updateStates();
    void on_treeView_clicked(const QModelIndex &index);
};

#endif // MAINWINDOW_H
