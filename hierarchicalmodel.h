#ifndef HIERARCHICALMODEL_H
#define HIERARCHICALMODEL_H

#include <QStandardItemModel>

class BaseModelItem: public QStandardItem
{
public:
    enum Type { BASE, NOTE, FOLDER, TRASH, ALL_NOTES, ERROR = -1, ROLE_TYPE = Qt::UserRole };

public:
    explicit BaseModelItem( const QString & text = QString() )
        : QStandardItem( text )
    {
        setType( BASE );
        setFlags( Qt::ItemIsEnabled | Qt::ItemIsSelectable );
    }
    virtual ~BaseModelItem() {}

    virtual int type() { return data( ROLE_TYPE ).toInt(); }
    virtual void setType(Type t) { setData( t, ROLE_TYPE ); }
};

class NoteModelItem: public BaseModelItem
{
public:
    explicit NoteModelItem( const QString & text = QString() )
        : BaseModelItem( text )
    {
        setIcon( QIcon( ":/note" ) );
        setType( NOTE );

        setDragEnabled( true );
        setEditable( true );
    }
};

class FolderModelItem: public BaseModelItem
{
public:
    explicit FolderModelItem( const QString & text = QString() )
        : BaseModelItem( text )
    {
        setIcon( QIcon( ":/folder" ) );
        setType( FOLDER );

        setDropEnabled( true );
        setDragEnabled( true );
        setEditable( true );
    }
};


class HierarchicalModel : public QStandardItemModel
{
    Q_OBJECT

public:
    explicit HierarchicalModel( QObject * parent = 0 );

    void appendToNotes( BaseModelItem * item );
    void appendToTrash( BaseModelItem * item );
    bool removeOfTrash( BaseModelItem * item );
    void clearTrash();

    BaseModelItem::Type typeItem( const QModelIndex & index );

    //BaseModelItem * itemNotes;
    BaseModelItem * itemTrash;
};

#endif // HIERARCHICALMODEL_H
