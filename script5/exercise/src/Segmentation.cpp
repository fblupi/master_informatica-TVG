#include "itkImage.h"
#include "itkImageFileReader.h"

#include "itkMedianImageFilter.h"
#include "itkConnectedThresholdImageFilter.h"
#include "itkNeighborhoodConnectedImageFilter.h"
#include "itkConfidenceConnectedImageFilter.h"

#include "itkBinaryErodeImageFilter.h"
#include "itkBinaryDilateImageFilter.h"
#include "itkBinaryBallStructuringElement.h"

#include "QuickView.h"

#define MATH 1

using namespace std;

int main (int argc, char * argv[])
{
	if (argc < 6) {
		cerr << "Usage: " << endl;
		cerr << argv[0] << "   inputImageFile seedX seedY lowerThreshold upperThreshold " << endl;
		return EXIT_FAILURE;
	}

	// 91,118 210,255
	// 60,125 150,180
	// 191,110 0,150

	typedef float InputPixelType;
	typedef float OutputPixelType;

	typedef itk::Image<InputPixelType, 2> InputImageType;
	typedef itk::Image<OutputPixelType, 2> OutputImageType;

	typedef itk::BinaryBallStructuringElement<InputPixelType, 2> StructuringElementType;
	typedef itk::BinaryErodeImageFilter<InputImageType, OutputImageType, StructuringElementType> ErodeFilterType;
	typedef itk::BinaryDilateImageFilter<InputImageType, OutputImageType, StructuringElementType> DilateFilterType;

	int seedX = atoi(argv[2]);
	int seedY = atoi(argv[3]);
	float lowerThreshold = atof(argv[4]);
	float upperThreshold = atof(argv[5]);

	InputImageType::IndexType index;
	index[0] = seedX;
	index[1] = seedY;

	typedef itk::ImageFileReader<InputImageType> ReaderType;
	ReaderType::Pointer reader = ReaderType::New();
	reader->SetFileName(argv[1]);

	typedef itk::MedianImageFilter<InputImageType, InputImageType> MedianImageFilterType;
	MedianImageFilterType::Pointer filter = MedianImageFilterType::New();
	filter->SetInput(reader->GetOutput());

	typedef itk::ConnectedThresholdImageFilter<InputImageType, InputImageType> ConnectedFilterType;
	ConnectedFilterType::Pointer connectedThreshold = ConnectedFilterType::New();
	ConnectedFilterType::Pointer connectedThresholdFiltered = ConnectedFilterType::New();
	connectedThreshold->SetInput(reader->GetOutput());
	connectedThresholdFiltered->SetInput(filter->GetOutput());
	connectedThreshold->SetLower(lowerThreshold);
	connectedThresholdFiltered->SetLower(lowerThreshold);
	connectedThreshold->SetUpper(upperThreshold);
	connectedThresholdFiltered->SetUpper(upperThreshold);
	connectedThreshold->SetReplaceValue(255);
	connectedThresholdFiltered->SetReplaceValue(255);
	connectedThreshold->SetSeed(index);
	connectedThresholdFiltered->SetSeed(index);

	typedef itk::NeighborhoodConnectedImageFilter<InputImageType, InputImageType> NeighborhoodConnectedFilterType;
	NeighborhoodConnectedFilterType::Pointer neighborhoodConnected = NeighborhoodConnectedFilterType::New();
	NeighborhoodConnectedFilterType::Pointer neighborhoodConnectedFiltered = NeighborhoodConnectedFilterType::New();
	neighborhoodConnected->SetInput(reader->GetOutput());
	neighborhoodConnectedFiltered->SetInput(filter->GetOutput());
	neighborhoodConnected->SetLower(lowerThreshold);
	neighborhoodConnectedFiltered->SetLower(lowerThreshold);
	neighborhoodConnected->SetUpper(upperThreshold);
	neighborhoodConnectedFiltered->SetUpper(upperThreshold);
	neighborhoodConnected->SetReplaceValue(255);
	neighborhoodConnectedFiltered->SetReplaceValue(255);
	neighborhoodConnected->SetSeed(index);
	neighborhoodConnectedFiltered->SetSeed(index);

	unsigned int radius = 3;
	double multiplier = 3;
	unsigned int iters = 25;

	typedef itk::ConfidenceConnectedImageFilter<InputImageType, InputImageType> ConfidenceConnectedFilterType;
	ConfidenceConnectedFilterType::Pointer confidenceConnected = ConfidenceConnectedFilterType::New();
	ConfidenceConnectedFilterType::Pointer confidenceConnectedFiltered = ConfidenceConnectedFilterType::New();
	confidenceConnected->SetInput(reader->GetOutput());
	confidenceConnectedFiltered->SetInput(reader->GetOutput());
	confidenceConnected->SetInitialNeighborhoodRadius(radius);
	confidenceConnectedFiltered->SetInitialNeighborhoodRadius(radius);
	confidenceConnected->SetMultiplier(multiplier);
	confidenceConnectedFiltered->SetMultiplier(multiplier);
	confidenceConnected->SetNumberOfIterations(iters);
	confidenceConnectedFiltered->SetNumberOfIterations(iters);
	confidenceConnected->SetReplaceValue(255);
	confidenceConnectedFiltered->SetReplaceValue(255);
	confidenceConnected->SetSeed(index);
	confidenceConnectedFiltered->SetSeed(index);

	ErodeFilterType::Pointer binaryErode = ErodeFilterType::New();
	DilateFilterType::Pointer binaryDilate = DilateFilterType::New();
	StructuringElementType structuringElement;
	structuringElement.SetRadius(1); // 3x3 structuring element
	structuringElement.CreateStructuringElement();
	binaryDilate->SetKernel(structuringElement);
	binaryErode->SetKernel(structuringElement);

	binaryDilate->SetInput(confidenceConnectedFiltered->GetOutput());
	binaryErode->SetInput(binaryDilate->GetOutput());
	binaryDilate->SetDilateValue(255);
	binaryErode->SetErodeValue(255);
	binaryErode->SetBackgroundValue(0);

	QuickView viewer;
	viewer.SetNumberOfColumns(4);

	string description;

	description = "Connected Threshold Image Filter \nLower: " + to_string(lowerThreshold) + ", Upper: " + to_string(upperThreshold);
	viewer.AddImage(connectedThreshold->GetOutput(), true, description);
	description = "Connected Threshold Image Filter Filtered \nLower: " + to_string(lowerThreshold) + ", Upper: " + to_string(upperThreshold);
	viewer.AddImage(connectedThresholdFiltered->GetOutput(), true, description);
	description = "Neigborhood Connected Image Filter \nLower: " + to_string(lowerThreshold) + ", Upper: " + to_string(upperThreshold);
	viewer.AddImage(neighborhoodConnected->GetOutput(), true, description);
	description = "Neigborhood Connected Image Filter Filtered \nLower: " + to_string(lowerThreshold) + ", Upper: " + to_string(upperThreshold);
	viewer.AddImage(neighborhoodConnectedFiltered->GetOutput(), true, description);
	description = "Confidence Connected Image Filter \nRadius: " + to_string(radius) + ", Multiplier: " + to_string(multiplier) + ", Iters: " + to_string(iters);
	viewer.AddImage(confidenceConnected->GetOutput(), true, description);
	description = "Confidence Connected Image Filter Filtered \nRadius: " + to_string(radius) + ", Multiplier: " + to_string(multiplier) + ", Iters: " + to_string(iters);
#if MATH
	viewer.AddImage(binaryErode->GetOutput(), true, description);
# else
	viewer.AddImage(confidenceConnectedFiltered->GetOutput(), true, description);
#endif
	description = "Original";
	viewer.AddImage(reader->GetOutput(), true, description);
	viewer.Visualize();

	return EXIT_SUCCESS;
}
