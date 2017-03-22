#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkDiscreteGaussianImageFilter.h"
#include "itkBinomialBlurImageFilter.h"

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

	QuickView viewer;
	viewer.SetNumberOfColumns(4);
	viewer.AddImage(reader->GetOutput());
	viewer.AddImage(discreteGaussian->GetOutput());
	viewer.AddImage(binomialBlur->GetOutput());
	viewer.Visualize();
	
	return EXIT_SUCCESS;
}