#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkRescaleIntensityImageFilter.h"
#include "itkImage.h"

using namespace std;

int main (int argc, char ** argv)
{
	if (argc < 3) {
		cerr << "Usage: " << endl;
		cerr << argv[0] << " inputImageFile  outputImageFile " << endl;
		return EXIT_FAILURE;
	}

	typedef float InputPixelType;
	typedef unsigned char OutputPixelType;
	const unsigned int Dimension = 2;

	typedef itk::Image<InputPixelType, Dimension> InputImageType;
	typedef itk::Image<OutputPixelType, Dimension> OutputImageType;

	typedef itk::ImageFileReader<InputImageType> ReaderType;
	typedef itk::ImageFileWriter<OutputImageType> WriterType;

	typedef itk::RescaleIntensityImageFilter<InputImageType, OutputImageType> FilterType;

	FilterType::Pointer filter = FilterType::New();
	filter->SetOutputMinimum(0);
	filter->SetOutputMaximum(255);

	ReaderType::Pointer reader = ReaderType::New();
	WriterType::Pointer writer = WriterType::New();

	filter->SetInput(reader->GetOutput());
	writer->SetInput(filter->GetOutput());

	const char * inputFilename = argv[1];
	const char * outputFilename = argv[2];

	reader->SetFileName(inputFilename);
	writer->SetFileName(outputFilename);

	try {
		writer->Update();
	} catch (itk::ExceptionObject & err) {
		cerr << "ExceptionObject caught !" << endl;
		cerr << err << endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
