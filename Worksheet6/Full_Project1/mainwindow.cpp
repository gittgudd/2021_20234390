#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
	// standard call to setup Qt UI (same as previously)
	ui->setupUi(this);

	connect(ui->cubeButton, &QPushButton::released, this, &MainWindow::handleCubeButton);
	connect(ui->sphereButton, &QPushButton::released, this, &MainWindow::handleSphereButton);
	connect(ui->tetraButton, &QPushButton::released, this, &MainWindow::handleTetraButton);
	connect(ui->objColorButton, &QPushButton::released, this, &MainWindow::handleObjColorButton);
	connect(ui->bgColorButton, &QPushButton::released, this, &MainWindow::handleBGColorButton);
	connect(ui->shrinkFilter, &QCheckBox::clicked, this, &MainWindow::handleShrinkFilter);
	connect(ui->clipFilter, &QCheckBox::clicked, this, &MainWindow::handleClipFilter);
	connect(ui->actionFileOpen, &QAction::triggered, this, &MainWindow::toolbarButton);

	

	// Now need to create a VTK render window and link it to the QtVTK widget
	ui->qvtkWidget->SetRenderWindow(renderWindow); // note that vtkWidget is the name I gave to my QtVTKOpenGLWidget in Qt creator


	//--------------------------------------------- Setting Mapper, Actor, and Renderer --------------------------------------------------------------------------

	mapper = vtkSmartPointer<vtkDataSetMapper>::New();
	actor = vtkSmartPointer<vtkActor>::New();
	colors = vtkSmartPointer<vtkNamedColors>::New();
	renderer = vtkSmartPointer<vtkRenderer>::New();
	ui->qvtkWidget->GetRenderWindow()->AddRenderer( renderer );

	
	actor->GetProperty()->SetColor(colors->GetColor3d("Red").GetData());
	renderer->SetBackground(colors->GetColor3d("Silver").GetData());

}

void MainWindow::handleCubeButton()
{
	// Create a cube using a vtkCubeSource
	vtkSmartPointer<vtkCubeSource> cubeSource = vtkSmartPointer<vtkCubeSource>::New();

	// Create a mapper that will hold the cube's geometry in a format suitable for rendering
	source = cubeSource;
	
	
	initialiseRender();
}

void MainWindow::handleSphereButton()
{
	vtkSmartPointer<vtkSphereSource> sphereSource = vtkSmartPointer<vtkSphereSource>::New();
	source = sphereSource;
	initialiseRender();
}

void MainWindow::handleTetraButton()
{
	vtkNew<vtkPoints> points;
	points->InsertNextPoint(0, 0, 0);
	points->InsertNextPoint(1, 0, 0);
	points->InsertNextPoint(1, 1, 0);
	points->InsertNextPoint(0, 1, 1);


	vtkNew<vtkUnstructuredGrid> unstructuredGrid;
	unstructuredGrid->SetPoints(points);

	vtkIdType ptIds[] = {0, 1, 2, 3};
	unstructuredGrid->InsertNextCell(VTK_TETRA, 4, ptIds);


	//Setting up geometry fitler
	vtkSmartPointer<vtkGeometryFilter> geometryFilter = vtkSmartPointer<vtkGeometryFilter>::New();
	geometryFilter->SetInputData(unstructuredGrid);
	source = geometryFilter;


	// Create a mapper and actor
	initialiseRender();
}

void MainWindow::handleObjColorButton()
{
	QColor objColor = QColorDialog::getColor(Qt::yellow, this );
    if( objColor.isValid() )
    {
      qDebug() << "Color Choosen : " << objColor.name();
	  actor->GetProperty()->SetColor(objColor.redF(), objColor.greenF(), objColor.blueF());

	  renderWindow->Render();
    }

}

void MainWindow::handleBGColorButton()
{
	QColor bgColor = QColorDialog::getColor(Qt::yellow, this );
    if( bgColor.isValid() )
    {
      qDebug() << "Color Choosen : " << bgColor.name();
	  renderer->SetBackground(bgColor.redF(), bgColor.greenF(), bgColor.blueF());

	  renderWindow->Render();
    }

}

void MainWindow::handleShrinkFilter()
{
	if(ui->shrinkFilter->isChecked())
	{
		vtkSmartPointer<vtkShrinkFilter> shrinkFilter = vtkSmartPointer<vtkShrinkFilter>::New();
		shrinkFilter->SetInputConnection( source->GetOutputPort() );
		shrinkFilter->SetShrinkFactor(.8);
		shrinkFilter->Update();
		mapper->SetInputConnection( shrinkFilter->GetOutputPort() );
	}
	
	else
	{
		mapper->SetInputConnection( source->GetOutputPort());
	}
	renderWindow->Render();
}

void MainWindow::handleClipFilter()
{
	if(ui->clipFilter->isChecked())
	{
		vtkSmartPointer<vtkPlane> planeLeft = vtkSmartPointer<vtkPlane>::New();
		planeLeft->SetOrigin(0.0, 0.0, 0.0);
		planeLeft->SetNormal(-1.0, 0.0, 0.0);
		vtkSmartPointer<vtkClipDataSet> clipFilter = vtkSmartPointer<vtkClipDataSet>::New();
		clipFilter->SetInputConnection( source->GetOutputPort() ) ;
		clipFilter->SetClipFunction( planeLeft.Get() );
		mapper->SetInputConnection( clipFilter->GetOutputPort() );
	}
	
	else
	{
		mapper->SetInputConnection( source->GetOutputPort());
	}
	renderWindow->Render();
}

void MainWindow::toolbarButton()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open STL File"), "./", tr("STL Files(*.stl)"));

	QByteArray ba = fileName.toLocal8Bit();
	const char *c_str = ba.data();

	vtkNew<vtkSTLReader> reader;
	reader->SetFileName(c_str);
	reader->Update();
	// Visualize

	source = reader;

	/*
	actor->GetProperty()->SetDiffuse(0.8);
	actor->GetProperty()->SetDiffuseColor(colors->GetColor3d("LightSteelBlue").GetData());
	actor->GetProperty()->SetSpecular(0.3);
	actor->GetProperty()->SetSpecularPower(60.0);
	*/

	initialiseRender();
}

void MainWindow::initialiseRender()
{	
	mapper->SetInputConnection(source->GetOutputPort());
	actor->SetMapper(mapper);
	actor->GetProperty()->EdgeVisibilityOn();
	renderer->AddActor(actor);
	renderer->ResetCamera();
	renderer->GetActiveCamera()->Azimuth(-10);
	renderer->GetActiveCamera()->Elevation(-20);
	renderer->ResetCameraClippingRange();
	
	
	
	renderWindow->Render();
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
