#ifndef QUADRATIC_H_
#define QUADRATIC_H_

#include <string>
#include <sstream>

using namespace std;

// Clase Quadratic
template <class Key, class Value>
class Quadratic{
private:
	unsigned int (*func) (const Key);
	unsigned int size;	//Tamaño de la tabla
	unsigned int count;	//Ocupación de la tabla
	Key *keys;			
	Key initialValue;	
	Value *values;		
	long indexOf(const Key) const;
	
public:
	Quadratic(unsigned int, Key, unsigned int (*f) (const Key));
	~Quadratic();
	bool full() const;
	bool put(Key, Value);
	bool contains(const Key) const;
	Value get(const Key);
	void clear();
	string toString() const;
};

// Constructor de la tabla Quadratic
template <class Key, class Value>
Quadratic<Key, Value>::Quadratic(unsigned int sze, Key init, unsigned int (*f) (const Key)) {
	size = sze;
	keys = new Key[size];	//Creamos un arreglo de Key con tamaño size
	initialValue = init;
	for(unsigned int i = 0; i < size; i++){
		keys[i] = init;
	} 
	values = new Value[size];
	for(int i = 0; i < size; i++){
		values[i] = 0;
	}
	func = f;
	count = 0;
}

// Destructo de la tabla Quadratic
template <class Key, class Value>
Quadratic<Key, Value>::~Quadratic() {
	delete[] keys;
	keys = 0;
	delete[] values;
	values = 0;
	count = 0;
	size = 0;
	func = 0;
}

// Verificamos si se lleno 
template <class Key, class Value>
bool Quadratic<Key, Value>::full() const {
	return (count >= size);
}

// Desplazamiento para el manejo de colisiones
template <class Key, class Value>
long Quadratic<Key, Value>::indexOf(const Key k) const {
	unsigned int i, start;
	start = i = func(k) % size;
	do{
		if(keys[i] == k){
			return i;
		}
		i = (start + i+i) % size;
	} while(start != i);
	return -1;
}

// Agrega keys y valores
template <class Key, class Value>
bool Quadratic<Key, Value>::put(Key k, Value v){
	unsigned i, start;
	long pos;
	//Si ya existe actualizar
	pos = indexOf(k);
	if(pos != -1){
		values[pos] = v;
		return true;
	}
	//Si no existe inserta en nuevo espacio
	start = i = func(k) % size;
	do{
		if (keys[i] == initialValue){
			keys[i] = k;
			values[i] = v;
			return true;
		}
		i = (start + i+i) % size;
	} while (start != i);
	return false;
}

// Verificar si hay o no un dato
template <class Key, class Value>
bool Quadratic<Key, Value>::contains(const Key k) const {
	long pos;

	pos = indexOf(k);
	return (pos != -1);
}

// Extraer un valor que le corresponde a una llave
template <class Key, class Value>
Value Quadratic<Key, Value>::get(const Key k){
	unsigned int i, start;
	long pos;

	pos = indexOf(k);
	if (pos != -1){
		return values[pos];
	}
	return -1;
}

// Resetea los valores
template <class Key, class Value>
void Quadratic<Key, Value>::clear() {
	count = 0;
	for(unsigned int i = 0; i < size; i++){
		keys[i] = initialValue;
	}
}

// Impresion clase quadratic
template <class Key, class Value>
std::string Quadratic<Key, Value>::toString() const {
	std::stringstream aux;
	for (int i = 0; i < size; i++){
			if (keys[i] != initialValue){
				aux << "(" << i << " ";
			  aux << keys[i] << " : " << values[i] << ") ";
			}
	}
	return aux.str();
}

// Fin de la transmisión ////////////////////////////////////////////////////////////////////////////////////////
#endif /* QUADRATIC_H_ */