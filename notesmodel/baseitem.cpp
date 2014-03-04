#include "baseitem.h"

BaseItem::BaseItem( BaseItem * p )
    : d_parent(p),
      d_type(BASE)
{

}
BaseItem::BaseItem( const QString & t, BaseItem * p )
    : d_parent( p ),
      d_type(BASE)
{
    setText(t);
}
BaseItem::BaseItem( const QString & t, const QIcon & i, BaseItem * p )
    : d_parent( p ),
      d_type(BASE)
{
    setText(t);
    setIcon(i);
}
BaseItem::~BaseItem()
{
    qDeleteAll( d_children );
}

void BaseItem::setParent( BaseItem * parent )
{
    d_parent = parent;
}
BaseItem * BaseItem::parent()
{
    return d_parent;
}

BaseItem * BaseItem::child( int index )
{
    return d_children[ index ];
}
int BaseItem::childCount() const
{
    return d_children.size();
}

int BaseItem::indexOf( BaseItem * item, int from )
{
    return d_children.indexOf( item, from );
}

void BaseItem::insert( int index, BaseItem * child )
{
    d_children.insert( index, child );
    child->setParent( this );
}
void BaseItem::append( BaseItem * child )
{
    d_children.append( child );
    child->setParent( this );
}
void BaseItem::append( const QList < BaseItem * > & list )
{
    foreach ( BaseItem * item, list )
        append( item );
}
bool BaseItem::remove( BaseItem * child )
{
    return d_children.removeOne( child );
}

void BaseItem::setData( int role, const QVariant & value )
{
    d_data[role] = value;
}
QVariant BaseItem::data( int role ) const
{
    return d_data[role];
}

void BaseItem::setText( const QString & text )
{
    setData( Qt::DisplayRole, text );
}
QString BaseItem::text() const
{
    return data( Qt::DisplayRole ).toString();
}

void BaseItem::setIcon( const QIcon & icon )
{
    setData(Qt::DecorationRole, icon);
}
QIcon BaseItem::icon() const
{
    return qvariant_cast < QIcon > ( data( Qt::DecorationRole ) );
}

BaseItem::Type BaseItem::type() const
{
    return d_type;
}

QList < BaseItem * > BaseItem::children()
{
    return d_children;
}
