# Volume Rendering with VTK

## Example 1

This code makes contouring from the input data.

## Example 2

In this second code example we will see two new aspects that we can set for a volume data: the material that will be applied to the extracted isosurface and the optimization by triangle strips.

## Example 3

This example shows how to use lookup tables for coloring different planes that pass through the volume data. The class vtkLookupTable together with ImageMapToColors give us the required functionality.

## Example 4

In this example we will see how VTK allows to use the raycasting technique for volume data by means of the class vtkVolumeRayCastMapper. The key tho achieving good results with volume rendering is to select an effective transfer function. We saw in class that a good transfer function should reveal boundaries present in the volume, when such boundaries exist. The classes vtkColorTransferFunction and vtkPiecewiseFunction permit to define transfer function for the volume raycaster.