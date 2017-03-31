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
	discreteGaussian->SetVariance(4);
	discreteGaussian->SetMaximumKernelWidth(9);
	discreteGaussian->Update();

	typedef itk::BinomialBlurImageFilter<ImageType, ImageType> BinomialBlurFilterType;
	
	BinomialBlurFilterType::Pointer binomialBlur = BinomialBlurFilterType::New();
	binomialBlur->SetInput(reader->GetOutput());
	binomialBlur->SetRepetitions(5);
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

	filterX->SetSigma(3);
	filterY->SetSigma(3);

	filterY->Update();

	QuickView viewer;
	viewer.SetNumberOfColumns(5);
	viewer.AddImage(reader->GetOutput());
	viewer.AddImage(discreteGaussian->GetOutput());
	viewer.AddImage(binomialBlur->GetOutput());
	viewer.AddImage(filterX->GetOutput());
	viewer.AddImage(filterY->GetOutput());
	viewer.Visualize();
	
	return EXIT_SUCCESS;
}