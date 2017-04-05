#include "itkImage.h"
#include "itkImageFileReader.h"

#include "itkGradientMagnitudeImageFilter.h"
#include "itkGradientMagnitudeRecursiveGaussianImageFilter.h"

#include "QuickView.h"

using namespace std;

int main (int argc, char * argv[])
{
	if (argc < 2) {
		cerr << "Usage: " << endl;
		cerr << argv[0] << "   inputImageFile " << endl;
		return EXIT_FAILURE;
	}

	typedef float InputPixelType;
	typedef float OutputPixelType;

	typedef itk::Image<InputPixelType, 2> InputImageType;
	typedef itk::Image<OutputPixelType, 2> OutputImageType;

	typedef itk::ImageFileReader<InputImageType> ReaderType;
	ReaderType::Pointer reader = ReaderType::New();
	reader->SetFileName(argv[1]);

	typedef itk::GradientMagnitudeImageFilter<InputImageType, OutputImageType> GradientMagnitudeFilterType;
	GradientMagnitudeFilterType::Pointer gradientMagnitudeFilter = GradientMagnitudeFilterType::New();
	gradientMagnitudeFilter->SetInput(reader->GetOutput());

	gradientMagnitudeFilter->Update();

	typedef itk::GradientMagnitudeRecursiveGaussianImageFilter<InputImageType, OutputImageType> GradientMagnitudeRecursiveGaussianFilterType;
	GradientMagnitudeRecursiveGaussianFilterType::Pointer gradientMagnitudeRecursiveGaussianFilter = GradientMagnitudeRecursiveGaussianFilterType::New();
	gradientMagnitudeRecursiveGaussianFilter->SetInput(reader->GetOutput());

	const double sigma = 0.5;
	gradientMagnitudeRecursiveGaussianFilter->SetSigma(sigma);

	gradientMagnitudeRecursiveGaussianFilter->Update();

	QuickView viewer;
	viewer.SetNumberOfColumns(3);

	string description;

	description = "Original";
	viewer.AddImage(reader->GetOutput(), true, description);
	description = "Gradient Magnitude";
	viewer.AddImage(gradientMagnitudeFilter->GetOutput(), true, description);
	description = "Gradient Magnitude Recursive Gausssian\nSigma = " + to_string(sigma);
	viewer.AddImage(gradientMagnitudeRecursiveGaussianFilter->GetOutput(), true, description);
	viewer.Visualize();

	return EXIT_SUCCESS;
}
