#ifndef NOTEMODELITEM_H
#define NOTEMODELITEM_H

#include "basemodelitem.h"

class NoteModelItem: public BaseModelItem
{
public:
    explicit NoteModelItem( const QString & text = QString() );
};
#endif // NOTEMODELITEM_H
