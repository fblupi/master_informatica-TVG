#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"

#include "itkGrayscaleErodeImageFilter.h"
#include "itkGrayscaleDilateImageFilter.h"
#include "itkBinaryBallStructuringElement.h"

#include "QuickView.h"

using namespace std;

int main(int argc, char * argv[])
{
	if(argc < 2) {
		cerr << "Usage: " << endl;
		cerr << argv[0] << "  inputImageFile  " << endl;
		return EXIT_FAILURE;
	}

	const unsigned int Dimension = 2;

	typedef unsigned char InputPixelType;
	typedef unsigned char OutputPixelType;

	typedef itk::Image<InputPixelType, Dimension> InputImageType;
	typedef itk::Image<OutputPixelType, Dimension> OutputImageType;

	typedef itk::ImageFileReader<InputImageType> ReaderType;
	typedef itk::ImageFileWriter<OutputImageType> WriterType;
	typedef itk::BinaryBallStructuringElement<InputPixelType, Dimension> StructuringElementType;
	typedef itk::GrayscaleErodeImageFilter<InputImageType, OutputImageType, StructuringElementType> ErodeFilterType;
	typedef itk::GrayscaleDilateImageFilter<InputImageType, OutputImageType, StructuringElementType> DilateFilterType;

	ReaderType::Pointer reader = ReaderType::New();
	reader->SetFileName(argv[1]);

	ErodeFilterType::Pointer grayscaleErode = ErodeFilterType::New();
	grayscaleErode->SetInput(reader->GetOutput());

	DilateFilterType::Pointer grayscaleDilate = DilateFilterType::New();
	grayscaleDilate->SetInput(reader->GetOutput());

	StructuringElementType structuringElement;
	structuringElement.SetRadius(1);  // 3x3 structuring element
	structuringElement.CreateStructuringElement();

	grayscaleErode->SetKernel(structuringElement);
	grayscaleDilate->SetKernel(structuringElement);

	QuickView viewer;
	viewer.SetNumberOfColumns(3);

	string description;

	description = "Dilate";
	viewer.AddImage(grayscaleDilate->GetOutput(), true, description);
	description = "Erode";
	viewer.AddImage(grayscaleErode->GetOutput(), true, description);
	description = "Original";
	viewer.AddImage(reader->GetOutput(), true, description);
	viewer.Visualize();

	return EXIT_SUCCESS;
}
