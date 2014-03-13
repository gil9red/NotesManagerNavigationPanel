#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSettings>
#include <QDebug>
#include <QFile>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    const QString & fileName = qApp->applicationDirPath() + "/notebook.xml";
    QFile file( fileName );
    if ( !file.open( QFile::ReadOnly | QFile::Text ) )
    {
        QMessageBox::warning( this, tr( "Error" ), tr( "Cannot read file %1:\n%2." ).arg( fileName ).arg( file.errorString() ) );
        return;
    }
    ui->treeNotes->model.read( &file );


    connect( ui->treeNotes, SIGNAL( itemAboutOpen( BaseModelItem * ) ), SLOT ( openItem( BaseModelItem * ) ) );
    connect( ui->tabNotes, SIGNAL( tabCloseRequested(int) ), SLOT( closeItem(int) ) );

    QSettings ini( qApp->applicationDirPath() + "/ini.ini", QSettings::IniFormat );
    ui->splitter->restoreState( ini.value( ui->splitter->objectName() ).toByteArray() );
    restoreState( ini.value( "State" ).toByteArray() );
    restoreGeometry( ini.value( "Geometry" ).toByteArray() );
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openItem( BaseModelItem * item )
{
    if ( !item )
    {
        QMessageBox::information( this, tr( "Ошибка" ), tr( "Объект не существует" ) );
        return;
    }
    bool isUnique = true;
    NoteEditor * editor;
    for ( int i = 0; i < ui->tabNotes->count(); i++ )
    {
        editor = static_cast < NoteEditor * > ( ui->tabNotes->widget(i) );
        if ( editor->item == item )
        {
            ui->tabNotes->setCurrentWidget( editor );
            isUnique = false;
            break;
        }
    }

    if ( isUnique && item->isNote() )
    {
        NoteEditor * editor = new NoteEditor();
        editor->item = item;
        editor->ui->lineEdit->setText( item->text() );

        ui->tabNotes->addTab( editor, item->icon(), item->text() );
        ui->tabNotes->setCurrentWidget( editor );
    }
}
void MainWindow::closeItem( int index )
{
    ui->tabNotes->widget( index )->deleteLater();
    ui->tabNotes->removeTab( index );
}

void MainWindow::closeEvent(QCloseEvent *)
{
    QSettings ini( qApp->applicationDirPath() + "/ini.ini", QSettings::IniFormat );
    ini.setValue( ui->splitter->objectName(), ui->splitter->saveState() );
    ini.setValue( "State", saveState() );
    ini.setValue( "Geometry", saveGeometry() );


    const QString & fileName = qApp->applicationDirPath() + "/notebook.xml";
    QFile file( fileName );
    if ( !file.open( QFile::WriteOnly | QFile::Text ) )
    {
        QMessageBox::warning( this, tr( "Error" ),tr( "Cannot write file %1:\n%2." ).arg( fileName ).arg( file.errorString() ) );
        return;
    }
    ui->treeNotes->model.write( &file );
}
