#include <itkImage.h>
#include <itkImageSeriesReader.h>
#include <itkNumericSeriesFileNames.h>
#include <itkBMPImageIO.h>
#include <itkBinomialBlurImageFilter.h>
#include <itkImageToVTKImageFilter.h>
#include <itkThresholdImageFilter.h>

#include <vtkSmartPointer.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkVolume.h>
#include <vtkSmartVolumeMapper.h>
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

	const unsigned int FIRST = 1;
	const unsigned int LAST = 250;
	const unsigned int REPS = 5;
	const unsigned int MIN = 50;
	const unsigned int MAX = 200;

	typedef unsigned char PixelType;
	const unsigned int Dimension = 3;

	typedef itk::Image<PixelType, Dimension> ImageType;

	typedef itk::NumericSeriesFileNames NameGeneratorType;
	NameGeneratorType::Pointer nameGenerator = NameGeneratorType::New();
	nameGenerator->SetSeriesFormat("t%d.bmp");
	nameGenerator->SetStartIndex(FIRST);
	nameGenerator->SetEndIndex(LAST);
	nameGenerator->SetIncrementIndex(1);

	cout << "Reading files..." << endl;

	typedef itk::ImageSeriesReader<ImageType> ReaderType;
	ReaderType::Pointer reader = ReaderType::New();
	reader->SetImageIO(itk::BMPImageIO::New());
	reader->SetFileNames(nameGenerator->GetFileNames());
	reader->Update();

	cout << "Filtering..." << endl;

	typedef itk::BinomialBlurImageFilter<ImageType, ImageType> BinomialBlurFilterType;
	BinomialBlurFilterType::Pointer filter = BinomialBlurFilterType::New();
	filter->SetInput(reader->GetOutput());
	filter->SetRepetitions(3);
	filter->Update();

	cout << "Segmentating..." << endl;

	typedef itk::ThresholdImageFilter<ImageType> ThresholdImageFilterType;
	ThresholdImageFilterType::Pointer segmentator = ThresholdImageFilterType::New();
	segmentator->SetInput(filter->GetOutput());
	segmentator->SetOutsideValue(0);
	segmentator->ThresholdOutside(MIN, MAX);
	segmentator->Update();

	cout << "Converting to VTK..." << endl;

	typedef itk::ImageToVTKImageFilter<ImageType> ConnectorType;
	ConnectorType::Pointer connector = ConnectorType::New();
	connector->SetInput(segmentator->GetOutput());
	connector->Update();

	vtkSmartPointer<vtkImageData> imageData = vtkSmartPointer<vtkImageData>::New();
	imageData->ShallowCopy(connector->GetOutput());

	vtkSmartPointer<vtkSmartVolumeMapper> volumeMapper = vtkSmartPointer<vtkSmartVolumeMapper>::New();
	volumeMapper->SetInputData(imageData);

	vtkSmartPointer<vtkColorTransferFunction>volumeColor = vtkSmartPointer<vtkColorTransferFunction>::New();
	volumeColor->AddRGBPoint(0,   0.00, 0.00, 0.00);
	volumeColor->AddRGBPoint(20,  1.00, 0.50, 0.30);
	volumeColor->AddRGBPoint(40,  1.00, 0.50, 0.30);
	volumeColor->AddRGBPoint(50,  0.95, 0.95, 0.85);
	volumeColor->AddRGBPoint(200, 1.00, 1.00, 0.90);

	vtkSmartPointer<vtkPiecewiseFunction> volumeScalarOpacity = vtkSmartPointer<vtkPiecewiseFunction>::New();
	volumeScalarOpacity->AddPoint(0,   0.00);
	volumeScalarOpacity->AddPoint(20,  0.10);
	volumeScalarOpacity->AddPoint(40,  0.15);
	volumeScalarOpacity->AddPoint(49,  0.15);
	volumeScalarOpacity->AddPoint(50,  0.80);
	volumeScalarOpacity->AddPoint(200, 1.00);

	vtkSmartPointer<vtkPiecewiseFunction> volumeGradientOpacity = vtkSmartPointer<vtkPiecewiseFunction>::New();
	volumeGradientOpacity->AddPoint(0,   0.0);
	volumeGradientOpacity->AddPoint(20,  0.1);
	volumeGradientOpacity->AddPoint(50,  0.5);
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

	vtkSmartPointer<vtkRenderer> ren = vtkSmartPointer<vtkRenderer>::New();
	ren->AddVolume(volume);
	ren->SetBackground(0.1, 0.2, 0.3);

	double *c = volume->GetCenter();
	vtkSmartPointer<vtkCamera> camera = ren->GetActiveCamera();
	camera->SetFocalPoint(c[0], c[1], c[2]);
	camera->SetPosition(c[0] + 400, c[1], c[2]);
	camera->SetViewUp(0, 0, -1);

	vtkSmartPointer<vtkRenderWindow> renWin = vtkSmartPointer<vtkRenderWindow>::New();
	renWin->AddRenderer(ren);
	renWin->SetSize(640, 480);
	renWin->Render();

	vtkSmartPointer<vtkRenderWindowInteractor> iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	iren->SetRenderWindow(renWin);
	iren->Initialize();
	iren->Start();
	
	return EXIT_SUCCESS;
}