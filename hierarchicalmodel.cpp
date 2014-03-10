#include "hierarchicalmodel.h"

#include <QDebug>

int indexChild( QStandardItem * parent, QStandardItem * child  )
{
    for ( int i = 0; i < parent->rowCount(); i++ )
        if ( parent->child(i) == child )
            return i;
    return -1;
}

HierarchicalModel::HierarchicalModel( QObject * parent )
    : QStandardItemModel( parent ),
      itemTrash( new BaseModelItem() )
{
    setHorizontalHeaderLabels( QStringList() << tr( "Notes Manager" ) );

    QFont font( BaseModelItem().font() );
    font.setBold( true );

    itemTrash->setType( BaseModelItem::TRASH );
    itemTrash->setIcon( QIcon( ":/trash" ) );
    itemTrash->setText( tr( "Корзина" ) );
    itemTrash->setDragEnabled( false );
    itemTrash->setDropEnabled( true );
    itemTrash->setEditable( false );
    itemTrash->setFont( font );

    appendRow( itemTrash );
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
        const QModelIndex & index = indexFromItem( removedItem );
        if ( index.isValid() )
        {
            int row = index.row();
            removedItem = takeItem( removedItem->row() );
            removeRow( row );
        }
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

BaseModelItem::Type HierarchicalModel::typeItem( const QModelIndex & index )
{
    if ( !index.isValid() )
        return BaseModelItem::ERROR;

    BaseModelItem * item = static_cast < BaseModelItem * > ( itemFromIndex( index ) );
    if ( !item )
        return BaseModelItem::ERROR;

    return ( BaseModelItem::Type ) item->type();
}
