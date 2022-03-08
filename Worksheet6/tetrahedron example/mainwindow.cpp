#include <vtkSmartPointer.h>
#include <vtkCubeSource.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkCamera.h>
#include <vtkPolyData.h>
#include <vtkDataSetMapper.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkCellArray.h>
#include <vtkCellType.h>
#include <vtkPoints.h>
#include <vtkTetra.h>
#include <vtkUnstructuredGrid.h>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
	// standard call to setup Qt UI (same as previously)
	ui->setupUi(this);

	// Now need to create a VTK render window and link it to the QtVTK widget
	vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;
	ui->qvtkWidget->SetRenderWindow(renderWindow); // note that vtkWidget is the name I gave to my QtVTKOpenGLWidget in Qt creator

	// Now use the VTK libraries to render something. To start with you can copy-paste the cube example code, there are comments to show where the code must be modified.
	//--------------------------------------------- Code From Example 1 --------------------------------------------------------------------------

	vtkNew<vtkNamedColors> colors;

	vtkNew<vtkPoints> points;
	points->InsertNextPoint(0, 0, 0);
	points->InsertNextPoint(1, 0, 0);
	points->InsertNextPoint(1, 1, 0);
	points->InsertNextPoint(0, 1, 1);

	points->InsertNextPoint(2, 2, 2);
	points->InsertNextPoint(3, 2, 2);
	points->InsertNextPoint(3, 3, 2);
	points->InsertNextPoint(2, 3, 3);

	vtkNew<vtkUnstructuredGrid> unstructuredGrid1;
	unstructuredGrid1->SetPoints(points);

	vtkIdType ptIds[] = {0, 1, 2, 3};
	unstructuredGrid1->InsertNextCell(VTK_TETRA, 4, ptIds);

	// Method 2
	vtkNew<vtkUnstructuredGrid> unstructuredGrid2;
	unstructuredGrid2->SetPoints(points);

	vtkNew<vtkTetra> tetra;

	tetra->GetPointIds()->SetId(0, 4);
	tetra->GetPointIds()->SetId(1, 5);
	tetra->GetPointIds()->SetId(2, 6);
	tetra->GetPointIds()->SetId(3, 7);

	vtkNew<vtkCellArray> cellArray;
	cellArray->InsertNextCell(tetra);
	unstructuredGrid2->SetCells(VTK_TETRA, cellArray);

	// Create a mapper and actor
	vtkNew<vtkDataSetMapper> mapper1;
	mapper1->SetInputData(unstructuredGrid1);

	vtkNew<vtkActor> actor1;
	actor1->SetMapper(mapper1);
	actor1->GetProperty()->SetColor(colors->GetColor3d("Cyan").GetData());

	// Create a mapper and actor
	vtkNew<vtkDataSetMapper> mapper2;
	mapper2->SetInputData(unstructuredGrid2);

	vtkNew<vtkActor> actor2;
	actor2->SetMapper(mapper2);
	actor2->GetProperty()->SetColor(colors->GetColor3d("Yellow").GetData());

	// Create a renderer, and render window
	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
	//vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();		// ###### We've already created the renderWindow this time ######
	ui->qvtkWidget->GetRenderWindow()->AddRenderer(renderer); // ###### ask the QtVTKOpenGLWidget for its renderWindow ######

	// Add the actor to the scene
	renderer->AddActor(actor1);
	renderer->AddActor(actor2);
	renderer->SetBackground(colors->GetColor3d("DarkGreen").GetData());
	renderer->ResetCamera();
	renderer->GetActiveCamera()->Azimuth(-10);
	renderer->GetActiveCamera()->Elevation(-20);

	// Render and interact
	//renderWindow->Render();					// ###### Not needed with Qt ######
	//renderWindowInteractor->Start();			// ###### Not needed with Qt ######
	//--------------------------------------------- /Code From Example 1 -------------------------------------------------------------------------*/
}

MainWindow::~MainWindow()
{
	delete ui;
}
