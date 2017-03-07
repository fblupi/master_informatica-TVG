#include "itkImage.h"
#include "itkRandomImageSource.h"
#include "itkImageRegionConstIterator.h"
#include "itkImageRegionIterator.h"

int main(int, char *[])
{
	// Create an instance of the Image class
	typedef float PixelType;
	typedef itk::Image<PixelType, 2> ImageType2D;

	// Declare a smart pointer to itk::RandomImageSource<Image2DType>
	itk::RandomImageSource<ImageType2D>::Pointer random = itk::RandomImageSource<ImageType2D>::New();

	// Set the minimum/maximum pixel value
	random->SetMin(0.0);
	random->SetMax(1.0);

	// Define and set the random image's size
	ImageType2D::SizeValueType size[2];
	size[0] = 20;
	size[1] = 20;
	random->SetSize(size);

	// Explicitly invoke the Update() method to update the pipeline
	random->Update();

	// Declare an smart pointer to point a new created object of type Image2DType
	ImageType2D::Pointer outputImage2D = ImageType2D::New();
	ImageType2D::Pointer inputImage2D = random->GetOutput();

	// Define where the image grid starts
	ImageType2D::IndexType region2DIndex;
	region2DIndex[0] = 0; // first coordinate on X in image space
	region2DIndex[1] = 0; // first coordinate on Y in image space

	// Define the number of pixels in each dimension
	ImageType2D::SizeType region2DSize;
	region2DSize[0] = 20; // number of pixels along X
	region2DSize[1] = 20; // number of pixels along Y

	// Create a region for the image from 'region2DIndex' and with 'region2DSize'
	ImageType2D::RegionType region2D;

	region2D.SetIndex(region2DIndex);
	region2D.SetSize(region2DSize);

	// Assign a valid region to the image and allocate memory
	outputImage2D->SetRegions(region2D);
	outputImage2D->Allocate();

	// Declare and define two new types of iterators across 'Image2DType'
	typedef itk::ImageRegionConstIterator<ImageType2D> ConstIterator2DType;
	typedef itk::ImageRegionIterator<ImageType2D> Iterator2DType;

	// Make an image pointer points to the output of random filter
	// Remember this filter has as output as itk::Image data rep
	ConstIterator2DType in(inputImage2D, inputImage2D->GetRequestedRegion());
	Iterator2DType out(outputImage2D, inputImage2D->GetRequestedRegion());

	for (in.GoToBegin(), out.GoToBegin(); !in.IsAtEnd(); ++in, ++out) {
		out.Set(in.Get() * in.Get());

		// Print stdout the value of the current input and output pixels
		float inputValue = in.Get();
		float outputValue = out.Get();
		std::cout << inputValue << "\t" << outputValue << std::endl;
	}

	return 0;
}