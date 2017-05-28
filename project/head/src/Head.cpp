#include "itkImage.h"
#include "itkImageSeriesReader.h"
#include "itkNumericSeriesFileNames.h"
#include "itkBMPImageIO.h"
#include "itkBinomialBlurImageFilter.h"
#include "itkImageToVTKImageFilter.h"

#include <vtkSmartPointer.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkVolume16Reader.h>
#include <vtkVolume.h>
#include <vtkVolumeRayCastMapper.h>
#include <vtkVolumeRayCastCompositeFunction.h>
#include <vtkVolumeProperty.h>
#include <vtkColorTransferFunction.h>
#include <vtkPiecewiseFunction.h>
#include <vtkCamera.h>

using namespace std;

int main(int argc, char * argv[])
{
	if (argc < 1) {
		cerr << "Usage: " << endl;
		cerr << argv[0] << " Head" << endl;
		return EXIT_FAILURE;
	}

	const unsigned int reps = 3;

	typedef unsigned char PixelType;
	const unsigned int Dimension = 3;

	typedef itk::Image<PixelType, Dimension> ImageType;

	typedef itk::NumericSeriesFileNames NameGeneratorType;
	NameGeneratorType::Pointer nameGenerator = NameGeneratorType::New();
	nameGenerator->SetSeriesFormat("t%d.bmp");
	nameGenerator->SetStartIndex(1);
	nameGenerator->SetEndIndex(250);
	nameGenerator->SetIncrementIndex(1);

	cout << "Name generator done" << endl;

	typedef itk::ImageSeriesReader<ImageType> ReaderType;
	ReaderType::Pointer reader = ReaderType::New();
	reader->SetImageIO(itk::BMPImageIO::New());
	reader->SetFileNames(nameGenerator->GetFileNames());

	cout << "Image Series done" << endl;

	typedef itk::BinomialBlurImageFilter<ImageType, ImageType> BinomialBlurFilterType;
	BinomialBlurFilterType::Pointer binomialBlur = BinomialBlurFilterType::New();
	binomialBlur->SetInput(reader->GetOutput());
	binomialBlur->SetRepetitions(reps);
	binomialBlur->Update();

	cout << "Binomial Blur done" << endl;

	typedef itk::ImageToVTKImageFilter<ImageType> ConnectorType;
	ConnectorType::Pointer connector = ConnectorType::New();
	connector->SetInput(reader->GetOutput());

	cout << "To VTK done" << endl;

	vtkSmartPointer<vtkRenderer> ren = vtkSmartPointer<vtkRenderer>::New();
	vtkSmartPointer<vtkRenderWindow> renWin = vtkSmartPointer<vtkRenderWindow>::New();
	renWin->AddRenderer(ren);
	vtkSmartPointer<vtkRenderWindowInteractor> iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	iren->SetRenderWindow(renWin);

	vtkSmartPointer<vtkVolumeRayCastCompositeFunction> rayCastFunction = vtkSmartPointer<vtkVolumeRayCastCompositeFunction>::New();

	vtkSmartPointer<vtkVolumeRayCastMapper> volumeMapper = vtkSmartPointer<vtkVolumeRayCastMapper>::New();
	volumeMapper->SetInputData(connector->GetOutput());
	volumeMapper->SetVolumeRayCastFunction(rayCastFunction);

	vtkSmartPointer<vtkColorTransferFunction>volumeColor = vtkSmartPointer<vtkColorTransferFunction>::New();
	volumeColor->AddRGBPoint(0, 0.0, 0.0, 0.0);
	volumeColor->AddRGBPoint(500, 1.0, 0.5, 0.3);
	volumeColor->AddRGBPoint(1000, 1.0, 0.5, 0.3);
	volumeColor->AddRGBPoint(1150, 1.0, 1.0, 0.9);

	vtkSmartPointer<vtkPiecewiseFunction> volumeScalarOpacity = vtkSmartPointer<vtkPiecewiseFunction>::New();
	volumeScalarOpacity->AddPoint(0, 0.00);
	volumeScalarOpacity->AddPoint(500, 0.15);
	volumeScalarOpacity->AddPoint(1000, 0.15);
	volumeScalarOpacity->AddPoint(1150, 0.85);

	vtkSmartPointer<vtkPiecewiseFunction> volumeGradientOpacity = vtkSmartPointer<vtkPiecewiseFunction>::New();
	volumeGradientOpacity->AddPoint(0, 0.0);
	volumeGradientOpacity->AddPoint(90, 0.5);
	volumeGradientOpacity->AddPoint(100, 1.0);

	vtkSmartPointer<vtkVolumeProperty> volumeProperty = vtkSmartPointer<vtkVolumeProperty>::New();
	volumeProperty->SetColor(volumeColor);
	volumeProperty->SetScalarOpacity(volumeScalarOpacity);
	volumeProperty->SetGradientOpacity(volumeGradientOpacity);
	volumeProperty->SetInterpolationTypeToLinear();
	volumeProperty->ShadeOn();
	volumeProperty->SetAmbient(0.4);
	volumeProperty->SetDiffuse(0.6);
	volumeProperty->SetSpecular(0.2);

	vtkSmartPointer<vtkVolume> volume = vtkSmartPointer<vtkVolume>::New();
	volume->SetMapper(volumeMapper);
	volume->SetProperty(volumeProperty);
	ren->AddViewProp(volume);

	vtkCamera *camera = ren->GetActiveCamera();
	double *c = volume->GetCenter();
	camera->SetFocalPoint(c[0], c[1], c[2]);
	camera->SetPosition(c[0] + 400, c[1], c[2]);
	camera->SetViewUp(0, 0, -1);

	renWin->SetSize(640, 480);

	iren->Initialize();
	iren->Start();
	
	return EXIT_SUCCESS;
}