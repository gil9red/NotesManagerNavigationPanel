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

    BaseItem * f1 = new FolderItem( "f1" );
    BaseItem * f2 = new FolderItem( "f2" );
    BaseItem * n2 = new NoteItem( "n2" );
    BaseItem * f3 = new FolderItem( "f3" );
    BaseItem * n3 = new NoteItem( "n3" );

    f2->append( n2 );
    f2->insert( 0, new FolderItem( "Folder_1" ) );
    f2->insert( 0, new FolderItem( "Folder_2" ) );
    f2->append( new NoteItem( "Note_1" ) );
    f2->insert( 0, new NoteItem( "Note_2" ) );

    f3->append( n3 );

    ui->treeView->setModel( &model );
    model.children.append( f1 );
    model.children.append( f2 );
    model.children.append( f3 );

    ui->treeView->expandAll();

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
}
void MainWindow::on_tButtonAddNote_clicked()
{
}
void MainWindow::on_tButtonRemove_clicked()
{
}
void MainWindow::updateStates()
{
    if ( !ui->treeView->currentIndex().isValid() )
    {
        ui->tButtonAddFolder->setEnabled( false );
        ui->tButtonAddNote->setEnabled( false );
        return;
    }

    BaseItem::Type type = model.item( ui->treeView->currentIndex() )->type();

    bool currentIsFolder = ( type == BaseItem::FOLDER );
    bool currentIsNote = ( type == BaseItem::NOTE );

    ui->tButtonAddFolder->setEnabled( currentIsFolder && !currentIsNote );
    ui->tButtonAddNote->setEnabled( currentIsFolder && !currentIsNote );
}

void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
    qDebug() << model.item( index )->type();
    updateStates();
}
