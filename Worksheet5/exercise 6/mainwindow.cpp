// mainwindow.cpp ------------------------------------------------------
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "stockitem.h"
#include "edititemdialog.h"
#include "stockitemlistmodel.h"
#include <QMessageBox>
#include <QAction>
#include <iostream>
#include <QDialog>
#include <QFileDialog>
#include <QString>
#include <QFile>
#include <QIODevice>

MainWindow::MainWindow(QWidget *parent) :
QMainWindow(parent),
ui(new Ui::MainWindow) {
ui->setupUi(this);
// Link the ListModel to the ListView
ui->listView->setModel( &stockList );
// Tell this list view to only accept single selections
ui->listView->setSelectionBehavior( QAbstractItemView::SelectItems );
// Connect the released() signal of the addButton object to the handleAddButton slot in this object
connect( ui->addButton, &QPushButton::released, this, &MainWindow::handleAddButton );
connect( ui->editButton, &QPushButton::released, this, &MainWindow::handleEditButton );
connect( ui->removeButton, &QPushButton::released, this, &MainWindow::handleRemoveButton );
connect( ui->actionSave, &QAction::triggered, this, &MainWindow::handleSaveButton );
connect( this, &MainWindow::statusUpdateMessage, ui->statusBar, &QStatusBar::showMessage );
}

MainWindow::~MainWindow() {
delete ui;
}
void MainWindow::handleAddButton() {
StockItem item;
stockList.addItem( item );
emit statusUpdateMessage( QString("Add button was clicked"), 0 );
}

void MainWindow::handleEditButton() {
EditItemDialog dialog( this );
QModelIndexList selectedList;
selectedList = ui->listView->selectionModel()->selectedIndexes();
if( selectedList.length() == 1 ) {
// selectedList is a list of all selected items in the listView. Since we set its
// behaviour to single selection, were only interested in the first selecteded item.
StockItem item = stockList.getItem( selectedList[0] );
if( dialog.runDialog( item ) ) {
// user clicked ok, need to update item in list...
stockList.setItem( item, selectedList[0] );
}
} else {
emit statusUpdateMessage( QString("No item selected to edit!"), 0 );
}
}

void MainWindow::handleRemoveButton() {
emit statusUpdateMessage( QString("Remove button was clicked"), 0 );
}


void MainWindow::handleSaveButton() {
    emit statusUpdateMessage( QString("Stocks saved to txt file"), 0 );

    //prompting the user for a file name
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("Text files (*.txt)"));
    emit statusUpdateMessage( QString(fileName), 0 );
    
    /*
    //converting filename from qstring to char*
    QByteArray ba = fileName.toLocal8Bit();
    const char *charFile = ba.data();

    //opening a file to store saved data in
    std::ofstream saveFile;
    //naming file
    saveFile.open (charFile);
    */

    //opening the file
    if (fileName.isEmpty())
        return;

    QFile file(fileName);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    QTextStream out(&file);

    //get row count
    int noOfRows = stockList.rowCount(QModelIndex());

    for(int i=0; i<noOfRows; i++)
    {
        //getting the index
        QModelIndex index = stockList.index(i, 0, QModelIndex());
        StockItem item = stockList.getItem(index);

        //writing to file
        out << item.getName() <<"\t"<< item.getUnitCost() <<"\t"<< item.getStockLevel() <<"\t"<< item.getReorder() <<"\n"; 
    }

    //closing file
    file.close();
}