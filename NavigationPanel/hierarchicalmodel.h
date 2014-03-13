#ifndef HIERARCHICALMODEL_H
#define HIERARCHICALMODEL_H

#include "basemodelitem.h"
#include "notemodelitem.h"
#include "foldermodelitem.h"
#include "trashmodelitem.h"

static BaseModelItem * createFromType( BaseModelItem::Type type )
{
    BaseModelItem * item = 0;
    switch ( type )
    {
    case BaseModelItem::BASE:
        item = new BaseModelItem();
        break;
    case BaseModelItem::NOTE:
        item = new NoteModelItem();
        break;
    case BaseModelItem::FOLDER:
        item = new FolderModelItem();
        break;
    case BaseModelItem::TRASH:
        item = new TrashModelItem();
        break;
    default:
        return item;
    }
    return item;
}
static BaseModelItem * createFromType( const QString & type )
{
    BaseModelItem * item = 0;

    if ( type == "Base" )
        item = new BaseModelItem();

    else if ( type == "Note" )
        item = new NoteModelItem();

    else if ( type == "Folder" )
        item = new FolderModelItem();

    else if ( type == "Trash" )
        item = new TrashModelItem();

    return item;
}

class HierarchicalModel : public QStandardItemModel
{
    Q_OBJECT

public:
    explicit HierarchicalModel( QObject * parent = 0 );

    bool read( QIODevice * device );
    bool write( QIODevice * device );

    void appendToNotes( BaseModelItem * item );
    void appendToTrash( BaseModelItem * item );
    bool removeOfTrash( BaseModelItem * item );
    void clearTrash();

    TrashModelItem * itemTrash;
};

#endif // HIERARCHICALMODEL_H
