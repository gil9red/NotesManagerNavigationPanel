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

    model.appendToNotes( new NoteModelItem("Заметка 1") );
    model.appendToNotes(new NoteModelItem("Заметка 2") );
    model.appendToNotes(new FolderModelItem("Папка 1") );
    model.appendToNotes(new FolderModelItem("Папка 2") );
    model.appendToTrash(new NoteModelItem("Заметка 3"));
    model.appendToTrash(new NoteModelItem("Заметка 4"));

    ui->treeView->setModel( &model );

    QSettings ini( qApp->applicationDirPath()+"/ini.ini", QSettings::IniFormat );
    //ui->splitter->restoreState( ini.value( ui->splitter->objectName() ).toByteArray() );
    restoreState( ini.value( "State" ).toByteArray() );
    restoreGeometry( ini.value( "Geometry" ).toByteArray() );

    updateStates();
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

void MainWindow::on_tButtonAddFolder_clicked()
{
    const QModelIndex & index = ui->treeView->currentIndex();
    model.itemFromIndex( index )->appendRow( new FolderModelItem( "Новая папка" ) );
}
void MainWindow::on_tButtonAddNote_clicked()
{
    const QModelIndex & index = ui->treeView->currentIndex();
    model.itemFromIndex( index )->appendRow( new NoteModelItem( "Новая заметка" ) );
}
void MainWindow::on_tButtonRemoveToTrash_clicked()
{

}
void MainWindow::on_tButtonDelete_clicked()
{

}
void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
    updateStates();
}

void MainWindow::updateStates()
{
    if ( !ui->treeView->currentIndex().isValid() )
    {
        ui->tButtonAddFolder->setEnabled( false );
        ui->tButtonAddNote->setEnabled( false );
        return;
    }

    BaseModelItem::Type type = model.typeItem( ui->treeView->currentIndex() );
    qDebug() << type;

    bool currentIsFolder = ( type == BaseModelItem::FOLDER );
    bool currentIsNote = ( type == BaseModelItem::NOTE );

    ui->tButtonAddFolder->setEnabled( currentIsFolder && !currentIsNote );
    ui->tButtonAddNote->setEnabled( currentIsFolder && !currentIsNote );
}
