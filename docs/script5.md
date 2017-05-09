# Script 5: Segmentación

> Francisco Javier Bolívar Lupiáñez

## Cerebro

Usando el archivo `BrainProtonDensitySlice256x256.png`:

![BrainProtonDensitySlice256x256](img/script5/BrainProtonDensitySlice256x256.png)

Se ha segmentado tanto el plexo coroideo como la sustancia blanca.

### Plexos coroideos

Al ser una imagen bastante buena, apenas se nota la diferencia entre aplicarle o no un filtrado, no obstante, se le ha aplicado un *median filter* para suavizarla.

#### *Connected Threshold*

* Seed: 91, 118 
* Threshold: 210, 255

##### Sin filtro

![connectedThreshold](img/script5/plexosCoroideos/connectedThreshold.png)

##### Con filtro

![connectedThresholdFiltered](img/script5/plexosCoroideos/connectedThresholdFiltered.png)

#### *Neighbourhood Connected*

* Seed: 91, 118 
* Threshold: 210, 255

##### Sin filtro

![neighbourhoodConnected](img/script5/plexosCoroideos/neighbourhoodConnected.png)

En este caso, el no agregar el filtrado previo hace que la segmentación no se haga completa y segmente solo una parte del plexo.

##### Con filtro

![neighbourhoodConnectedFiltered](img/script5/plexosCoroideos/neighbourhoodConnectedFiltered.png)

#### *Confidence Connected*

* Seed: 91, 118 
* Radius: 3
* Multiplier: 3
* Iters: 2 (a partir de la tercera iteración empieza a segmentar zonas que no forman parte del plexo coroideo)

##### Sin filtro

![confidenceConnected](img/script5/plexosCoroideos/confidenceConnected.png)

##### Con filtro

![confidenceConnectedFiltered](img/script5/plexosCoroideos/confidenceConnectedFiltered.png)

##### 4 iteraciones

![confidenceConnected4Iters](img/script5/plexosCoroideos/confidenceConnected4Iters.png)

### Sustancia blanca

Al segmentar esta parte se debe notar más el pre-filtrado de la imagen pues no es una parte tan diferenciada como la anterior.

#### *Connected Threshold*

* Seed: 60, 125 
* Threshold: 150, 180

##### Sin filtro

![connectedThreshold](img/script5/sustanciaBlanca/connectedThreshold.png)

##### Con filtro

![connectedThresholdFiltered](img/script5/sustanciaBlanca/connectedThresholdFiltered.png)

#### *Neighbourhood Connected*

* Seed: 60, 125 
* Threshold: 150, 180

##### Sin filtro

![neighbourhoodConnected](img/script5/sustanciaBlanca/neighbourhoodConnected.png)

##### Con filtro

![neighbourhoodConnectedFiltered](img/script5/sustanciaBlanca/neighbourhoodConnectedFiltered.png)

#### *Confidence Connected*

* Seed: 60, 125 
* Radius: 3
* Multiplier: 3
* Iters: 1

##### Sin filtro

![confidenceConnected](img/script5/sustanciaBlanca/confidenceConnected.png)

##### Con filtro

![confidenceConnectedFiltered](img/script5/sustanciaBlanca/confidenceConnectedFiltered.png)

## Angiograma

Usando el archivo `coronaryAngiogram.png`:

![coronaryAngiogram](img/script5/coronaryAngiogram.png)

Para este se ha utilizado el filtro *Confidence Connected* pues es el único con el que se obtenía una segmentación medianamente buena. Además, se ha aplicado operadores morfológicos con los que se ve que mejora esta segmentación.

#### *Confidence Connected*

* Seed: 79, 321 
* Radius: 3
* Multiplier: 3
* Iters: 25

![confidenceConnected](img/script5/angiograma/confidenceConnected.png)

##### Diferencia con operadores morfológicos

A la derecha la imagen con operadores morfológicos (dilatación + erosión) y a la izquierda sin ellos donde se ve cómo tapa agujeros.

![mathMorph](img/script5/angiograma/mathMorph.png)
