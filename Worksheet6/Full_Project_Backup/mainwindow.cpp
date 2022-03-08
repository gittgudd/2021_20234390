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

#include <QFileDialog>
#include <QFileInfo>
#include <QTextEdit>
#include <QString>
#include <QDebug>
#include <QByteArray>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
	// standard call to setup Qt UI (same as previously)
	ui->setupUi(this);

	connect(ui->cubeButton, &QPushButton::released, this, &MainWindow::handleCubeButton);
	connect(ui->tetraButton, &QPushButton::released, this, &MainWindow::handleTetraButton);
	connect(ui->actionFileOpen, &QAction::triggered, this, &MainWindow::toolbarButton);

	// Now need to create a VTK render window and link it to the QtVTK widget
	vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;
	ui->qvtkWidget->SetRenderWindow(renderWindow); // note that vtkWidget is the name I gave to my QtVTKOpenGLWidget in Qt creator

	// Now use the VTK libraries to render something. To start with you can copy-paste the cube example code, there are comments to show where the code must be modified.
	//--------------------------------------------- Code From Example 1 --------------------------------------------------------------------------
			
}

void MainWindow::handleCubeButton()
{
	// Create a cube using a vtkCubeSource
	vtkSmartPointer<vtkCubeSource> cubeSource = vtkSmartPointer<vtkCubeSource>::New();

	// Create a mapper that will hold the cube's geometry in a format suitable for rendering
	vtkSmartPointer<vtkDataSetMapper> mapper = vtkSmartPointer<vtkDataSetMapper>::New();
	mapper->SetInputConnection( cubeSource->GetOutputPort() );

	// Create an actor that is used to set the cube's properties for rendering and place it in the window
	vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);
	actor->GetProperty()->EdgeVisibilityOn();

	vtkSmartPointer<vtkNamedColors> colors = vtkSmartPointer<vtkNamedColors>::New();
	actor->GetProperty()->SetColor( colors->GetColor3d("Red").GetData() );

	// Create a renderer, and render window
	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
	//vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();		// ###### We've already created the renderWindow this time ######
	ui->qvtkWidget->GetRenderWindow()->AddRenderer( renderer );									// ###### ask the QtVTKOpenGLWidget for its renderWindow ######

	// Link a renderWindowInteractor to the renderer (this allows you to capture mouse movements etc)  ###### Not needed with Qt ######
	//vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	//renderWindowInteractor->SetRenderWindow( ui->vtkWidget->GetRenderWindow() );				

	// Add the actor to the scene
	renderer->AddActor(actor);
	renderer->SetBackground( colors->GetColor3d("Silver").GetData() );

	// Setup the renderers's camera
	renderer->ResetCamera();
	renderer->GetActiveCamera()->Azimuth(30);
	renderer->GetActiveCamera()->Elevation(30);
	renderer->ResetCameraClippingRange();

}

void MainWindow::handleTetraButton()
{
	vtkNew<vtkNamedColors> colors;
	vtkNew<vtkPoints> points;
	points->InsertNextPoint(0, 0, 0);
	points->InsertNextPoint(1, 0, 0);
	points->InsertNextPoint(1, 1, 0);
	points->InsertNextPoint(0, 1, 1);

	points->InsertNextPoint(2, 2, 2);
	points->InsertNextPoint(5, 2, 2);
	points->InsertNextPoint(5, 5, 2);
	points->InsertNextPoint(2, 5, 5);

	// Method 1
	vtkNew<vtkUnstructuredGrid> unstructuredGrid1;
	unstructuredGrid1->SetPoints(points);

	vtkIdType ptIds[] = {0, 1, 2, 3};
	unstructuredGrid1->InsertNextCell(VTK_TETRA, 4, ptIds);

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
	actor1->GetProperty()->SetColor(colors->GetColor3d("Red").GetData());

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

	// Link a renderWindowInteractor to the renderer (this allows you to capture mouse movements etc)  ###### Not needed with Qt ######
	//vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	//renderWindowInteractor->SetRenderWindow( ui->vtkWidget->GetRenderWindow() );

	// Add the actor to the scene
	renderer->AddActor(actor1);
	renderer->AddActor(actor2);
	renderer->SetBackground(colors->GetColor3d("Silver").GetData());
	renderer->ResetCamera();
	renderer->GetActiveCamera()->Azimuth(-10);
	renderer->GetActiveCamera()->Elevation(-20);
	// Render and interact
	//renderWindow->Render();					// ###### Not needed with Qt ######
	//renderWindowInteractor->Start();			// ###### Not needed with Qt ######
	//--------------------------------------------- /Code From Example 1 -------------------------------------------------------------------------*/
}

void MainWindow::toolbarButton()
{
		vtkNew<vtkNamedColors> colors;

QString fileName = QFileDialog::getOpenFileName(this, tr("Open STL File"), "./", tr("STL Files(*.stl)"));

	QByteArray ba = fileName.toLocal8Bit();
	const char *c_str = ba.data();

	vtkNew<vtkSTLReader> reader;
	reader->SetFileName(c_str);
	reader->Update();
	// Visualize
	vtkNew<vtkPolyDataMapper> mapper;
	mapper->SetInputConnection(reader->GetOutputPort());

	vtkNew<vtkActor> actor;
	actor->SetMapper(mapper);
	actor->GetProperty()->SetDiffuse(0.8);
	actor->GetProperty()->SetDiffuseColor(colors->GetColor3d("LightSteelBlue").GetData());
	actor->GetProperty()->SetSpecular(0.3);
	actor->GetProperty()->SetSpecularPower(60.0);

	// Create a renderer, and render window
	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
	//vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();		// ###### We've already created the renderWindow this time ######
	ui->qvtkWidget->GetRenderWindow()->AddRenderer(renderer); // ###### ask the QtVTKOpenGLWidget for its renderWindow ######

	renderer->AddActor(actor);
	renderer->SetBackground(colors->GetColor3d("DarkOliveGreen").GetData());
	renderer->ResetCamera();
	renderer->GetActiveCamera()->Azimuth(-10);
	renderer->GetActiveCamera()->Elevation(-20);
}

/*
void MainWindow::shrinkFilter(bool shrinkBool)
{
	if (ui -> shrinkBool -> isChecked())
	{
		//enable filter
	} 
}
*/

MainWindow::~MainWindow()
{
	delete ui;
}
