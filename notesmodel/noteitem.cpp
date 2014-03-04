#include "noteitem.h"

NoteItem::NoteItem( const QString & t, BaseItem * p )
    : BaseItem( t, QIcon( ":/note" ), p )
{
    d_type = NOTE;
}
