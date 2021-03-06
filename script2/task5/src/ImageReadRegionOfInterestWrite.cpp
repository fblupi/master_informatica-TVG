#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkRegionOfInterestImageFilter.h"
#include "itkImage.h"

using namespace std;

int main (int argc, char ** argv)
{
	if (argc < 7) {
		cerr << "Usage: " << std::endl;
		cerr << argv[0] << " inputImageFile  outputImageFile " << endl;
		cerr << " startX startY sizeX sizeY" << endl;
		return EXIT_FAILURE;
	}

	typedef signed short InputPixelType;
	typedef signed short OutputPixelType;
	const unsigned int Dimension = 2;

	typedef itk::Image<InputPixelType, Dimension> InputImageType;
	typedef itk::Image<OutputPixelType, Dimension> OutputImageType;

	typedef itk::ImageFileReader<InputImageType> ReaderType;
	typedef itk::ImageFileWriter<OutputImageType> WriterType;

	typedef itk::RegionOfInterestImageFilter<InputImageType, OutputImageType> FilterType;

	FilterType::Pointer filter = FilterType::New();

	OutputImageType::IndexType start;
	start[0] = atoi(argv[3]);
	start[1] = atoi(argv[4]);

	OutputImageType::SizeType size;
	size[0] = atoi(argv[5]);
	size[1] = atoi(argv[6]);

	OutputImageType::RegionType desiredRegion;
	desiredRegion.SetSize(size );
	desiredRegion.SetIndex(start);

	filter->SetRegionOfInterest(desiredRegion);

	ReaderType::Pointer reader = ReaderType::New();
	WriterType::Pointer writer = WriterType::New();

	const char * inputFilename = argv[1];
	const char * outputFilename = argv[2];

	reader->SetFileName(inputFilename);
	writer->SetFileName(outputFilename);

	filter->SetInput(reader->GetOutput());
	writer->SetInput(filter->GetOutput());

	try {
		writer->Update();
	} catch (itk::ExceptionObject & err) {
		cerr << "ExceptionObject caught !" << endl;
		cerr << err << endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
