# Final Project

La práctica consiste en leer una serie de imágenes con ITK y aplicarles un filtro gaussiano a la parte del hueso. Para ello, hacemos un programa que permita ajustar los parámetros leyendo un solo archivo. Después construimos un programa que lea la serie de imágenes, aplique el gaussiano a cada una de ellas, segmente el hueso por umbralización y visualice usando las funciones de transferencia de medical4.cxx.

Contenido:

* [Fitering](https://github.com/fblupi/master_informatica-TVG/tree/master/project/filtering): Programa para ajustar parámetros del filtrado y la segmentación
* [Head](https://github.com/fblupi/master_informatica-TVG/tree/master/project/head): Programa que lee la serie de imágenes, le aplica el filtrado, la segmentación y las visualiza usando *volume ray-casting*

Resultado:

!["result"](https://fblupi.github.io/master_informatica-TVG/img/project/result.png)