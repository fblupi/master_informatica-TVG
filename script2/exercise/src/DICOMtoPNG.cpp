#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkImage.h"
#include "itkGDCMImageIO.h"
#include "itkPNGImageIO.h"

using namespace std;

int main (int argc, char ** argv)
{
	if (argc < 3) {
		cerr << "Usage: " << endl;
		cerr << argv[0] << " inputImageFile  outputImageFile " << endl;
		return EXIT_FAILURE;
	}

	typedef unsigned char PixelType;
	const unsigned int Dimension = 2;
	typedef itk::Image<PixelType, Dimension> ImageType;

	typedef itk::ImageFileReader<ImageType> ReaderType;
	ReaderType::Pointer reader = ReaderType::New();
	reader->SetFileName(argv[1]);

	typedef itk::GDCMImageIO ImageIOTypeInput;
	ImageIOTypeInput::Pointer gdcmImageIO = ImageIOTypeInput::New();
	reader->SetImageIO(gdcmImageIO);

	try {
		reader->Update();
	} catch (itk::ExceptionObject & err) {
		cerr << "ExceptionObject caught !" << endl;
		cerr << err << std::endl;
		return EXIT_FAILURE;
	}

	typedef itk::ImageFileWriter<ImageType> WriterType;
	WriterType::Pointer writer = WriterType::New();
	writer->SetFileName(argv[2]);
	writer->SetInput(reader->GetOutput());

	typedef itk::PNGImageIO ImageIOTypeOutput;
	ImageIOTypeOutput::Pointer pngImageIO = ImageIOTypeOutput::New();
	writer->SetImageIO(pngImageIO);

	try {
		writer->Update();
	}
	catch (itk::ExceptionObject & err) {
		cerr << "ExceptionObject caught !" << endl;
		cerr << err << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
