#include "itkImage.h"
#include "itkImageFileReader.h"

#include "itkBinaryThresholdImageFilter.h"
#include "itkThresholdImageFilter.h"

#include "QuickView.h"

using namespace std;

int main(int argc, char * argv[])
{
	if (argc < 2) {
		cerr << "Usage: " << endl;
		cerr << argv[0] << " inputImageFile" << endl;
		return EXIT_FAILURE;
	}

	typedef unsigned char PixelType;
	const unsigned int Dimension = 2;

	typedef itk::Image<PixelType, Dimension> ImageType;

	typedef itk::ImageFileReader<ImageType> ReaderType;
	ReaderType::Pointer reader = ReaderType::New();
	reader->SetFileName(argv[1]);

	typedef itk::BinaryThresholdImageFilter<ImageType, ImageType> BinaryThresholdFilterType;
	BinaryThresholdFilterType::Pointer binaryThresholdFilter = BinaryThresholdFilterType::New();
	binaryThresholdFilter->SetInput(reader->GetOutput());

	int outside = 0;
	int inside = 255;
	int lower = 150;
	int upper = 180;
	binaryThresholdFilter->SetOutsideValue(outside);
	binaryThresholdFilter->SetInsideValue(inside);
	binaryThresholdFilter->SetLowerThreshold(lower);
	binaryThresholdFilter->SetUpperThreshold(upper);

	binaryThresholdFilter->Update();

	typedef itk::ThresholdImageFilter<ImageType> ThresholdFilterType;
	ThresholdFilterType::Pointer thresholdFilter = ThresholdFilterType::New();
	thresholdFilter->SetInput(reader->GetOutput());

	int below = 180;
	thresholdFilter->SetOutsideValue(outside);
	thresholdFilter->ThresholdBelow(below);

	thresholdFilter->Update();

	QuickView viewer;
	viewer.SetNumberOfColumns(3);

	string description;

	description = "Original";
	viewer.AddImage(reader->GetOutput(), true, description);
	description = "Binary Threshold\nOutside = " + to_string(outside) + ", Inside = " + to_string(inside) + ", Lower = " + to_string(lower) + ", Upper = " + to_string(upper);
	viewer.AddImage(binaryThresholdFilter->GetOutput(), true, description);
	description = "Threshold\nOutside = " + to_string(outside) + ", Below = " + to_string(below);
	viewer.AddImage(thresholdFilter->GetOutput(), true, description);
	viewer.Visualize();
	
	return EXIT_SUCCESS;
}