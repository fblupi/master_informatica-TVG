# Filtering with ITK (II)

## Task 1

Write a program that reads an image from a file and displays the result of applying the previous filters for calculating gradient magnitude to the input image. Try this program with the input images: `BrainProtonDensitySlice256x256.png` `saltAndPepperNoise1.jpg`, `saltAndPepperNoise2.jpg` and `gaussianNoise.jpg`. You may read the source codes `GradientRecursiveGaussianImageFilter.cxx` and `GradientMagnitudeFilter.cxx` placed at `'ITK_DIR/Examples/Filtering'` to take a clue of how to program this task.

## Task 2

Write a program that reads an image from a file and displays the result of applying the previous thresholding filters to the input image. The idea is to obtain a segmentation of some region of interest that you can identify in the image.Try this program with the input images: `BrainProtonDensitySlice256x256.png` `saltAndPepperNoise1.jpg`, `saltAndPepperNoise2.jpg` and `gaussianNoise.jpg`. You may read the source codes `BinaryThresholdImageFilter.cxx` and `ThresholdImageFilter.cxx` placed at `'ITK_DIR/Examples/Filtering'` to take a clue of how to program this task.

## Task 3

Write a program that reads an image from a file and displays the result of applying the Cany Edge Detection filter to the input image. The idea is to obtain several results depending of the free parameters of the filter, together with using a previous noise reduction step. Try this program with the input images: `BrainProtonDensitySlice256x256.png` `saltAndPepperNoise1.jpg`, `saltAndPepperNoise2.jpg` and `gaussianNoise.jpg`.

## Exercise

Write a report on the different results you have obtained concerning the different types of images you have provided to your programs for thresholding and edge detection, together with the different parameter values you have used. Please, illustrate the results showing the images you have obtained in each pipeline, detailing the parameters you have used.