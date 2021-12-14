#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect( ui->addButton, &QPushButton::released, this, &MainWindow::handleAddButton );
    connect( ui->editButton, &QPushButton::released, this, &MainWindow::handleEditButton );
    connect( ui->removeButton, &QPushButton::released, this, &MainWindow::handleRemoveButton );
    connect( this, &MainWindow::statusUpdateMessage, ui->statusBar, &QStatusBar::showMessage );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleAddButton() {
    emit statusUpdateMessage( QString("Add button was clicked"), 0 );
}

void MainWindow::handleEditButton() {
    emit statusUpdateMessage( QString("Edit button was clicked"), 0 );
}

void MainWindow::handleRemoveButton() {
    emit statusUpdateMessage( QString("Remove button was clicked"), 0 );
}