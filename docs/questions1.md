# Questions 1

> Francisco Javier Bolívar Lupiáñez

## Issues about Medical Imaging Modalities

**1.- X-ray images rely upon two underlying physical phenomena: *absorption* and *scattering* which provoke X-ray *attenuation*. Which are the effects that these two phenomena produce onto final X-ray images?**

Los rayos X son absorbidos por el objeto con el que inciden y son dispersados por el denominado efecto Compton que limitan el contraste y la calidad de las imágenes.

**2.- How influences the kind of beam X-rays, soft or hard, on the type of tissues that can be clearly perceived in the final X-ray image?**

Con los *hard beam x-rays* se obtienen materiales muy densos como pueden ser los huesos, mientras que con los *soft beam x-rays* se obtienen tejidos menos densos.

**3.- Describe the physical model of attenuation for X-rays.**

Tras el paciente se coloca una hoja que captura la intensidad que le va llegando en cada punto. La intensidad resultante depende tanto de la anchura del material como de un coeficiente mu que caracteriza la atenuaación S. La intensidad inicial `I_0` cae exponencialmente conforme se incrementa la distancia d:

```
I(d) = I_0 * e^(-mu * d)
```

Por lo tanto, la atenuación será la sumatoria de los productos `mu * d` ya que distintos tipos de materiales se ven involucrados en el cómputo:

```
S = sum(mu_i * d_i)
```

**4.- Enumerate the properties of the images coming from X-ray Rotational Angiography.**

- Resolución muy alta
- Conjuntos de datos isotrópicos
- Buena calidad de reconstrucción (para determinados órganos, hueso y vasos sanguíneos con contrastes)
- Rápidos (13 segundos para un escaneo completo)

**5.- Which are the parameters of CT scanning and how influence the visual quality of the final 3D image (volume)**

- Resolución espacial (número de cortes, píxeles por corte y distancias entre voxeles): Si la resolución es más alta los datos serán más ruidosos si la dosis de radiación se mantiene.
- Dosis de radiación: Si la dosis de radiación es mayor se conseguirá mejor radio señal-ruido.
- *Gantry tilt* (sistema de rotación emitor/detector): Se puede adaptar el *gantry tilt* para un órgano específico a examinar.

**6.- MRI exploits the occurrence of hydrogen nucleus in human tissue for image generation. The MRI device measures two times that take into account the time between *phase* (the protons are misaligned in a magnetic field) and *dephase* (the protons realign with the magnetic field). Looking at the slides titled "Magnetic Resonance Imaging: T1 and T2", can you describe how to discriminate between different tissue types using the plots of the bottom?**

T2 se obtiene en la gráfica de relajación transversal al 37%. Esta línea cortará las gráficas de los distintos tejidos en un punto determinado. Lo mismo pasa con T1 y la relajación longitudinal al 63%.

**7.- Compare CT imaging properties against to MRI imaging properties.**

- La MRI obtiene imágenes de menor resolución que la CT.
- Son complementarios la MRI puede ser usado para fluidos y la CT para huesos.
- La MRI da un mayor contraste en tejidos poco densos.
- Los datos obtenidos con una CT son más entendibles por médicos mientras que los obtenidos con una MRI por radiólogos.
