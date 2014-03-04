#ifndef BASEITEM_H
#define BASEITEM_H

#include <QMap>
#include <QVariant>
#include <QIcon>

class BaseItem
{
public:
    enum Type { NOTE, FOLDER, BASE };

public:
    BaseItem( BaseItem * p = 0 );
    BaseItem( const QString & t, BaseItem * p = 0 );
    BaseItem( const QString & t, const QIcon & i, BaseItem * p = 0 );
    virtual ~BaseItem();

    void setParent( BaseItem * parent );
    BaseItem * parent();

    BaseItem * child( int index );
    int childCount() const;

    int indexOf( BaseItem * item, int from = 0 );

    void insert( int index, BaseItem * child );
    void append( BaseItem * child );
    void append( const QList < BaseItem * > & list );
    bool remove( BaseItem * child );

    void setData( int role, const QVariant & value );
    QVariant data( int role ) const;

    void setText( const QString & text );
    QString text() const;

    void setIcon( const QIcon & icon );
    QIcon icon() const;

    Type type() const;

    QList < BaseItem * > children();

protected:
    QList < BaseItem * > d_children;
    QMap < int, QVariant > d_data;
    BaseItem * d_parent;
    Type d_type;
};

#endif // BASEITEM_H
