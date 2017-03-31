#include "itkImageFileReader.h"
#include "itkImage.h"
#include "itkRescaleIntensityImageFilter.h"

#include "itkGradientAnisotropicDiffusionImageFilter.h"
#include "itkCurvatureAnisotropicDiffusionImageFilter.h"
#include "itkCurvatureFlowImageFilter.h"

#include "QuickView.h"

using namespace std;

int main (int argc, char ** argv)
{
	if (argc < 2) {
		cerr << "Usage: " << endl;
		cerr << argv[0] << " inputImageFile" << endl;
		return EXIT_FAILURE;
	}

	typedef float InputPixelType;
	typedef float OutputPixelType;

	typedef itk::Image<InputPixelType, 2> InputImageType;
	typedef itk::Image<OutputPixelType, 2> OutputImageType;

	typedef itk::ImageFileReader<InputImageType> ReaderType;
	ReaderType::Pointer reader = ReaderType::New();
	reader->SetFileName(argv[1]);

	typedef itk::GradientAnisotropicDiffusionImageFilter<InputImageType, OutputImageType> GradientAnisotropicFilterType;
	GradientAnisotropicFilterType::Pointer gradientAnisotropicFilter = GradientAnisotropicFilterType::New();
	gradientAnisotropicFilter->SetInput(reader->GetOutput());

	const unsigned int gradientAnisotropicNumberOfIterations = 15;
	const double gradientAnisotropicTimeStep = 0.01;
	const double gradientAnistropicConductance = 3;

	gradientAnisotropicFilter->SetNumberOfIterations(gradientAnisotropicNumberOfIterations);
	gradientAnisotropicFilter->SetTimeStep(gradientAnisotropicTimeStep);
	gradientAnisotropicFilter->SetConductanceParameter(gradientAnistropicConductance);

	gradientAnisotropicFilter->Update();
	
	typedef itk::CurvatureAnisotropicDiffusionImageFilter<InputImageType, OutputImageType> CurvatureAnisotropicFilterType;
	CurvatureAnisotropicFilterType::Pointer curvatureAnisotropicFilter = CurvatureAnisotropicFilterType::New();
	curvatureAnisotropicFilter->SetInput(reader->GetOutput());

	const unsigned int curvatureAnisotropicNumberOfIterations = 5;
	const double curvatureAnisotropicTimeStep = 0.01;
	const double curvatureAnisotropicConductance = 3;
	const bool curvatureAnisotropicUseImageSpacing = true;

	curvatureAnisotropicFilter->SetNumberOfIterations(curvatureAnisotropicNumberOfIterations);
	curvatureAnisotropicFilter->SetTimeStep(curvatureAnisotropicTimeStep);
	curvatureAnisotropicFilter->SetConductanceParameter(curvatureAnisotropicConductance);
	curvatureAnisotropicUseImageSpacing ? curvatureAnisotropicFilter->UseImageSpacingOn() : curvatureAnisotropicFilter->UseImageSpacingOff();
	curvatureAnisotropicFilter->Update();

	typedef itk::CurvatureFlowImageFilter<InputImageType, OutputImageType> CurvatureFlowFilterType;
	CurvatureFlowFilterType::Pointer curvatureFlowFilter = CurvatureFlowFilterType::New();
	curvatureFlowFilter->SetInput(reader->GetOutput());

	const unsigned int curvatureFlowNumberOfIterations = 3;
	const double curvatureFlowTimeStep = 0.0025;

	curvatureFlowFilter->SetNumberOfIterations(curvatureFlowNumberOfIterations);
	curvatureFlowFilter->SetTimeStep(curvatureFlowTimeStep);
	curvatureFlowFilter->Update();

	QuickView viewer;
	viewer.SetNumberOfColumns(4);
	viewer.AddImage(reader->GetOutput());
	viewer.AddImage(gradientAnisotropicFilter->GetOutput());
	viewer.AddImage(curvatureAnisotropicFilter->GetOutput());
	viewer.AddImage(curvatureFlowFilter->GetOutput());
	viewer.Visualize();

	return EXIT_SUCCESS;
}
