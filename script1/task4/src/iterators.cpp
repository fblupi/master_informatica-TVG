#include "itkImage.h"
#include "itkRandomImageSource.h"
#include "itkImageRegionConstIterator.h"
#include "itkImageRegionIterator.h"

int main(int, char *[])
{
	/*
	Define a new type from the template object itk::image<T1,T2>, 'FloatImage2DType', using
	template instantiation whose T1=float and T2=2.
	*/
	typedef itk::Image<float, 2> FloatImage2DType;

	/*
	Declare a smart pointer, 'random', that points to an object (source object) of type
	itk::RandomImageSource<T> which is templated by 'FloatImage2DType', i.e.
	whose T=FloatImage2DType.
	*/
	itk::RandomImageSource<FloatImage2DType>::Pointer random;

	// Create a new object of type itk::RandomImageSource<FloatImage2DType> which is
	// pointed by 'random'.
	random = itk::RandomImageSource<FloatImage2DType>::New();

	// Set the interval for generating random numbers. SetMin/Max sets the minimum/maximum pixel value
	random->SetMin(0.0);
	random->SetMax(1.0);

	// Define and set the random image's size
	FloatImage2DType::SizeValueType size[2];
	size[0] = 20;
	size[1] = 20;
	random->SetSize(size);

	// Explicitly invoke the Update() method to update de pipeline.
	random->Update();

	// Create an object from the previously instantiated Image class
	FloatImage2DType::Pointer outputImage2D = FloatImage2DType::New();

	// Define where the image grid starts
	FloatImage2DType::IndexType region2DIndex;
	region2DIndex[0] = 0;  // first coordinate on X in image space
	region2DIndex[1] = 0;  // first coordinate on Y in image space

						   // Define the number of pixels in each dimension
	FloatImage2DType::SizeType region2DSize;
	region2DSize[0] = 20; // number of pixels along X 
	region2DSize[1] = 20; // number of pixels along Y

						  // Create a region for the image from 'region2DIndex' and with 'region2DSize'
	FloatImage2DType::RegionType region2D;

	region2D.SetIndex(region2DIndex);
	region2D.SetSize(region2DSize);

	// Assign a valid region to the image and allocate memory
	outputImage2D->SetRegions(region2D);
	outputImage2D->Allocate();

	// Declare and define two new types of iterators across 'FloatImage2DType'
	typedef itk::ImageRegionConstIterator< FloatImage2DType > FloatConstIterator2DType;
	typedef itk::ImageRegionIterator< FloatImage2DType > FloatIterator2DType;

	// Make an Image pointer points to the output of random filter
	FloatImage2DType::Pointer inputImage2D = random->GetOutput();

	// Define the iterators across 'inputImage2D' and 'outputImage2D'
	FloatConstIterator2DType in(inputImage2D, inputImage2D->GetRequestedRegion());
	FloatIterator2DType out(outputImage2D, inputImage2D->GetRequestedRegion());

	for (in.GoToBegin(), out.GoToBegin(); !in.IsAtEnd(); ++in, ++out) {
		out.Set(in.Get() * in.Get());

		// Print stdout the value of the current input and output pixels
		float inputValue = in.Get();
		float outputValue = out.Get();
		std::cout << inputValue << "\t" << outputValue << std::endl;
	}
}