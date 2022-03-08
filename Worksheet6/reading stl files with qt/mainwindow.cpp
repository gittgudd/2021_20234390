#include <vtkActor.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkSTLReader.h>
#include <vtkCamera.h>
#include <QString>
#include <QFileDialog>
#include <QDebug>
#include <QByteArray>
#include <vtkSmartPointer.h>

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

	// Render and interact
	//renderWindow->Render();					// ###### Not needed with Qt ######
	//renderWindowInteractor->Start();			// ###### Not needed with Qt ######
	//--------------------------------------------- /Code From Example 1 -------------------------------------------------------------------------*/
}

MainWindow::~MainWindow()
{
	delete ui;
}
