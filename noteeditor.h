#ifndef NOTEEDITOR_H
#define NOTEEDITOR_H

#include <QMainWindow>

namespace Ui {
    class NoteEditor;
}
#include "hierarchicalmodel.h"
#include "ui_noteeditor.h"

class NoteEditor : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit NoteEditor(QWidget *parent = 0);
    ~NoteEditor();
    
public:
    Ui::NoteEditor *ui;

    BaseModelItem * item;
};

#endif // NOTEEDITOR_H
