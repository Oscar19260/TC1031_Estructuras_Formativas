#ifndef HEAP_H_
#define HEAP_H_

#include <string>
#include <sstream>
#include <iostream>

// Clase Heap //////////////////////////////////
template <class T>
class Heap{
private:
	T *dato;		  		//Nodo (se almacenan los daatos)
	unsigned int tam;		//Tamaño de la lista
	unsigned int count;		//Cantidad datos
	unsigned int padre(unsigned int) const;	//Padre
	unsigned int izq(unsigned int) const;	//Nodo izquierdo
	unsigned int der(unsigned int) const; 	//Nodo izquierdo
	void heapify(unsigned int);				//Acomodo de la fila
	void swap(unsigned int, unsigned int);
	
public:
	Heap(unsigned int);
	~Heap();
	void push(T);		//Agregue un dato a la fila priorizada
	void pop();			//Saca de la fila priorizada el dato que tiene mayor prioridad
	T top();			//Regresa el valor del dato que esta con mayor prioridad en la fila priorizada
	bool empty() const;	//Regresa un valor boleando diciendo si la fila priorizada esta vacía o tiene datos
	int size() const;	//Regresa la cantidad de datos que tiene la fila priorizada
	std::string toString() const;
};

// Constructor de Heap //////////////////////////////////
template <class T>
Heap<T>::Heap(unsigned int t) {
	tam = t;
	dato = new T[tam];
	count = 0;
}

// Destructor de Heap //////////////////////////////////
template <class T>
Heap<T>::~Heap() {
	delete [] dato;	
	dato = 0;
	tam = 0; 
	count = 0;
}

// Padre //////////////////////////////////
template <class T>
unsigned int Heap<T>::padre(unsigned int pos) const {
	return (pos - 1)/2;		//Regresa la posición del padre
}

// Izquierda //////////////////////////////////
template <class T>
unsigned int Heap<T>::izq(unsigned int pos) const {
	return (pos*2 + 1);		//Regresa la posición del nodo izquierdo
}

// Derecha //////////////////////////////////
template <class T>
unsigned int Heap<T>::der(unsigned int pos) const {
	return (pos*2 + 2);		//Regresa la posición del nodo derecho
}

// Swap //////////////////////////////////
template <class T>
void Heap<T>::swap(unsigned int i, unsigned int j){
	T aux = dato[i];
	dato[i] = dato[j];
	dato[j] = aux;
}

// Heapfy //////////////////////////////////
template <class T>
void Heap<T>::heapify(unsigned int pos){
	unsigned int iz = izq(pos);
	unsigned int de = der(pos);
	unsigned int min = pos;
	if (iz <= count && dato[iz] < dato[min]) {
		min = iz;
	}
	if (de <= count && dato[de] < dato[min]) {
		min = de;
	}
	if (min != pos) {
		swap(pos, min);
		heapify(min);
	}
}

// Push //////////////////////////////////
template <class T>
void Heap<T>::push(T val){
	int pos;
	pos = count;
	count++;

	while(pos > 0 && val < dato[padre(pos)]){
		dato[pos] = dato[padre(pos)];
		pos = padre(pos);
	}
	dato[pos] = val;
}

// Pop //////////////////////////////////
template <class T>
void Heap<T>::pop(){
	T aux = dato[0];
	dato[0] = dato[--count];
	heapify(0);
}

// Top /////////////////////////////////////
template <class T>
T Heap<T>::top(){
	T aux = dato[0];
	return aux;
}

// Empty //////////////////////////////////
template <class T>
bool Heap<T>::empty() const {
	return (count == 0);	//El tamaño de a estructura es 0
}

// Size //////////////////////////////////
template <class T>
int Heap<T>::size() const{
	return count;			//Regresa la cantidad de datos
}

// To String //////////////////////////////////
template <class T>
std::string Heap<T>::toString() const{
	std::stringstream aux;
	aux << "[";	for (unsigned int i = 0; i < count; i++) {
		if (i != 0) {
			aux << " ";
		} 
		aux << dato[i];
	} 
	aux << "]";
	return aux.str();
}

#endif /* HASH_H_ */
	
