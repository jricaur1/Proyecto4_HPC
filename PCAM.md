# Modelo PCAM para la predicción del clima usando paralelismo

## Algoritmo original

Existen múltiples acercamientos a la problemática del clima dentro de la computación, especialmente por las potenciales variaciones del clima y los diversos factores implicados, que pueden volver predicciones fuera de un rango de 10 días, Inutilizables. Por lo anterior, es común encontrar implementaciones que utilizan lógica difusa , Redes neuronales con múltiples componentes que aumentan su complejidad, y modelos estadísticos  que aunque complejos, pueden omitir aspectos a considerar dependiendo del nivel de abstracción utilizado en el modelo.

En este caso, se implementará una solución que haga uso de un modelo estadístico que considere las condiciones climáticas de la semana anterior, además de las de las 2 semanas anteriores, a través de un algoritmo de ventana deslizante, que permitirá determinar las fechas que más se acerquen al comportamiento de los componentes del clima a analizar de la semana actual.

// sliding window

Las fechas más cercanas pueden encontrarse a través de una diferencia euclidiana entre los componentes a considerar dentro del modelo determinado. 

// euclidean model

Al encontrar este valor, se puede determinar cuál matriz dentro de las ventanas, tiene el mayor acercamiento a la matriz actual, que denominaremos CD. 

Al obtener estos componentes, se puede ejecutar una diferencia simple para determinar la relación entre la semana anterior y la actual. Al tener valores que pueden ser cero, ejecutar una diferencia porcentual no es posible. Después de esto se requiere encontrar una media para cada componente de las semanas y entre ellas para así encontrar la asociación entre la semana anterior y la actual. Este dato podrá asociarse al día anterior al solicitado, para generar así la predicción. El algoritmo puede definirse de la siguiente manera:

1. Se obtiene la matriz de los 7 días anteriores a la fecha a predecir (CD), retornando una matriz de 7x4
2. Se obtiene la matriz de los 14 días del año anterior a la fecha a predecir (PD) obteniendo una matriz de 14x4
3. Se generan 8 ventanas deslizantes usando la matriz PD, (W1, W2 … W7, W8)
4.  Se obtiene la distancia euclidiana entre las matrices de las ventanas y la matriz CD (ED1, ED2 … ED7, ED8)
5. Se selecciona la matriz ventana con la menor distancia euclidiana
6. Para cada componente del clima:
   6.1. Se encuentra su vector de diferencia en cd ABS(CDi+1j - CDij), Obteniendo una matriz de 6x1 denominada VC
   6.2. Se encuentra su vector de diferencia en pd ABS(PDi+1j - PDij), Obteniendo una matriz de 6x1 denominada VP.
   6.3. Se encuentra la media del vector VC, denominada MVC
   6.4. Se encuentra la media del vector  VP, denominada MVP
   6.5. Se encuentra la media general Mean= (MVC + MVP)/2
   6.6. Se suma este componente al componente de la fecha anterior. 

A través de este proceso se encuentra una aproximación de los componentes a analizar en este caso. Por motivos de facilidad, se tomaron los datos de National Oceanic and Atmospheric Administration (NOAA), para la ciudad de Washington en su estación GHCND:USC00450008, utilizando un rango de fechas desde el 12/05/2013 hasta 12/05/2020, fecha en la que se cierra dicha estación.

Es importante resaltar que el algoritmo secuencial expresado anteriormente fue tomado del paper Weather Forecasting Using Sliding Window Algorithm, referenciado en la parte inferior del algoritmo. Sin embargo, su implementación fue desarrollada por los estudiantes que presentan este trabajo.

## Particionamiento

Los datos a analizar se segmentan en cada una de las funciones a través de los procesos como el Sliding window ejecutado. Para este proceso cada uno de los métodos que usa vectores fue vectorizado y hace uso de OpenMP en cada for ejecutado. Esto puede observarse especialmente en el archivo prediction.cc

## Comunicación

La comunicación entre procesos ejecutados la realiza OpenMP de forma transparente haciendo uso de hilos. Dado que todos los datos se encuentran en memoria compartida, se puede acceder con facilidad a los datos, a menos que se requiera un proceso de escritura pues en estos casos se ejecuta un Mutex para garantizar una gestión sincrónica de los datos. En este caso no fue posible finalizar la implementación haciendo uso de MPI para el paso de mensajes.

## Aglomeración

La aglomeración de datos es realizada a través de matrices después del proceso de Sliding window. En este, gracias a los vectores, contamos con varias matrices resultantes de las Sliding windows y tenemos que empezar a computar las predicciones. Este proceso se hace cuando encontramos la distancia euclideana, la varianza, la media varianza y la aproximación.

## Mapping  

Dado que solo hacemos uso de OpemMP y no usamos OpenMPI, el mapping lo maneja OpenMP y esto se puede ver evidenciado en el reporte de salida ipo_out.optrpt.
