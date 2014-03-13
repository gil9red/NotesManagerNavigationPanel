#ifndef HIERARCHICALVIEW_H
#define HIERARCHICALVIEW_H

#include <QTreeView>
#include <QContextMenuEvent>

#include "hierarchicalmodel.h"

class HierarchicalView : public QTreeView
{
    Q_OBJECT

public:
    explicit HierarchicalView( QWidget * parent = 0 ) ;
    
    HierarchicalModel model;

public slots:
    void addTopLevelNote();
    void addTopLevelFolder();
    void addFolder();
    void addNote();
    void rename();
    void open();
    void removeToTrash();
    void removeFromTrash();
    void clearTrash();

    void textColor();
    void defaultTextColor();
    void backColor();
    void defaultBackColor();

signals:
    void itemAboutOpen( BaseModelItem * );

protected:    
    void contextMenuEvent( QContextMenuEvent * event );
};

#endif // HIERARCHICALVIEW_H
