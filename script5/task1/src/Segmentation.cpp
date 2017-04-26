#include "itkImage.h"
#include "itkImageFileReader.h"

#include "itkConnectedThresholdImageFilter.h"
#include "itkMedianImageFilter.h"

#include "QuickView.h"

using namespace std;

int main (int argc, char * argv[])
{
	if (argc < 6) {
		cerr << "Usage: " << endl;
		cerr << argv[0] << "   inputImageFile seedX seedY lowerThreshold upperThreshold " << endl;
		return EXIT_FAILURE;
	}

	typedef float InputPixelType;
	typedef float OutputPixelType;

	typedef itk::Image<InputPixelType, 2> InputImageType;
	typedef itk::Image<OutputPixelType, 2> OutputImageType;

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

	QuickView viewer;
	viewer.SetNumberOfColumns(3);

	string description;

	description = "Original";
	viewer.AddImage(reader->GetOutput(), true, description);
	description = "Connected Threshold Image Filter \nLower: " + to_string(lowerThreshold) + ", Upper: " + to_string(upperThreshold);
	viewer.AddImage(connectedThreshold->GetOutput(), true, description);
	description = "Connected Threshold Image Filter Filtered \nLower: " + to_string(lowerThreshold) + ", Upper: " + to_string(upperThreshold);
	viewer.AddImage(connectedThresholdFiltered->GetOutput(), true, description);
	description = "Neigborhood Connected Image Filter";
	description = "Neigborhood Connected Image Filter Filtered";
	description = "Confidence Connected Image Filter";
	description = "Confidence Connected Image Filter Filtered";
	viewer.Visualize();

	return EXIT_SUCCESS;
}
