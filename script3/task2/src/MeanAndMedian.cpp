#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkMeanImageFilter.h"
#include "itkMedianImageFilter.h"

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

	typedef itk::MeanImageFilter<ImageType, ImageType> MeanFilterType;
	typedef itk::MedianImageFilter<ImageType, ImageType> MedianFilterType;

	ImageType::SizeType indexRadius3;
	indexRadius3[0] = 1;
	indexRadius3[1] = 1;

	ImageType::SizeType indexRadius5;
	indexRadius5[0] = 2;
	indexRadius5[1] = 2;

	ImageType::SizeType indexRadius7;
	indexRadius7[0] = 3;
	indexRadius7[1] = 3;

	MeanFilterType::Pointer mean3 = MeanFilterType::New();
	mean3->SetInput(reader->GetOutput());
	mean3->SetRadius(indexRadius3);

	MeanFilterType::Pointer mean5 = MeanFilterType::New();
	mean5->SetInput(reader->GetOutput());
	mean5->SetRadius(indexRadius5);

	MeanFilterType::Pointer mean7 = MeanFilterType::New();
	mean7->SetInput(reader->GetOutput());
	mean7->SetRadius(indexRadius7);

	MedianFilterType::Pointer median3 = MedianFilterType::New();
	median3->SetInput(reader->GetOutput());
	median3->SetRadius(indexRadius3);

	MedianFilterType::Pointer median5 = MedianFilterType::New();
	median5->SetInput(reader->GetOutput());
	median5->SetRadius(indexRadius5);

	MedianFilterType::Pointer median7 = MedianFilterType::New();
	median7->SetInput(reader->GetOutput());
	median7->SetRadius(indexRadius7);

	QuickView viewer;
	viewer.SetNumberOfColumns(3);

	string description;

	description = "Mean\nRadius = 3";
	viewer.AddImage(mean3->GetOutput(), true, description.c_str());
	description = "Mean\nRadius = 5";
	viewer.AddImage(mean5->GetOutput(), true, description.c_str());
	description = "Mean\nRadius = 7";
	viewer.AddImage(mean7->GetOutput(), true, description.c_str());
	description = "Median\nRadius = 3";
	viewer.AddImage(median3->GetOutput(), true, description.c_str());
	description = "Median\nRadius = 5";
	viewer.AddImage(median5->GetOutput(), true, description.c_str());
	description = "Median\nRadius = 3";
	viewer.AddImage(median7->GetOutput(), true, description.c_str());
	description = "Original";
	viewer.AddImage(reader->GetOutput(), true, description.c_str());
	viewer.Visualize();
	
	return EXIT_SUCCESS;
}