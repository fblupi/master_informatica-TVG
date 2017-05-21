# Questions 2

> Francisco Javier Bolívar Lupiáñez

## Issues about Analysis for Medical Visualization

**1.- There are two main categories of spatial processing: *intensity transformations* and *spatial (kernel) filtering*. Describe the general idea in which they rely upon and the underlying general functions.**

Las transformaciones de intensidad operan sobre un solo pixel de la imagen mientras que el filtrado espacial lo hace sobre el vecindario de un pixel.

La función general es:

g(x,y) = T[f(x,y)]

Donde f(x,y) es la imagen de entrada, g(x,y) la de salida y T un operador en f definido sobre un vecindario del punto (x,y).

**2.- Noise reduction filtering aims to reduce inhomogeneities in medical images. Which does noise level depends on in medical imaging?**

- Del tejido y su valor medio de gris.
- De la resolución espacial de los datos (datos de una CT con mucha resolución tienen más ruido).
- En rayos X y CT, de la cantidad de radiación.

**3.- The binomial (Gaussian) filter for noise elimination is a static noise reduction filter. Describe it. Why are the static noise reduction filter scaled so that the sum of their elements is 1?**

El filtro binomial es uan versión discretizada de la función Gaussiana y por tanto se basa en la convolución con una matriz. Por ejemplo, para un vecindario 5x5 sería:

<table>
  <tr>
    <td>1</td>
    <td>4</td>
    <td>6</td>
    <td>4</td>
    <td>1</td>
  </tr>
  <tr>
    <td>4</td>
    <td>16</td>
    <td>24</td>
    <td>16</td>
    <td>4</td>
  </tr>
  <tr>
    <td>6</td>
    <td>24</td>
    <td>36</td>
    <td>24</td>
    <td>6</td>
  </tr>
  <tr>
    <td>4</td>
    <td>16</td>
    <td>24</td>
    <td>16</td>
    <td>4</td>
  </tr>
  <tr>
    <td>1</td>
    <td>4</td>
    <td>6</td>
    <td>4</td>
    <td>1</td>
  </tr>
</table>

Para normalizar los elementos del kernel necesitamos que sumen 1, para ello se divide entre la suma de todos los elementos (256).

**4.- Explain the *property of separability* for filters and the main problem of static filters.**

Filtros separables en 2D o 3D pueden sustituirse combinando 2 o 3 filtros 1D pasando de una complejidad cuadrática a una lineal.

El problema de los filtros estáticos es que no son adaptativos y características como los bordes pueden perderse cambiando la topología de la imagen y pasar de tener dos órganos separados a juntos.

**5.- The sigma-filter is a paradigmatic case of dynamic noise reduction filters. Describe it.**

El valor de cada voxel se reemplaza por el de la media de su vecindario si su diferencia con esta es menor que el valor dado por sigma. De esta forma los bordes entre tejidos se mantendrán por lo que se le puede clasificar dentro de los filtros adaptativos (dinámicos).

**6.- Describe the threshold-based segmentation method and relates it with the segmentation methods provides by ITK.**

Partiendo de una semilla se extiende alrededor de esta fijando como voxel a segmentar aquel cuyo valor se encuentra entre los límites dados. Se parece al filtro *threshold* solo que se tiene en cuenta el vecindario.

Para implementar este tipo de segmentación hemos utilizado los filtros ITK:

- *Connected Threshold*
- *Neighborhood Connected*

**7.- Describe the procedure to obtain a watershed segmentation image, including the merging component.**

La idea de la segmentación *watershed* es ver la imagen como un mapa de colinas y valles. Los valores de elevación vienen dados por el valor de grises de los píxeles o su magnitud gradiente. Las *watershed* son las zonas que separan cuencas.

En imágenes médicas con datos algo ruidosos podemos detectar el problema de sobre segmentación que se puede resolver usando un criterio de unión de regiones. Dando un valor de inundación, se inundarán todas las regiones que se encuentren por debajo de este valor de umbral.

A veces esta inundación no examinada es insuficiente para segmentar las estructuras que queremos, la solución es que el usuario marque esas zonas de inclusión y exclusión a la estructura objetivo.

**8.- Describe the different steps carried on by livewire edge-based segmentation approach.**

- Se calculan costes desde un punto de control hasta la posición actual del ratón marcando el que tenga el coste más bajo.
- Si el camino se desvía del borde del objetivo el ratón se mueve atrás hasta que el contorno sugerido coincide con el deseado y se añade un punto de control.
- El nuevo punto de control se convierte en la semilla para el siguiente trazo.
- Este proceso se repite hasta que se cierra la región del borde.

**9.- How can you use morphologic operators to reduce noise? What kind of morphologic to take into account (transformation and similarity measure).**

Los operadores morfológicos simples son los de erosión y dilatación.

Con estos dos operadores simples surgen otros dos: apertura (erosión + dilatación) y clausura (dilatación + erosión). Con la apertura se pueden eliminar pequeños objetos y bultos y con la clausura cerrar pequeños agujeros y muescas o cortes en V.
