#include "notemodelitem.h"

NoteModelItem::NoteModelItem( const QString & text )
    : BaseModelItem( text )
{
//        QIcon icon;
//        icon.addPixmap( qApp->style()->standardPixmap( QStyle::SP_FileIcon ) );
//        setIcon( icon );
    setIcon( QIcon( ":/note" ) );
    setType( NOTE );

    setDragEnabled( true );
    setEditable( true );
}
