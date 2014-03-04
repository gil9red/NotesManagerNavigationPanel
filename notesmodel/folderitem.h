#ifndef FOLDERITEM_H
#define FOLDERITEM_H

#include "baseitem.h"

class FolderItem : public BaseItem
{
public:
    FolderItem( const QString & t, BaseItem * p = 0 );
};

#endif // FOLDERITEM_H
