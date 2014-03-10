#include "noteeditor.h"

NoteEditor::NoteEditor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NoteEditor),
    item(0)
{
    ui->setupUi(this);
}

NoteEditor::~NoteEditor()
{
    delete ui;
}
