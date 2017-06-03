# Segmentation of images using ITK

## Task 1

Write a program that reads an image from a file and displays the result of applying to the input image the following filters: ConnectedThresholdImageFilter, NeighbourhoodConnnectedImageFilter and ConfidenceConnectedImageFilter. The idea is to obtain several results depending of the three parameters of the filter, together with using a previous noise reduction over an input image or providing the filter with the input image without any previous noise reduction step. Try this program with the input images: `BrainProtonDensitySlice256x256.png`, `coronaryAngiogram.png`, `saltAndPepperNoise1.jpg`, and `gaussianNoise.jpg`.

## Watershed 

You can read the review in the guide on section "4.2 Sgementation based on Watersheds" for remembering the basis of watershed segmentation, but we are going to focus on the use of the ITK Watershed filter illustrated in section "4.2.2 Using the ITK Watershed Filter" using the code WatershedSegmentation1.cxx.

## Mathematical Morphology

Mathematical morphology filters are an important tool in image processing. ITK provides us with filters that operate on binary images and filters that operate on grayscale images.

Read the section "2.6.3 Mathematical Morphology" in the ITKSoftwareGuide and try the code examples.

## Exercise

Take as input an image from MRI data and try to segment different structures from the MRI you used when worked in the last script about filtering. Try the different filters for doing segmentation and try different parameter settings. Finally, try to use a mathematical morphology binary filter to correct some parts of a semented image.