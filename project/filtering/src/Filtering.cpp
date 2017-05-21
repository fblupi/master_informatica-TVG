#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkBinomialBlurImageFilter.h"

#include "QuickView.h"

using namespace std;

int main(int argc, char * argv[])
{
	if (argc < 3) {
		cerr << "Usage: " << endl;
		cerr << argv[0] << " inputImageFile repetitions" << endl;
		return EXIT_FAILURE;
	}

	typedef float PixelType;
	const unsigned int Dimension = 2;

	typedef itk::Image<PixelType, Dimension> ImageType;

	typedef itk::ImageFileReader<ImageType> ReaderType;

	ReaderType::Pointer reader = ReaderType::New();
	reader->SetFileName(argv[1]);

	typedef itk::BinomialBlurImageFilter<ImageType, ImageType> BinomialBlurFilterType;
	
	BinomialBlurFilterType::Pointer binomialBlur = BinomialBlurFilterType::New();
	binomialBlur->SetInput(reader->GetOutput());

	int binomialBlurRepetitions = atoi(argv[2]);

	binomialBlur->SetRepetitions(binomialBlurRepetitions);
	binomialBlur->Update();

	QuickView viewer;
	viewer.SetNumberOfColumns(2);

	string description;

	description = "Original";
	viewer.AddImage(reader->GetOutput(), true, description);
	description = "Binomial Blur\nRepetitions = " + to_string(binomialBlurRepetitions);
	viewer.AddImage(binomialBlur->GetOutput(), true, description);
	viewer.Visualize();
	
	return EXIT_SUCCESS;
}