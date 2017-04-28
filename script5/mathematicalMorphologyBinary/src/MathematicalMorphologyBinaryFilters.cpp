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

	const InputPixelType lowerThreshold = atoi(argv[2]);
	const InputPixelType upperThreshold = atoi(argv[3]);
	InputPixelType background = 0;
	InputPixelType foreground = 255;

	typedef itk::Image<InputPixelType, Dimension> InputImageType;
	typedef itk::Image<OutputPixelType, Dimension> OutputImageType;

	typedef itk::ImageFileReader<InputImageType> ReaderType;
	typedef itk::BinaryThresholdImageFilter<InputImageType, InputImageType> ThresholdFilterType;
	typedef itk::BinaryBallStructuringElement<InputPixelType, Dimension> StructuringElementType;
	typedef itk::BinaryErodeImageFilter<InputImageType, OutputImageType, StructuringElementType> ErodeFilterType;
	typedef itk::BinaryDilateImageFilter<InputImageType, OutputImageType, StructuringElementType> DilateFilterType;

	ReaderType::Pointer reader = ReaderType::New();
	reader->SetFileName(argv[1]);

	ThresholdFilterType::Pointer thresholder = ThresholdFilterType::New();
	thresholder->SetInput(reader->GetOutput());

	thresholder->SetOutsideValue(background);
	thresholder->SetInsideValue(foreground);

	thresholder->SetLowerThreshold(lowerThreshold);
	thresholder->SetUpperThreshold(upperThreshold);

	ErodeFilterType::Pointer binaryErode = ErodeFilterType::New();
	binaryErode->SetInput(thresholder->GetOutput());
	DilateFilterType::Pointer binaryDilate = DilateFilterType::New();
	binaryDilate->SetInput(thresholder->GetOutput());

	StructuringElementType structuringElement;
	structuringElement.SetRadius(1);  // 3x3 structuring element
	structuringElement.CreateStructuringElement();

	binaryErode->SetKernel(structuringElement);
	binaryErode->SetErodeValue(foreground);

	binaryDilate->SetKernel(structuringElement);
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
