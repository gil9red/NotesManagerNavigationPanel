#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSettings>
#include <QDebug>
#include <QFile>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->treeNotes->model.appendToNotes(new NoteModelItem("Заметка 1"));
    ui->treeNotes->model.appendToNotes(new NoteModelItem("Заметка 2"));
    ui->treeNotes->model.appendToNotes(new FolderModelItem("Папка 1"));
    ui->treeNotes->model.appendToNotes(new FolderModelItem("Папка 2"));
    ui->treeNotes->model.appendToTrash(new NoteModelItem("Заметка 3"));
    ui->treeNotes->model.appendToTrash(new NoteModelItem("Заметка 4"));

    QSettings ini( qApp->applicationDirPath()+"/ini.ini", QSettings::IniFormat );
    //ui->splitter->restoreState( ini.value( ui->splitter->objectName() ).toByteArray() );
    restoreState( ini.value( "State" ).toByteArray() );
    restoreGeometry( ini.value( "Geometry" ).toByteArray() );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *)
{
    QSettings ini( qApp->applicationDirPath()+"/ini.ini", QSettings::IniFormat );
    //ini.setValue( ui->splitter->objectName(), ui->splitter->saveState() );
    ini.setValue( "State", saveState() );
    ini.setValue( "Geometry", saveGeometry() );
}
