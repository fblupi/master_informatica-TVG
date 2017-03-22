#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkDiscreteGaussianImageFilter.h"

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

	typedef itk::DiscreteGaussianImageFilter<ImageType, ImageType> DiscreteGaussianImageFilter;

	DiscreteGaussianImageFilter::Pointer discreteGaussian = DiscreteGaussianImageFilter::New();
	discreteGaussian->SetInput(reader->GetOutput());
	discreteGaussian->SetVariance(4);
	discreteGaussian->SetMaximumKernelWidth(9);
	discreteGaussian->Update();

	QuickView viewer;
	viewer.SetNumberOfColumns(4);
	viewer.AddImage(reader->GetOutput());
	viewer.AddImage(discreteGaussian->GetOutput());
	viewer.Visualize();
	
	return EXIT_SUCCESS;
}