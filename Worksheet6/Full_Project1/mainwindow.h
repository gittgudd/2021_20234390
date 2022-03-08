#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <vtkSmartPointer.h>
#include <vtkCubeSource.h>
#include <vtkPolyData.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkCellArray.h>
#include <vtkCellType.h>
#include <vtkDataSetMapper.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkPoints.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkTetra.h>
#include <vtkUnstructuredGrid.h>
#include <vtkSTLReader.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkShrinkFilter.h>
#include <vtkAlgorithm.h>
#include <vtkPlane.h>
#include <vtkClipDataSet.h>
#include <vtkSphereSource.h>
#include <vtkGeometryFilter.h>

#include <QMainWindow>
#include <QFileDialog>
#include <QFileInfo>
#include <QTextEdit>
#include <QString>
#include <QtDebug>
#include <QByteArray>
#include <QColorDialog>
#include <QCheckBox>

#include "ui_mainwindow.h"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void handleCubeButton();
    void handleSphereButton();
    void handleTetraButton();
    void handleObjColorButton();
    void handleBGColorButton();
    void handleShrinkFilter();
    void handleClipFilter();
    void toolbarButton();
    
    /*
    void shrinkFilter(bool shrinkBool);
    void clipFilter(bool clipBool);
    void sliderIntensity();
    */

   // bool shrinkBool;
   // bool clipBool;

private:
    Ui::MainWindow *ui;
    vtkSmartPointer<vtkDataSetMapper> mapper;
    vtkSmartPointer<vtkActor> actor;
    vtkSmartPointer<vtkNamedColors> colors;
    vtkSmartPointer<vtkRenderer> renderer;
    vtkSmartPointer<vtkAlgorithm> source;
    vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;
    
    void initialiseRender();

};

#endif // MAINWINDOW_H
