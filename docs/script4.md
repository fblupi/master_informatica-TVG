# Script 4: Filtrado (II)

> Francisco Javier Bolívar Lupiáñez

## Gradient Computation

#### Salt and Pepper Noise 1

!["sap1"](img/script4/task1/saltAndPepperNoise1.png)

#### Salt and Pepper Noise 2

!["sap2"](img/script4/task1/saltAndPepperNoise2.png)

#### Gaussian Noise

!["gn"](img/script4/task1/gaussianNoise.png)

### Conclusiones

Vemos como aplicar la detección de gradientes en imágenes con ruido sin filtrar puede dar resultados malos que se pueden salvar un poco usando un cómputo gaussiano recursivo. No obstante, es mucho más adecuado aplicar un filtro de los vistos en el [tema anterior](script3).

## Thresholding

#### Salt and Pepper Noise 1

!["sap1"](img/script4/task2/saltAndPepperNoise1.png)

#### Salt and Pepper Noise 2

!["sap2"](img/script4/task2/saltAndPepperNoise2.png)

#### Gaussian Noise

!["gn"](img/script4/task2/gaussianNoise.png)

### Conclusiones

El thresholding es una aproximación burda a la segmentación, en este caso vemos dos orientaciones o binario con un valor mínimo y máximo o basíco con un valor de iso-superficie a partir del cual considerar. También observamos como sería necesario aplicar algún filtro antes de realizar esta primera segmentación.

## Edge Detection

#### Salt and Pepper Noise 1

!["sap1"](img/script4/task3/saltAndPepperNoise1.png)

#### Salt and Pepper Noise 2

!["sap2"](img/script4/task3/saltAndPepperNoise2.png)

#### Gaussian Noise

!["gn"](img/script4/task3/gaussianNoise.png)

#### Brain Proton Slice (sin ruido)

!["nn"](img/script4/task3/noNoise.png)

### Conclusiones

Al igual que los filtros anteriores, se ve que es necesario filtrar antes. A la derecha se observan los bordes detectados sobre una imagen previamente filtrada con un median filter y a la izquierda sin este. Se ve como afecta en las imágenes con ruido de tipo salt and pepper e incluso en la última de las imágnes donde no hay ruido. También se puede ver la importancia de los parámetros. En la imagen sin rudio con una varianza de 1 ha bastado para tener un buen resultado, pero en las imágenes con ruido ha hecho falta bajar hasta diez veces este valor.