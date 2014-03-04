#ifndef NOTEITEM_H
#define NOTEITEM_H

#include "baseitem.h"

class NoteItem : public BaseItem
{
public:
    NoteItem( const QString & t, BaseItem * p = 0 );
};

#endif // NOTEITEM_H
