# Questions 2

> Francisco Javier Bolívar Lupiáñez

## Issues about Analysis for Medical Visualization

**1.- There are two main categories of spatial processing: *intensity transformations* and *spatial (kernel) filtering*. Describe the general idea in which they rely upon and the underlying general functions.**

Respuesta

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

Respuesta

**6.- Describe the threshold-based segmentation method and relates it with the segmentation methods provides by ITK.**

Respuesta

**7.- Describe the procedure to obtain a watershed segmentation image, including the merging component.**

Respuesta

**8.- Describe the different steps carried on by livewire edge-based segmentation approach.**

Respuesta

**9.- How can you use morphologic operators to reduce noise? What kind of morphologic to take into account (transformation and similarity measure).**

Respuesta
