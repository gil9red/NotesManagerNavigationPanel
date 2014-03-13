#include "foldermodelitem.h"

FolderModelItem::FolderModelItem( const QString & text )
    : BaseModelItem( text )
{
//        QIcon icon;
//        icon.addPixmap( qApp->style()->standardPixmap( QStyle::SP_DirClosedIcon ), QIcon::Normal, QIcon::Off );
//        icon.addPixmap( qApp->style()->standardPixmap( QStyle::SP_DirOpenIcon ), QIcon::Normal, QIcon::On );
//        setIcon( icon );
    setIcon( QIcon( ":/folder" ) );
    setType( FOLDER );

    setDropEnabled( true );
    setDragEnabled( true );
    setEditable( true );
}
