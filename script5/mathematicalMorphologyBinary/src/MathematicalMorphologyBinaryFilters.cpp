#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"

#include "itkBinaryErodeImageFilter.h"
#include "itkBinaryDilateImageFilter.h"
#include "itkBinaryBallStructuringElement.h"
#include "itkBinaryThresholdImageFilter.h"

#include "QuickView.h"

using namespace std;

int main(int argc, char * argv[])
{
	if (argc < 4) {
		cerr << "Usage: " << endl;
		cerr << argv[0] << "  inputImageFile lowerThreshold upperThreshold " << endl;
		return EXIT_FAILURE;
	}

	const unsigned int Dimension = 2;

	typedef unsigned char InputPixelType;
	typedef unsigned char OutputPixelType;

	typedef itk::Image<InputPixelType, Dimension> InputImageType;
	typedef itk::Image<OutputPixelType, Dimension> OutputImageType;

	typedef itk::ImageFileReader<InputImageType> ReaderType;
	typedef itk::BinaryThresholdImageFilter<InputImageType, InputImageType> ThresholdFilterType;
	typedef itk::BinaryBallStructuringElement<InputPixelType, Dimension> StructuringElementType;
	typedef itk::BinaryErodeImageFilter<InputImageType, OutputImageType, StructuringElementType> ErodeFilterType;
	typedef itk::BinaryDilateImageFilter<InputImageType, OutputImageType, StructuringElementType> DilateFilterType;

	ReaderType::Pointer reader = ReaderType::New();

	ThresholdFilterType::Pointer thresholder = ThresholdFilterType::New();

	ErodeFilterType::Pointer binaryErode = ErodeFilterType::New();
	DilateFilterType::Pointer binaryDilate = DilateFilterType::New();

	StructuringElementType  structuringElement;

	structuringElement.SetRadius(1);  // 3x3 structuring element

	structuringElement.CreateStructuringElement();

	binaryErode->SetKernel(structuringElement);
	binaryDilate->SetKernel(structuringElement);

	reader->SetFileName(argv[1]);

	const InputPixelType lowerThreshold = atoi(argv[2]);
	const InputPixelType upperThreshold = atoi(argv[3]);

	thresholder->SetInput(reader->GetOutput());

	InputPixelType background = 0;
	InputPixelType foreground = 255;

	thresholder->SetOutsideValue(background);
	thresholder->SetInsideValue(foreground);

	thresholder->SetLowerThreshold(lowerThreshold);
	thresholder->SetUpperThreshold(upperThreshold);

	binaryErode->SetInput(thresholder->GetOutput());
	binaryDilate->SetInput(thresholder->GetOutput());

	binaryErode->SetErodeValue(foreground);
	binaryDilate->SetDilateValue(foreground);

	QuickView viewer;
	viewer.SetNumberOfColumns(3);

	string description;

	description = "Dilate\nLower: " + to_string(lowerThreshold) + ", Upper: " + to_string(upperThreshold);
	viewer.AddImage(binaryDilate->GetOutput(), true, description);
	description = "Erode\nLower: " + to_string(lowerThreshold) + ", Upper: " + to_string(upperThreshold);
	viewer.AddImage(binaryErode->GetOutput(), true, description);
	description = "Original";
	viewer.AddImage(reader->GetOutput(), true, description);
	viewer.Visualize();

	return EXIT_SUCCESS;
}
