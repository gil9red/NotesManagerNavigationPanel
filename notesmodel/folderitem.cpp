#include "folderitem.h"

FolderItem::FolderItem( const QString & t, BaseItem * p )
    : BaseItem( t, QIcon( ":/folder" ), p )
{
    d_type = FOLDER;
}
