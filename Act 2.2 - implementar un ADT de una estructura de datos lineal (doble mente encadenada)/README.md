# Análisis de complejidad

Las listas doblemente ligadas contienen un puntero adicional, es decir un puntero previo, que junto con el puntero siguente permite que los datos queden de manera enlazada en la lista.

## add
Análisis de complejidad temporal: El algoritmo recorre n pasos ya que usa un ciclo que recorre toda la lista desde su inicio hasta la posición final agregando un elemento, por lo que su complejidad es O(n) para el peor de los casos.

## find
Análisis de complejidad temporal: El algoritmo recorre n pasos ya que usa un ciclo que recorre toda la lista desde su inicio hasta el dato que esta buscando regresando su posición, en caso de que no encuentre el dato va a regresar -1, por lo que su complejidad es O(n) para el peor de los casos.

## update
Análisis de complejidad temporal: El algoritmo recorre n pasos ya que usa un ciclo el que recorre toda la lista desde su inicio hasta la posición que busca para actualizar, por lo que su complejidad es O(n) para el peor de los casos.

## remove
Análisis de complejidad temporal: El algoritmo recorre n pasos ya que usa un ciclo el que recorre toda la lista desde su inicio hasta la posición que busca para eliminar el elemento, por lo que su complejidad es O(n) para el peor de los casos.
