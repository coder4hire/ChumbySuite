#include "FolderDialog.h"
#include "ui_CFolderDialog.h"
#include <QDir>
#include <QTreeView>
#include <QModelIndex>

CFolderDialog::CFolderDialog(QWidget *parent) :
    QDialog(parent,Qt::FramelessWindowHint),
    ui(new Ui::CFolderDialog)
{
    ui->setupUi(this);

    model = new QFileSystemModel;
    model->setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
    model->setRootPath(QDir::rootPath());
    ui->treeView->setModel(model);


    for(int i=1;i<ui->treeView->header()->count();i++)
    {
        ui->treeView->header()->hideSection(i);
    }
}

CFolderDialog::~CFolderDialog()
{
    delete model;
    delete ui;
}

void CFolderDialog::showEvent(QShowEvent *)
{
    QModelIndex index = model->index(SelectedPath);
    ui->treeView->selectionModel()->setCurrentIndex(index,QItemSelectionModel::ClearAndSelect | QItemSelectionModel::Current);
}

void CFolderDialog::on_buttonBox_clicked(QAbstractButton *button)
{
    QModelIndex index = ui->treeView->selectionModel()->currentIndex();
    SelectedPath = index.isValid() ? model->filePath(index) : "";
}
