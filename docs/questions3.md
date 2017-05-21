# Questions 3

> Francisco Javier Bolívar Lupiáñez

## Issues about Fundamentals of Volume Visualization

**1.- The classification step in the volume visualization pipeline determines how each voxel contributes to the final image by means of transfer functions. Define the aim of a transfer function and list the four transfer functions commonly used in volume visualization.**

La función de transferencia mapea valores escalares de vóxeles a propiedades ópticas. Las cuatro funciones de transferencia serían las de los tres canales de color (RGB) y la de opacidad.

**2.- Describe an example of how histograms can be useful in the classification step and propose a procedure and an interface that permits the interactive specification of this step. Look at the images below (Figs. 1, 2 and 3).**

!["fig1"](img/questions3/1.2/fig1.png)

!["fig2"](img/questions3/1.2/fig2.png)

!["fig3"](img/questions3/1.2/fig3.png)

Los histogramas nos sirven para detectar los distintos materiales que se encuentran en una imagen. Cada uno de los picos puede corresponder a un material. El problema es que no todo es tan bonito ya que hay materiales cuyo rango de valores pueden solaparse. Por ejemplo: la sangre tiene valores de 30 a 45 HU y el músculo de 10 a 40 HU. No obstante, el histograma sigue siendo útil pues nos da pistas para definir las distintas partes de función de transferencia (color y opacidad).

Para especificar la función de transferencia se le podría proveer al usuario de una gráfica interactiva (la que forma tanto la función de transferencia de color como de opacidad) con la función de transferencia mostrándose de fondo. Para la parte de color se podría mostrar, en lugar de la curva de la función para cada uno de los valores RGB el color del que se pintaría. Algo así como lo que aparece en la Figura 2. El usuario podría pinchar en la curva de la función para añadir puntos de control o editar los ya existentes. Mostrándose el efecto de los cambios al instante.

**3.- Write a pseudocode for calculating Phong Illumination Model for each voxel of a volume dataset taking into account that the classification step has been finished - you have color per voxel! Don't consider the opacity assigned.**

Respuesta

## Issues about Indirect Volume Visualization

**1.- Describe the isosurface specification model commonly used in polygonal isosurface extraction.**

Respuesta

**2.- Draw the 16 possible cases produced by Marching Squares algorithm indicating the equivalence classes that rotations and complement (inversion) produce. See the Fig. 4 for a guidance.**

!["fig4"](img/questions3/2.2/fig4.png)

Respuesta

**3.- Write a pseudocode for extracting an isosurface using a marching cubes from a volume dataset. The isovalue tau and the dataset will be specified as a parameter. You must approximate the normals using the central difference operator and suppose the classification step is previously done - you have colors and opacities in each voxel together with the true density value. The output will be the triangle mesh with color and opacity per vertex. You have not to write low-level code, just use functions (methods), named clearly, for each different processing.**

Respuesta

## Issues about Direct Volume Visualization (Rendering)

**1.- Describe the main idea which direct volume rendering relies on. Base your explanation in the discretized volume rendering equation.**

Respuesta

**2.- Explain why compositing can be done in two directions and explain *back to front compositing*.**

Respuesta
