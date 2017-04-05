#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkDiscreteGaussianImageFilter.h"
#include "itkBinomialBlurImageFilter.h"
#include "itkRecursiveGaussianImageFilter.h"

#include "QuickView.h"

using namespace std;

int main(int argc, char * argv[])
{
	if (argc < 2) {
		cerr << "Usage: " << endl;
		cerr << argv[0] << " inputImageFile" << endl;
		return EXIT_FAILURE;
	}

	typedef float PixelType;
	const unsigned int Dimension = 2;

	typedef itk::Image<PixelType, Dimension> ImageType;

	typedef itk::ImageFileReader<ImageType> ReaderType;

	ReaderType::Pointer reader = ReaderType::New();
	reader->SetFileName(argv[1]);

	typedef itk::DiscreteGaussianImageFilter<ImageType, ImageType> DiscreteGaussianFilterType;

	DiscreteGaussianFilterType::Pointer discreteGaussian = DiscreteGaussianFilterType::New();
	discreteGaussian->SetInput(reader->GetOutput());

	int discreteGaussianVariance = 4;
	int discreteGaussianMaximumKernelWidth = 3;

	discreteGaussian->SetVariance(discreteGaussianVariance);
	discreteGaussian->SetMaximumKernelWidth(discreteGaussianMaximumKernelWidth);
	discreteGaussian->Update();

	typedef itk::BinomialBlurImageFilter<ImageType, ImageType> BinomialBlurFilterType;
	
	BinomialBlurFilterType::Pointer binomialBlur = BinomialBlurFilterType::New();
	binomialBlur->SetInput(reader->GetOutput());

	int binomialBlurRepetitions = 5;

	binomialBlur->SetRepetitions(binomialBlurRepetitions);
	binomialBlur->Update();

	typedef itk::RecursiveGaussianImageFilter<ImageType, ImageType> RecursiveGaussianFilterType;
	
	RecursiveGaussianFilterType::Pointer filterX = RecursiveGaussianFilterType::New();
	RecursiveGaussianFilterType::Pointer filterY = RecursiveGaussianFilterType::New();

	filterX->SetDirection(0);
	filterY->SetDirection(1);

	filterX->SetOrder(RecursiveGaussianFilterType::ZeroOrder);
	filterY->SetOrder(RecursiveGaussianFilterType::ZeroOrder);

	filterX->SetNormalizeAcrossScale(false);
	filterY->SetNormalizeAcrossScale(false);

	filterX->SetInput(reader->GetOutput());
	filterY->SetInput(filterX->GetOutput());

	int sigma = 3;

	filterX->SetSigma(sigma);
	filterY->SetSigma(sigma);

	filterY->Update();

	QuickView viewer;
	viewer.SetNumberOfColumns(5);

	string description;

	description = "Original";
	viewer.AddImage(reader->GetOutput(), true, description);
	description = "Discrete Gaussian\nVariance = " + to_string(discreteGaussianVariance) + ", Maximum Kernel = " + to_string(discreteGaussianMaximumKernelWidth);
	viewer.AddImage(discreteGaussian->GetOutput(), true, description);
	description = "Binomial Blur\nRepetitions = " + to_string(binomialBlurRepetitions);
	viewer.AddImage(binomialBlur->GetOutput(), true, description);
	description = "Recursive Gaussian X\nSigma = " + to_string(sigma);
	viewer.AddImage(filterX->GetOutput(), true, description);
	description = "Recursive Gaussian XY\nSigma = " + to_string(sigma);
	viewer.AddImage(filterY->GetOutput(), true, description);
	viewer.Visualize();
	
	return EXIT_SUCCESS;
}