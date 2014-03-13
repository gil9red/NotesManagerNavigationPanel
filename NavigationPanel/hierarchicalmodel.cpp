#include "hierarchicalmodel.h"

#include <QDomDocument>
#include <QMessageBox>
#include <QDebug>

int indexChild( QStandardItem * parent, QStandardItem * child  )
{
    for ( int i = 0; i < parent->rowCount(); i++ )
        if ( parent->child(i) == child )
            return i;
    return -1;
}

BaseModelItem * createItemOfDomElement( const QDomElement & element )
{
    BaseModelItem * node = createFromType( element.tagName() );

    if ( !node->isTrash() )
    {
        node->setText( element.attribute( "name" ) );
        node->setForeground( QColor( element.attribute( "text_color", "#000000" ) ) );
        node->setBackground( QColor( element.attribute( "back_color", "#FFFFFF" ) ) );
    }
    return node;
}
void parseDomElement( BaseModelItem * node, QDomElement & element )
{
    QDomElement child = element.firstChildElement();
    while( !child.isNull() )
    {
        BaseModelItem * child_item = createItemOfDomElement( child );
        node->appendRow( child_item );

        if ( child.hasChildNodes() )
            parseDomElement( child_item, child );

        child = child.nextSiblingElement();
    }
}

QDomElement createDomElementOfItem( BaseModelItem * item, QDomDocument & xmlDomDocument )
{
    QDomElement element = xmlDomDocument.createElement( stringType( item ) );
    if ( !item->isTrash() )
    {
        element.setAttribute( "name", item->text() );
        element.setAttribute( "text_color", item->foreground().color().name() );
        element.setAttribute( "back_color", item->background().color().name() );
    }

    return element;
}
void parseItem( BaseModelItem * node, QDomElement & element, QDomDocument & xmlDomDocument )
{
    for ( int i = 0; i < node->rowCount(); i++ )
    {
        BaseModelItem * itemChild = static_cast < BaseModelItem * > ( node->child(i) );
        QDomElement domChild = createDomElementOfItem( itemChild, xmlDomDocument );
        element.appendChild( domChild );
        parseItem( itemChild, domChild, xmlDomDocument );
    }
}


HierarchicalModel::HierarchicalModel( QObject * parent )
    : QStandardItemModel( parent ),
      itemTrash( 0 )
{
    setHorizontalHeaderLabels( QStringList() << tr( "Notes Manager" ) );
}

bool HierarchicalModel::read( QIODevice * device )
{
    QString errorStr;
    int errorLine;
    int errorColumn;

    QDomDocument xmlDomDocument;
    if ( !xmlDomDocument.setContent( device, true, &errorStr, &errorLine, &errorColumn) ) {
        QMessageBox::information( 0, QObject::tr( "Error" ), QObject::tr( "Parse error at line %1, column %2:\n%3" ).arg( errorLine ).arg( errorColumn ).arg( errorStr ) );
        return false;
    }

    QDomElement root = xmlDomDocument.documentElement();
    QDomElement child = root.firstChildElement();
    while( !child.isNull() )
    {
        BaseModelItem * topLevelItem = createItemOfDomElement( child );

        if ( topLevelItem->isTrash() )
            itemTrash = static_cast < TrashModelItem * > ( topLevelItem );

        appendToNotes( topLevelItem );

        if ( child.hasChildNodes() )
            parseDomElement( topLevelItem, child );

        child = child.nextSiblingElement();
    }

    return true;
}
bool HierarchicalModel::write( QIODevice * device )
{
    const int indentSize = 4;
    QTextStream out( device );
    out.setCodec("UTF-8");
    out << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";

    QDomDocument xmlDomDocument;
    QDomElement root = xmlDomDocument.createElement( "Notes" );
    xmlDomDocument.appendChild( root );

    for ( int i = 0; i < rowCount(); i++ )
    {
        BaseModelItem * topLevelItem = static_cast < BaseModelItem * > ( item(i) );

        QDomElement element = createDomElementOfItem( topLevelItem, xmlDomDocument );
        root.appendChild( element );

        parseItem( topLevelItem, element, xmlDomDocument );
    }

    xmlDomDocument.save( out, indentSize );

    return true;
}

void HierarchicalModel::appendToNotes( BaseModelItem * item )
{
    appendRow( item );
}
void HierarchicalModel::appendToTrash( BaseModelItem * item )
{
    QStandardItem * removedItem = item;
    // Если есть родитель - тогда это под элемент
    // иначе - элемент верхнего уровня
    if ( removedItem->parent() )
    {
        int row = removedItem->row();
        removedItem = removedItem->parent()->takeChild( row );
        removedItem->parent()->removeRow( row );
    } else
    {
        const QModelIndex & index = removedItem->index();
        int row = index.row();
        removedItem = takeItem( removedItem->row() );
        removeRow( row );
    }

    itemTrash->appendRow( removedItem );
}
bool HierarchicalModel::removeOfTrash( BaseModelItem * item )
{    
    int index = indexChild( itemTrash, item );
    if ( index != -1 )
    {
        itemTrash->removeRow( index );
        return true;
    }

    return false;
}
void HierarchicalModel::clearTrash()
{
    while ( itemTrash->rowCount() )
        itemTrash->removeRow( itemTrash->rowCount() - 1 );
}
