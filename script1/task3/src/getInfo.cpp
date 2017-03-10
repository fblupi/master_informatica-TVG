#include "itkImage.h"
#include "itkImageFileReader.h"
#include "QuickView.h"

using namespace std;

int main(int argc, char* argv[])
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
	ReaderType::Pointer reader = ReaderType::New();
	reader->SetFileName(argv[1]);

	// Send an update message to reader in order to the pipeline executes.
	try {
		reader->Update();
	}
	catch (itk::ExceptionObject & error) {
		cerr << "Error: " << error << endl;
		return EXIT_FAILURE;
	}

	// Get size of each dimension
	const ImageType::SizeType & size = reader->GetOutput()->GetLargestPossibleRegion().GetSize();
	cout << "Size = ";
	cout << size << endl;

	// Get origin
	const ImageType::PointType & origin = reader->GetOutput()->GetOrigin();
	cout << "Origin = ";
	cout << origin[0] << ", "
		<< origin[1] << ", "
		<< origin[2] << endl;

	// Get spacing
	const ImageType::SpacingType & sp = reader->GetOutput()->GetSpacing();
	cout << "Spacing = ";
	cout << sp[0] << ", " << sp[1] << ", " << sp[2] << endl;

	// Get direction
	const ImageType::DirectionType & direct = reader->GetOutput()->GetDirection();
	cout << "Direction = ";
	cout << direct << endl;

	// User QuickView to show the images
	QuickView viewer;
	viewer.AddImage(reader->GetOutput());
	viewer.Visualize();

	return EXIT_SUCCESS;
}