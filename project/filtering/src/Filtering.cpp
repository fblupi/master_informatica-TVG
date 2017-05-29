#include <itkImage.h>
#include <itkImageFileReader.h>
#include <itkBinomialBlurImageFilter.h>
#include <itkThresholdImageFilter.h>

#include <QuickView.h>

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

	typedef itk::BinomialBlurImageFilter<ImageType, ImageType> BinomialBlurFilterType;
	BinomialBlurFilterType::Pointer binomialBlur = BinomialBlurFilterType::New();
	binomialBlur->SetInput(reader->GetOutput());
	binomialBlur->SetRepetitions(8);
	binomialBlur->Update();

	typedef itk::ThresholdImageFilter<ImageType> ThresholdImageFilterType;
	ThresholdImageFilterType::Pointer segmentator = ThresholdImageFilterType::New();
	segmentator->SetInput(binomialBlur->GetOutput());
	segmentator->SetOutsideValue(0);
	segmentator->ThresholdOutside(50, 200);

	QuickView viewer;
	viewer.SetNumberOfColumns(2);

	string description;
	description = "Original";
	viewer.AddImage(reader->GetOutput(), true, description);
	description = "Filtered";
	viewer.AddImage(segmentator->GetOutput(), true, description);
	viewer.Visualize();
	
	return EXIT_SUCCESS;
}