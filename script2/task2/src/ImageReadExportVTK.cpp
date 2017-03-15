#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkVTKImageIO.h"
#include "itkImage.h"

using namespace std;

int main (int argc, char ** argv)
{
	if (argc < 3) {
		cerr << "Usage: " << endl;
		cerr << argv[0] << " inputImageFile  outputImageFile " << endl;
		return EXIT_FAILURE;
	}

	typedef unsigned short PixelType;
	const unsigned int Dimension = 2;
	typedef itk::Image<PixelType, Dimension> ImageType;

	typedef itk::ImageFileReader<ImageType> ReaderType;
	typedef itk::ImageFileWriter<ImageType> WriterType;
	typedef itk::VTKImageIO ImageIOType;

	ReaderType::Pointer reader = ReaderType::New();
	WriterType::Pointer writer = WriterType::New();
	ImageIOType::Pointer vtkIO = ImageIOType::New();

	const char * inputFilename  = argv[1];
	const char * outputFilename = argv[2];

	reader->SetFileName(inputFilename);
	writer->SetFileName(outputFilename);

	writer->SetInput(reader->GetOutput());

	vtkIO->SetFileTypeToASCII();

	writer->SetImageIO(vtkIO);

	try {
		writer->Update();
	} catch (itk::ExceptionObject & err) {
		cerr << "ExceptionObject caught !" << endl;
		cerr << err << endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
