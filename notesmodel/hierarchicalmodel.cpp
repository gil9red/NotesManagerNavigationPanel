#include "hierarchicalmodel.h"

HierarchicalModel::HierarchicalModel( QObject * parent )
    : QAbstractItemModel( parent )
{
}
HierarchicalModel::~HierarchicalModel()
{
    qDeleteAll( children );
}

QModelIndex HierarchicalModel::index( int row, int column, const QModelIndex & parent ) const
{
    if ( !hasIndex(row, column, parent) )
        return QModelIndex();

    // запрашивают индексы корневых узлов
    if ( !parent.isValid() )
        return createIndex( row, column, children[row] );

    BaseItem * parentItem = item(parent);
    return createIndex( row, column, parentItem->child( row ) );
}
QModelIndex HierarchicalModel::parent( const QModelIndex &child ) const
{
    if ( !child.isValid() )
        return QModelIndex();

    BaseItem * i = item( child );
    if ( !i->parent() )
        return QModelIndex();

    BaseItem * parentItem = i->parent();

    int row = 0;
    if ( parentItem->parent() )
        row = parentItem->parent()->indexOf( parentItem );

    return createIndex( row, 0, parentItem );
}
int HierarchicalModel::rowCount( const QModelIndex & parent ) const
{
    if ( !parent.isValid() )
        return children.size();

    BaseItem * parentInfo = item( parent );
    return parentInfo->childCount();
}
int HierarchicalModel::columnCount( const QModelIndex & ) const
{
    return 1;
}
QVariant HierarchicalModel::headerData( int section, Qt::Orientation orientation, int role ) const
{
    if ( section == 0 && orientation == Qt::Horizontal && role == Qt::DisplayRole )
        return tr( "Notes" );

    return QVariant();
}
QVariant HierarchicalModel::data( const QModelIndex & index, int role ) const
{
    if ( !index.isValid() )
        return QVariant();

    BaseItem * i = item( index );

    switch ( role )
    {
    case Qt::DisplayRole:
    case Qt::EditRole:
        return i->text();

    case Qt::DecorationRole:
        return i->icon();

    default:
        return QVariant();
    }

    return QVariant();
}
bool HierarchicalModel::setData(const QModelIndex & index, const QVariant & value, int role)
{
    if ( role != Qt::EditRole )
        return false;

    BaseItem * i = item( index );
    i->setText( value.toString() );
    emit dataChanged(index, index);
    return true;
}
BaseItem * HierarchicalModel::item( const QModelIndex & index ) const
{
    if ( index.isValid() )
        return static_cast < BaseItem * > ( index.internalPointer() );

    return 0;
}
Qt::DropActions HierarchicalModel::supportedDropActions () const
{
    return Qt::MoveAction;
}
Qt::ItemFlags HierarchicalModel::flags( const QModelIndex & index ) const
{
    if ( !index.isValid() )
        return 0;

    Qt::ItemFlags f = QAbstractItemModel::flags( index );
    f |= Qt::ItemIsEditable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled;
    return f;
}
