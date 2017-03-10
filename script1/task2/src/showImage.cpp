#include "itkImage.h"
#include "itkImageFileReader.h"
#include "QuickView.h"
#include "itkShrinkImageFilter.h"

using namespace std;

int main( int argc, char* argv[])
{
	// Check arguments
	if (argc < 2 || argc > 2) {
		cerr << "Usage: " << argv[0] << " <ImageFileName>" << endl;
		return EXIT_FAILURE;
	}

	// Define the image type
	typedef itk::Image<unsigned char, 2> ImageType;

	// Define the reader type for the ImageType
	typedef itk::ImageFileReader<ImageType> ReaderType;

	// Instantiate an object of type ReaderType
	ReaderType::Pointer reader= ReaderType::New();
	reader->SetFileName(argv[1]);

	// Send an update message to reader in order to the pipeline executes.
	try {
		reader->Update();
	}
		catch (itk::ExceptionObject & error){
		cerr << "Error: " << error << endl;
		return EXIT_FAILURE;
	}

	// Define the shrink filter type
	typedef itk::ShrinkImageFilter <ImageType, ImageType> ShrinkImageFilterType;
	
	// Instantiate an object of type shrink image filter
	ShrinkImageFilterType::Pointer shrinkFilter = ShrinkImageFilterType::New();
	shrinkFilter->SetInput(reader->GetOutput());
	shrinkFilter->SetShrinkFactors(2);
	shrinkFilter->Update();

	// User QuickView to show the images
	QuickView viewer;
	viewer.AddImage(reader->GetOutput());
	viewer.AddImage(shrinkFilter->GetOutput());
	viewer.Visualize();

	return EXIT_SUCCESS;
}