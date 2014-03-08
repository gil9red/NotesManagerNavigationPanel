#include "hierarchicalmodel.h"

int indexChild( QStandardItem * item )
{
    for ( int i = 0; i < item->rowCount(); i++ )
        if ( item->child(i) == item )
            return i;
    return -1;
}

HierarchicalModel::HierarchicalModel( QObject * parent )
    : QStandardItemModel( parent ),
      itemNotes( new BaseModelItem() ),
      itemTrash( new BaseModelItem() )
{
    QFont font( BaseModelItem().font() );
    font.setBold( true );

    itemNotes->setIcon( QIcon( ":/notes" ) );
    itemNotes->setText( tr( "Заметки" ) );
    itemNotes->setDragEnabled( false );
    itemNotes->setDropEnabled( true );
    itemNotes->setEditable( false );
    itemNotes->setFont( font );

    itemTrash->setIcon( QIcon( ":/trash" ) );
    itemTrash->setText( tr( "Корзина" ) );
    itemTrash->setDragEnabled( false );
    itemTrash->setDropEnabled( true );
    itemTrash->setEditable( false );
    itemTrash->setFont( font );

    clear();
    appendRow( itemNotes );
    appendRow( itemTrash );
}

void HierarchicalModel::appendToNotes( BaseModelItem * item )
{
    itemNotes->appendRow( item );
}
bool HierarchicalModel::removeOfNotes( BaseModelItem * item )
{
    int index = indexChild( item );
    if ( index != -1 )
    {
        itemNotes->removeRow( index );
        return true;
    }

    return false;
}
void HierarchicalModel::appendToTrash( BaseModelItem * item )
{
    itemTrash->appendRow( item );
}
bool HierarchicalModel::removeOfTrash( BaseModelItem * item )
{
    int index = indexChild( item );
    if ( index != -1 )
    {
        itemTrash->removeRow( index );
        return true;
    }

    return false;
}

BaseModelItem::Type HierarchicalModel::typeItem( const QModelIndex & index )
{
    return ( BaseModelItem::Type ) static_cast < BaseModelItem * > ( itemFromIndex( index ) )->type();
}
