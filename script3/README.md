# Filtering with ITK (I)

## Task 1

Write a program that reads an image from a file and displays the result of applying the following filters to the input image: RescaleIntensityImageFilter, ShiftScaleImageFilter and NormalizeImageFilter. Try this program with the input image `BrainProtonDensitySlice256x256.png`. You may read the source code `CastingImageFilters.cxx` placed at `'ITK_DIR/Examples/Filtering'` to take a clue of how to program this task.

## Task 2

Write a program that reads an image from a file and displays the result of applying two means filters with neighborhood size of *3x3* and *5x5* respectively, and two median filters with the same neighborhood sizes. Try the program with the following images: `saltAndPepperNoise1.jpg`, `saltAndPepperNoise2.jpg` and `gaussianNoise.jpg`. You may read the source code MeanImageFilter.cxx and MedianImageFilter.cxx placed `'ITK_DIR/Examples/Filtering'` to understand the use of both filters.

## Task 3

Write a program that reads an image from a file and displays the result of applying the three Gaussian filters presented (Discrete Gaussian, Binomial Blurring and Recursive Gaussian IRR). Try the program with the following images: `saltAndPepperNoise1.jpg`, `saltAndPepperNoise2.jpg` and `gaussianNoise.jpg`.

## Task 4

Write a program that reads and image from a file and displays the result of applying the three edge-preserving filters presented above. Try the program with the following images: `saltAndPepperNoise1.jpg`, `saltAndPepperNoise2.jpg` and `gaussianNoise.jpg`.

## Exercise

Take as input a noisy image and try to obtain a noise-free output image by combining several filters in a pipeline. Write a report on the different results you have obtained concerning the different types of images you have provided to your programs including smoothing filters and edge preserve smoothing filters, together with the different parameter values you have used. Please, illustrate the result showing the images you have obtained in each pipeline, detailing the parameters you have used.