#ifndef HIERARCHICALMODEL_H
#define HIERARCHICALMODEL_H

#include <QAbstractItemModel>
#include "baseitem.h"
#include "noteitem.h"
#include "folderitem.h"

class HierarchicalModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit HierarchicalModel( QObject * parent = 0 ) : QAbstractItemModel( parent ) { }
    ~HierarchicalModel() { qDeleteAll( children ); }

    QVector < BaseItem * > children;

    virtual QModelIndex index( int row, int column, const QModelIndex & parent ) const
    {
        if ( !hasIndex(row, column, parent) )
            return QModelIndex();

        // запрашивают индексы корневых узлов
        if ( !parent.isValid() )
            return createIndex( row, column, children[row] );

        BaseItem * parentItem = item(parent);
        return createIndex( row, column, parentItem->child( row ) );
    }
    virtual QModelIndex parent( const QModelIndex &child ) const
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
    virtual int rowCount( const QModelIndex & parent = QModelIndex() ) const
    {
        if ( !parent.isValid() )
            return children.size();

        BaseItem * parentInfo = item( parent );
        return parentInfo->childCount();
    }
    virtual int columnCount( const QModelIndex & /*parent = QModelIndex()*/ ) const
    {
        return 1;
    }
    virtual QVariant headerData( int section, Qt::Orientation orientation, int role ) const
    {
        if ( section == 0 && orientation == Qt::Horizontal && role == Qt::DisplayRole )
            return tr( "Notes" );

        return QVariant();
    }
    virtual QVariant data( const QModelIndex & index, int role = Qt::DisplayRole ) const
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
    virtual bool setData(const QModelIndex & index, const QVariant & value, int role)
    {
        if ( role != Qt::EditRole )
            return false;

        BaseItem * i = item( index );
        i->setText( value.toString() );
        emit dataChanged(index, index);
        return true;
    }
    virtual BaseItem * item( const QModelIndex & index ) const
    {
        if ( index.isValid() )
            return static_cast < BaseItem * > ( index.internalPointer() );

        return 0;
    }


    Qt::DropActions supportedDropActions () const
    {
        return Qt::MoveAction;
    }

    virtual Qt::ItemFlags flags( const QModelIndex & index ) const
    {
        if ( !index.isValid() )
            return 0;

        Qt::ItemFlags f = QAbstractItemModel::flags( index );
        f |= Qt::ItemIsEditable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled;
        return f;
    }
//    bool dropMimeData( const QMimeData * mimeData, Qt::DropAction action, int row, int column, const QModelIndex & parent )
//    {
//        qDebug() << "Drop happened";

//        if ( action == Qt::IgnoreAction )
//            return true;
//        if ( !mimeData->hasFormat( "application/ami.pointer" ) )
//            return false;
//        if ( column > 0 )
//            return false;

//        BaseItem * i;
//        QByteArray data = mimeData->data( "application/ami.pointer" );
//        QDataStream stream( &data, QIODevice::ReadOnly );
//        stream.readRawData( (char*) &i, sizeof( i ) );

//        qDebug() << row << column << item(parent)->text << " | " << i->text;

//        return true;
//    }
//    QMimeData* mimeData (const QModelIndexList& indexes) const
//    {
//        QMimeData *mimeData = new QMimeData();
//        QByteArray encodedData;

//        QDataStream stream(&encodedData, QIODevice::WriteOnly);

//        QListIterator<QModelIndex> iterator(indexes);
//        while (iterator.hasNext())
//        {
//            QModelIndex index = iterator.next();
//            if (index.isValid())
//            {
//                void * p = index.internalPointer();
//                stream.writeRawData((char*)&p, sizeof(p)); // god forgive me
//            }
//        }

//        mimeData->setData("application/ami.pointer", encodedData);
//        return mimeData;
//    }
//    QStringList mimeTypes () const
//    {
//        return QStringList() << "application/ami.pointer";
//    }
};

#endif // HIERARCHICALMODEL_H
