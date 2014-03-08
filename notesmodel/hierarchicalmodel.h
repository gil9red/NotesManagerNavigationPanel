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
    explicit HierarchicalModel( QObject * parent = 0 );
    virtual ~HierarchicalModel();

    virtual QModelIndex index( int row, int column, const QModelIndex & parent ) const;
    virtual QModelIndex parent( const QModelIndex &child ) const;
    virtual int rowCount( const QModelIndex & parent = QModelIndex() ) const;
    virtual int columnCount( const QModelIndex & /*parent = QModelIndex()*/ ) const;
    virtual QVariant headerData( int section, Qt::Orientation orientation, int role ) const;
    virtual QVariant data( const QModelIndex & index, int role = Qt::DisplayRole ) const;
    virtual bool setData(const QModelIndex & index, const QVariant & value, int role);
    virtual BaseItem * item( const QModelIndex & index ) const;
    Qt::DropActions supportedDropActions () const;
    virtual Qt::ItemFlags flags( const QModelIndex & index ) const;

    QVector < BaseItem * > children;

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
