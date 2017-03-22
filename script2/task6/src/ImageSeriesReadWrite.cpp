#include "itkImage.h"
#include "itkImageSeriesReader.h"
#include "itkImageFileWriter.h"
#include "itkNumericSeriesFileNames.h"
#include "itkBMPImageIO.h"

using namespace std;

int main(int argc, char ** argv)
{
	if (argc < 4) {
		cerr << "Usage: " << endl;
		cerr << argv[0] << " firstSliceValue lastSliceValue outputImageFile " << endl;
		return EXIT_FAILURE;
	}

	typedef unsigned char PixelType;
	const unsigned int Dimension = 3;

	typedef itk::Image<PixelType, Dimension> ImageType;

	typedef itk::ImageSeriesReader<ImageType> ReaderType;
	typedef itk::ImageFileWriter<ImageType> WriterType;

	ReaderType::Pointer reader = ReaderType::New();
	WriterType::Pointer writer = WriterType::New();


	const unsigned int first = atoi(argv[1]);
	const unsigned int last = atoi(argv[2]);

	const char * outputFilename = argv[3];

	typedef itk::NumericSeriesFileNames NameGeneratorType;

	NameGeneratorType::Pointer nameGenerator = NameGeneratorType::New();

	nameGenerator->SetSeriesFormat("t%d.bmp");

	nameGenerator->SetStartIndex(first);
	nameGenerator->SetEndIndex(last);
	nameGenerator->SetIncrementIndex(1);

	reader->SetImageIO(itk::BMPImageIO::New());

	reader->SetFileNames(nameGenerator->GetFileNames());

	writer->SetFileName(outputFilename);

	writer->SetInput(reader->GetOutput());

	try {
		writer->Update();
	}
	catch (itk::ExceptionObject & err) {
		cerr << "ExceptionObject caught !" << endl;
		cerr << err << endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
