#include "hierarchicalview.h"

#include <QMenu>
#include <QColorDialog>

HierarchicalView::HierarchicalView( QWidget * parent )
    : QTreeView( parent )
{
    setModel( &model );
    setContextMenuPolicy( Qt::DefaultContextMenu );
}

void HierarchicalView::addTopLevelNote()
{
    model.appendToNotes( new NoteModelItem( tr( "Новая заметка" ) ) );
}
void HierarchicalView::addTopLevelFolder()
{
    model.appendToNotes( new FolderModelItem( tr( "Новая папка" ) ) );
}
void HierarchicalView::addFolder()
{
    QStandardItem * currentItem = model.itemFromIndex( currentIndex() );
    currentItem->appendRow( new FolderModelItem( tr( "Новая папка" ) ) );
}
void HierarchicalView::addNote()
{
    QStandardItem * currentItem = model.itemFromIndex( currentIndex() );
    currentItem->appendRow( new NoteModelItem( tr( "Новая заметка" ) ) );
}
void HierarchicalView::rename()
{
    edit( currentIndex() );
}
void HierarchicalView::open()
{

}
void HierarchicalView::removeToTrash()
{
    BaseModelItem * item = static_cast < BaseModelItem * > ( model.itemFromIndex( currentIndex() ) );
    model.appendToTrash( item );
}
void HierarchicalView::removeFromTrash()
{
    BaseModelItem * item = static_cast < BaseModelItem * > ( model.itemFromIndex( currentIndex() ) );
    model.removeOfTrash( item );
}
void HierarchicalView::clearTrash()
{
    model.clearTrash();
}

void HierarchicalView::textColor()
{
    const QModelIndex & index = currentIndex();
    QStandardItem * currentItem = model.itemFromIndex( index );

    const QColor & color = QColorDialog::getColor( currentItem->foreground().color(), this );
    currentItem->setForeground( color );
}
void HierarchicalView::defaultTextColor()
{
    const QModelIndex & index = currentIndex();
    QStandardItem * currentItem = model.itemFromIndex( index );
    currentItem->setForeground( QBrush() );
}
void HierarchicalView::backColor()
{
    const QModelIndex & index = currentIndex();
    QStandardItem * currentItem = model.itemFromIndex( index );

    const QColor & color = QColorDialog::getColor( currentItem->background().color(), this );
    currentItem->setBackground( color );
}
void HierarchicalView::defaultBackColor()
{
    const QModelIndex & index = currentIndex();
    QStandardItem * currentItem = model.itemFromIndex( index );
    currentItem->setBackground( QBrush() );
}

void HierarchicalView::contextMenuEvent( QContextMenuEvent * event )
{
    const QModelIndex & index = currentIndex();
    if ( !index.isValid() )
        return;

    BaseModelItem::Type type = model.typeItem( index );
    if ( type == BaseModelItem::ERROR )
        return;

    BaseModelItem * itemTrash = model.itemTrash;
    BaseModelItem * currentItem = static_cast < BaseModelItem * > ( model.itemFromIndex( index ) );

    bool isFolder = ( type == BaseModelItem::FOLDER );
    bool isNote = ( type == BaseModelItem::NOTE );
    bool isTrash = ( type == BaseModelItem::TRASH );
    bool isEmptyTrash = ( itemTrash->rowCount() == 0 );
    bool isChildTrash = false;
    if ( currentItem->parent() )
        isChildTrash = ( currentItem->parent() == itemTrash );


    QMenu menu( this );
    menu.addAction( QIcon( "" ), tr( "Добавить заметку верхнего уровня" ), this, SLOT( addTopLevelNote() ), QKeySequence( "" ) );
    menu.addAction( QIcon( "" ), tr( "Добавить папку верхнего уровня" ), this, SLOT( addTopLevelFolder() ), QKeySequence( "" ) );
    menu.addSeparator();

    if ( isFolder )
    {
        menu.addAction( QIcon( ":/add_folder" ), tr( "Добавить папку" ), this, SLOT( addFolder() ), QKeySequence( "" ) );
        menu.addAction( QIcon( ":/add_note" ), tr( "Добавить заметку" ), this, SLOT( addNote() ), QKeySequence( "" ) );
    }

    if ( !isTrash )
        menu.addAction( QIcon( "" ), tr( "Переименовать" ), this, SLOT( rename() ), QKeySequence( "" ) );

    if ( isNote )
        menu.addAction( QIcon( "" ), tr( "Открыть" ), this, SLOT( open() ), QKeySequence( "" ) );

    if ( !isTrash && !isChildTrash )
        menu.addAction( QIcon( ":/trash" ), tr( "Переместить в корзину" ), this, SLOT( removeToTrash() ), QKeySequence( "" ) );

    if ( isChildTrash )
        menu.addAction( QIcon( ":/delete" ), tr( "Удалить" ), this, SLOT( removeFromTrash() ), QKeySequence( "" ) );

    if ( isTrash && !isEmptyTrash )
        menu.addAction( QIcon( "" ), tr( "Очистить корзину" ), this, SLOT( clearTrash() ), QKeySequence( "" ) );

    menu.addSeparator();

    if ( !isTrash )
    {
        QMenu * menuTextColor = menu.addMenu( QIcon( "" ), tr( "Изменить цвет текста" ) );
        menuTextColor->addAction( QIcon( "" ), tr( "Цвет по умолчанию" ), this, SLOT( defaultTextColor() ), QKeySequence( "" ) );
        menuTextColor->addAction( QIcon( "" ), tr( "Выбрать цвет" ), this, SLOT( textColor() ), QKeySequence( "" ) );

        QMenu * menuBackColor = menu.addMenu( QIcon( "" ), tr( "Изменить цвет фона" ) );
        menuBackColor->addAction( QIcon( "" ), tr( "Цвет по умолчанию" ), this, SLOT( defaultBackColor() ), QKeySequence( "" ) );
        menuBackColor->addAction( QIcon( "" ), tr( "Выбрать цвет" ), this, SLOT( backColor() ), QKeySequence( "" ) );
    }

    menu.exec( event->globalPos() );
}
