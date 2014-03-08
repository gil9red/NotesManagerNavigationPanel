#ifndef HIERARCHICALMODEL_H
#define HIERARCHICALMODEL_H

#include <QStandardItemModel>

class BaseModelItem: public QStandardItem
{
public:
    enum Type { BASE, NOTE, FOLDER };

public:
    explicit BaseModelItem( const QString & text = QString() )
        : QStandardItem( text )
    {
        setFlags( Qt::ItemIsEnabled | Qt::ItemIsSelectable );
    }
    virtual ~BaseModelItem() {}
    virtual int type() { return BASE; }
};

class NoteModelItem: public BaseModelItem
{
public:
    explicit NoteModelItem( const QString & text = QString() )
        : BaseModelItem( text )
    {
        setIcon( QIcon( ":/note" ) );

        setDragEnabled( true );
        setEditable( true );
    }
    virtual int type() { return NOTE; }
};

class FolderModelItem: public BaseModelItem
{
public:
    explicit FolderModelItem( const QString & text = QString() )
        : BaseModelItem( text )
    {
        setIcon( QIcon( ":/folder" ) );

        setDropEnabled( true );
        setDragEnabled( true );
        setEditable( true );
    }
    virtual int type() { return FOLDER; }
};


class HierarchicalModel : public QStandardItemModel
{
    Q_OBJECT

public:
    explicit HierarchicalModel( QObject * parent = 0 );

    void appendToNotes( BaseModelItem * item );
    bool removeOfNotes( BaseModelItem * item );
    void appendToTrash( BaseModelItem * item );
    bool removeOfTrash( BaseModelItem * item );

    BaseModelItem::Type typeItem( const QModelIndex & index );

    BaseModelItem * itemNotes;
    BaseModelItem * itemTrash;
};

#endif // HIERARCHICALMODEL_H
