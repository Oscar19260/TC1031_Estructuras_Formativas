# Análisis de complejidad

## add
Análisis de complejidad temporal: El algoritmo recorre n*n pasos ya que usa dos ciclos el primero va de i = 0 hasta el tamaño del arreglo y el segundo va de desde j = i+1 hasta el tamaño del arreglo, por lo que su complejidad es O(n^2) para el peor de los casos.

## find
Análisis de complejidad temporal: El algoritmo recorre n*n pasos ya que usa dos ciclos el primero va de i = 0 hasta el tamaño del arreglo y el segundo va de desde j = 0 hasta el tamaño del arreglo menos i menos 1 hasta el tamaño del arreglo, por lo que su complejidad es O(n^2) para el peor de los casos.

## update
Análisis de complejidad temporal: El algoritmo recorre los pasos en subgrupos, dividiendose a su vez generando una especie de arbol, por lo que su complejidad es de O(nlog(n)) para el peor de los casos.

## remove
Análisis de complejidad temporal: El algoritmo recorre n pasos ya que usa un ciclo que va i = 0 hasta el tamaño del arreglo, por lo que su complejidad es O(n) para el peor de los casos.
