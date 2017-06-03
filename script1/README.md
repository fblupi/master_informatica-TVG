# A First Contact with ITK

## Task 1

In this task our goal is to generate our first executable program and we just need to look up on the section "Getting Started with ITK" in the guide. You must rememeber after generating the build files, on UNIX/Linux systems the project can be compiled by typing `make` in the terminal provided the current directory is set to the project's binary directory.

## Task 2

In this task we are going to learn how to read an image from a file and then show ItkVtkGlue capabilities. Our code `showImage.cpp`, reads and image passed by argument and displays it. We will replicate the structure of this code many times in order to show the results of our pipelines. Read the code and use it to read and display the image `BrainProtonDensity3Slices.mha` that is included in the directory `ITK_DIR/Examples/Data`. Remember to create a directory for Task 2, `task02` and inside it build directory, next modify adequetely the file `CMakeLists.txt` for including the name of the new executable and source code file.

Once you have read and executed `showImage.cpp` try to write a program that reads an image from a file and Shrinks the image in a factor of 2, displaying both the read and the shrunk image into a viewer. For understanding `itk::ShrinkImageFilter` seek in itk documentation at the web page.

## Task 3

In this task we will construct a program to extract information from a image that is provided as an argument and then we will display it. Concretely, we will show the following data: image size for each dimension, origin, spacing, and direction matrix. We will work with the image `BrainProtonDensitySliceBorder20DirectionPlus30.mhd` placed at Data directory inside the ITK installation directory.

## Task 4

Try to generate an executable from the code shown in the listing below and note; how to manually create an itk::Image, how to use an Image pointer to "raw" access to the Image data generated from a filter, and how to use iterators.

```c++
// Create an instance of the Image class
typedef float PixelType;
typedef itk::Image<PixelType, 2> ImageType2D;
// Declare a smart pointer to itk::RandomImageSource<Image2DType>
itk::RandomImageSource<Image2DType>::Pointer random;
// Create a new object of type itk::RandomImageSource<Image2DType>
random = itk::RandomImageSource<Image2DType>::New();
// Set the minimum/maximum pixel value
random->SetMin(0.0);
random->SetMax(1.0);
// Define and set the random image's size
Image2DType::SizeValueTypesize[2];
size[0] = 20;
size[1] = 20;
random->SetSize(size);
// Explicitly invoke the Update() method to update de popeline.
random->Update();
// Declare an smart pointer to point to a new created object of type Image2DType
Image2DType::Pointer outputImage2D = Image2DType::New();
// Define where the image grid starts
Image2DType::IndexType region2DIndex ;
region2DIndex[0] = 0 ; // first coordinate on X in image space
region2DIndex[1] = 0 ; // first coordinate on Y in image space
// Define the number of pixels in each dimens ion
Image2DType::SizeType region2DSize ;
region2DSize[0] = 20 ; // number of pixels along X
region2DSize[1] = 20 ; // number of pixel s along Y
// Create a region for the image from 'region2DIndex' and with 'region2DSize'
Image2DType::RegionType region2D;
region2D.SetIndex(region2DIndex);
region2D.SetSize(region2DSize);
// Assign a valid region to the image and allocate memory
outputImage2D->SetRegions(region2D) ;
outputImage2D->Allocate();
// Declare and defin e two new types of iterators across 'Image2DType'
typedef itk::ImageRegionConstIterator<Image2DType> ConstIterator2DType;
typedef itk::ImageRegionIterator<Image2DType> Iterator2DType;
// Make an Image pointer points to the output of random filter
// Remember this filter has as output an itk::Image data rep
Image2DType::PointerinputImage2D = random->GetOutput();
// Define the iterators across 'inputImage2D' and 'outputImage2D'
ConstIterator2DType in(inputImage2D, inputImage2D->GetRequestedRegion());
Iterator2DType out (outputImage2D, inputImage2D->GetRequestedRegion());
for (in.GoToBegin(), out.GoToBegin(); !in.IsAtEnd(); ++in, ++out) {
    out.Set(in.Get() * in.Get());
    // Print stdout the value of the current input and output pixels
    float inputValue = in.Get();
    float outputValue = out.Get();
    std::cout << inputValue << "\t" << outputValue << std::endl;
}
return EXIT_SUCCESS;
```