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

	binaryThresholdFilter->SetOutsideValue(0);
	binaryThresholdFilter->SetInsideValue(255);
	binaryThresholdFilter->SetLowerThreshold(150);
	binaryThresholdFilter->SetUpperThreshold(180);

	binaryThresholdFilter->Update();

	typedef itk::ThresholdImageFilter<ImageType> ThresholdFilterType;
	ThresholdFilterType::Pointer thresholdFilter = ThresholdFilterType::New();
	thresholdFilter->SetInput(reader->GetOutput());

	thresholdFilter->SetOutsideValue(0);
	thresholdFilter->ThresholdBelow(180);

	thresholdFilter->Update();

	QuickView viewer;
	viewer.SetNumberOfColumns(3);
	viewer.AddImage(reader->GetOutput());
	viewer.AddImage(binaryThresholdFilter->GetOutput());
	viewer.AddImage(thresholdFilter->GetOutput());
	viewer.Visualize();
	
	return EXIT_SUCCESS;
}