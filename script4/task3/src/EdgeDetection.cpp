#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkMedianImageFilter.h"
#include "itkCannyEdgeDetectionImageFilter.h"

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

	typedef itk::CannyEdgeDetectionImageFilter<ImageType, ImageType> CannyEdgeDetectionFilterType;
	CannyEdgeDetectionFilterType::Pointer cannyEdgeDetectionFilterNoFiltered = CannyEdgeDetectionFilterType::New();

	float variance = 1;
	float upper = 5;
	float lower = 0;

	cannyEdgeDetectionFilterNoFiltered->SetInput(reader->GetOutput());
	cannyEdgeDetectionFilterNoFiltered->SetVariance(variance);
	cannyEdgeDetectionFilterNoFiltered->SetUpperThreshold(upper);
	cannyEdgeDetectionFilterNoFiltered->SetLowerThreshold(lower);

	typedef itk::MedianImageFilter<ImageType, ImageType> MedianFilterType;
	MedianFilterType::Pointer median = MedianFilterType::New();

	ImageType::SizeType indexRadius;
	indexRadius[0] = 1;
	indexRadius[1] = 1;

	median->SetInput(reader->GetOutput());
	median->SetRadius(indexRadius);

	CannyEdgeDetectionFilterType::Pointer cannyEdgeDetectionFilterFiltered = CannyEdgeDetectionFilterType::New();

	cannyEdgeDetectionFilterFiltered->SetInput(median->GetOutput());
	cannyEdgeDetectionFilterFiltered->SetVariance(variance);
	cannyEdgeDetectionFilterFiltered->SetUpperThreshold(upper);
	cannyEdgeDetectionFilterFiltered->SetLowerThreshold(lower);

	QuickView viewer;
	viewer.SetNumberOfColumns(5);

	string description;

	description = "Original";
	viewer.AddImage(reader->GetOutput(), true, description);
	description = "Canny No Filtered\nVariance = " + to_string(variance) + ", Upper = " + to_string(upper) + ", Lower = " + to_string(lower);
	viewer.AddImage(cannyEdgeDetectionFilterNoFiltered->GetOutput(), true, description);
	description = "Canny Filtered\nVariance = " + to_string(variance) + ", Upper = " + to_string(upper) + ", Lower = " + to_string(lower);
	viewer.AddImage(cannyEdgeDetectionFilterFiltered->GetOutput(), true, description);
	viewer.Visualize();
	
	return EXIT_SUCCESS;
}