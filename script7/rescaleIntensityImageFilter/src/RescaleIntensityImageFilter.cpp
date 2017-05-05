#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkRescaleIntensityImageFilter.h"
#include "itkCastImageFilter.h"
#include "itkMedianImageFilter.h"

#include <cstdlib>
#include <iostream>

#include "itkImageToVTKImageFilter.h"

#include "vtkVersion.h"
#include "vtkImageViewer.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkSmartPointer.h"
#include "vtkImageActor.h"
#include "vtkImageMapper3D.h"
#include "vtkInteractorStyleImage.h"
#include "vtkRenderer.h"
#include "vtkCamera.h"

using namespace std;

#define INTERACTOR 0

int main(int argc, char *argv[])
{
	if (argc < 2) {
		cerr << "Usage: " << argv[0] << " filename" << endl;
		return EXIT_FAILURE;
	}
    
	typedef itk::Image<unsigned char, 2>  ImageType;

	typedef itk::ImageFileReader<ImageType> ReaderType;
	ReaderType::Pointer reader = ReaderType::New();
	reader->SetFileName(argv[1]);

	typedef itk::MedianImageFilter<ImageType, ImageType> MedianImageFilterType;
	MedianImageFilterType::Pointer filter = MedianImageFilterType::New();
	filter->SetInput(reader->GetOutput());

	typedef itk::ImageToVTKImageFilter<ImageType> ConnectorType;
	ConnectorType::Pointer originalConnector = ConnectorType::New();
	originalConnector->SetInput(reader->GetOutput());
	vtkSmartPointer<vtkImageActor> originalActor = vtkSmartPointer<vtkImageActor>::New();

	typedef itk::ImageToVTKImageFilter<ImageType> ConnectorType;
	ConnectorType::Pointer filterConnector = ConnectorType::New();
	filterConnector->SetInput(filter->GetOutput());
	vtkSmartPointer<vtkImageActor> filteredActor = vtkSmartPointer<vtkImageActor>::New();

#if VTK_MAJOR_VERSION <= 5
	originalActor->SetInput(originalConnector->GetOutput());
	filterActor->SetInput(filterConnector->GetOutput());
#else
	originalConnector->Update();
	originalActor->GetMapper()->SetInputData(originalConnector->GetOutput());
	filterConnector->Update();
	filteredActor->GetMapper()->SetInputData(filterConnector->GetOutput());
#endif

	// There will be one render window
	vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->SetSize(900, 300);

	vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	interactor->SetRenderWindow(renderWindow);

	// Define viewport ranges
	// (xmin, ymin, xmax, ymax)
	double leftViewport[4] = {0.0, 0.0, 0.5, 1.0};
	double rightViewport[4] = {0.5, 0.0, 1.0, 1.0};

	// Setup both renderers
	vtkSmartPointer<vtkRenderer> leftRenderer = vtkSmartPointer<vtkRenderer>::New();
	renderWindow->AddRenderer(leftRenderer);
	leftRenderer->SetViewport(leftViewport);
	leftRenderer->SetBackground(.1, .2, .3);

	vtkSmartPointer<vtkRenderer> rightRenderer = vtkSmartPointer<vtkRenderer>::New();
	renderWindow->AddRenderer(rightRenderer);
	rightRenderer->SetViewport(rightViewport);
	rightRenderer->SetBackground(.3, .2, .1);

	// Add the sphere to the left and the cube to the right
	leftRenderer->AddActor(originalActor);
	rightRenderer->AddActor(filteredActor);

	vtkSmartPointer<vtkCamera> camera = vtkSmartPointer<vtkCamera>::New();
	leftRenderer->SetActiveCamera(camera);
	rightRenderer->SetActiveCamera(camera);

	leftRenderer->ResetCamera();
	renderWindow->Render();

#if INTERACTOR == 0
	vtkSmartPointer<vtkInteractorStyleImage> style = vtkSmartPointer<vtkInteractorStyleImage>::New();
	interactor->SetInteractorStyle(style);
	interactor->Start();
# else
	vtkSmartPointer<vtkInteractorStyleTrackballCamera> style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
	interactor->SetInteractorStyle(style);
	interactor->Start();
#endif

	return EXIT_SUCCESS;
}
