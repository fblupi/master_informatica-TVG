#include "itkRGBPixel.h"
#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"

using namespace std;

int main (int argc, char ** argv)
{
	if (argc < 3) {
		cerr << "Usage: " << endl;
		cerr << argv[0] << " inputRGBImageFile  outputRGBImageFile " << endl;
		return EXIT_FAILURE;
	}

	typedef itk::RGBPixel<unsigned char> PixelType;
	typedef itk::Image<PixelType, 2> ImageType;

	typedef itk::ImageFileReader<ImageType> ReaderType;
	typedef itk::ImageFileWriter<ImageType> WriterType;

	ReaderType::Pointer reader = ReaderType::New();
	WriterType::Pointer writer = WriterType::New();

	const char * inputFilename = argv[1];
	const char * outputFilename = argv[2];

	reader->SetFileName(inputFilename);
	writer->SetFileName(outputFilename);

	ImageType::Pointer image = reader->GetOutput();
	writer->SetInput(image);

	writer->Update();

	return EXIT_SUCCESS;
}
