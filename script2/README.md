# Reading and Writing Images with ITK

## Task 1

In this task our goal is to generate a program that implements a file format conversion taking advantage of the capabilities which ITK give us. You have only to build the `ImageReadWrite.cxx` placed at `'Examples/IO'`.

Note that it would be a good idea to insert any `Update()` call inside a `try/catch block` in case exceptions are thrown during the execution of the pipeline as shown in listing below:

```c++
try {
    writer->Update();
} catch(itk::ExceptionObject &err) {
    std::cerr << "ExceptionObject caught!" << std::endl;
    std::cerr << err << std::endl;
    return EXIT_FAILURE;
}
```

## Task 2

In this task we will run an example that illustrates explicit instantiation of an IO class (in this case a VTK file format), setting its parameters and then connecting it to the `itk::ImageFileWriter`. The source code for this example can be found in the file `ImageReadExportVTK.cxx`.

Although this example only illustrates how to use an explicit ImageIO class with the ImageFileWriter, the same can be done with the ImageFileReader. The Typical case in which this is done is when reading raw image files with the `itk::RawImageIO` object. The drawback of this approach is that the parameters of the image have to be explicitily written in the code. The **direct use of raw files is strongly discouraged in medical imaging**. It is always better to create a header for a raw file by using any of the file formats that combine a text header file and a raw binary file, like `itk::MetaImageIO`, `itk::GiplImageIO` and `itk::VTKImageIO`.

## Task 3

In this task we will run an example that illustrates how to read and write RGB color images to and from a file. You have to build the example in the file `RGBImageReadWrite.cxx`. Run the program with a color image such as `VisibleWomanHeadSlice.png` placed at `'ITK_DIR/Examples/Data'`.

## Task 4

In this task we will run an example that shows how to make an appropiate pipeline to cast image correctly. You have to build the example in the file `ImageReadCastWrite.cxx`. Run the program with an image from `'ITK_DIR/Examples/Data'`.

## Task 5

In this task we will run an example that reads an image and the parameters we need to define the region of interest, and then writes this region to a image file. You have to build the example in the file `ImageReadRegionOfInterestWrite.cxx`. Run the program with an image from `'ITK_DIR/Examples/Data'`.

## Task 6

In this task we will run an example for extracting an slice from a 3D volume. In this example the region that the ExtractImageFilter requires will be defined from the largest possible region of the input image. We take the size from the region and collapse the size in the *Z* component by setting its value to the input image. Note that in this case we are extracting a *Z* slice and for that reason, the dimension to be collapsed is the one with index 2. You may keep in mind the association of index components *{X = 0, Y = 1, Z = 2}*. You have to build the example in the file `ImageReadExtractWrite.cxx`.

## Exercise

Try to read the two images in DICOM format and write them in PNG format in order to visualize them with a simple image viewer application.