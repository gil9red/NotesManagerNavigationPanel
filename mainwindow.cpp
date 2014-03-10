#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSettings>
#include <QDebug>
#include <QFile>
#include <QDomDocument>
#include <QMessageBox>

BaseModelItem * createNode( QDomElement element, HierarchicalModel * model )
{
    BaseModelItem * node;

    const QString & tag = element.tagName();
    if ( tag == "Note" )
        node = new NoteModelItem();
    else if ( tag == "Folder" )
        node = new FolderModelItem();
    else if ( tag == "Trash" )
        node = model->itemTrash;
    else
        return 0;

    node->d_node = element;

    if ( node != model->itemTrash )
    {
        node->setText( element.attribute( "name" ) );
        node->setForeground( QColor( element.attribute( "text_color", "#000000" ) ) );
        node->setBackground( QColor( element.attribute( "back_color", "#FFFFFF" ) ) );
    }
    return node;
}
void parseNode( BaseModelItem * node, HierarchicalModel * model )
{
    QDomElement child = node->d_node.firstChildElement();
    while( !child.isNull() )
    {
        BaseModelItem * child_item = createNode( child, model );
        node->appendRow( child_item );

        if ( child.hasChildNodes() )
            parseNode( child_item, model );

        child = child.nextSiblingElement();
    }
}
bool read( QIODevice * device, HierarchicalModel * model )
{
    QDomDocument domDocument;
    QString errorStr;
    int errorLine;
    int errorColumn;

    if ( !domDocument.setContent( device, true, &errorStr, &errorLine, &errorColumn) ) {
        QMessageBox::information( 0, QObject::tr( "Error" ), QObject::tr( "Parse error at line %1, column %2:\n%3" ).arg( errorLine ).arg( errorColumn ).arg( errorStr ) );
        return false;
    }

    QDomElement root = domDocument.documentElement();
    QDomElement child = root.firstChildElement();
    while( !child.isNull() )
    {
        BaseModelItem * topLevelItem = createNode( child, model );

        if ( topLevelItem != model->itemTrash )
            model->appendToNotes( topLevelItem );

        if ( child.hasChildNodes() )
            parseNode( topLevelItem, model );

        child = child.nextSiblingElement();
    }

    return true;
}

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
    read( &file, &ui->treeNotes->model );


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
        editor = new NoteEditor();
        editor->item = item;

        ui->tabNotes->addTab( editor, item->icon(), item->text() );
        ui->tabNotes->setCurrentWidget( editor );
    }

    editor->ui->lineEdit->setText( item->text() );
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


//    const QString & fileName = qApp->applicationDirPath() + "/notebook.xml";
//    QFile file( fileName );
//    if ( !file.open( QFile::WriteOnly | QFile::Text ) )
//    {
//        QMessageBox::warning( this, tr( "Error" ),tr( "Cannot write file %1:\n%2." ).arg( fileName ).arg( file.errorString() ) );
//        return;
//    }

    QDomDocument document;
    for ( int i = 0; i < ui->treeNotes->model.rowCount(); i++ )
    {
        BaseModelItem * topLevelItem = static_cast < BaseModelItem * > ( ui->treeNotes->model.item(i) );
        document.appendChild( topLevelItem->d_node );

        qDebug() << topLevelItem->text();
    }

    qDebug() << document.toString();

//    const int indentSize = 4;
//    QTextStream out( &file );
//    document.save( out, indentSize );
}
