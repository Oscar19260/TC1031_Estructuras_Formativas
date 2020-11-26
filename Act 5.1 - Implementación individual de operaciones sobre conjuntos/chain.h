#ifndef CHAIN_H_
#define CHAIN_H_

#include <string>
#include <vector>
#include <list>
#include <sstream>

using namespace std;

// Clase Chain
template <class Key, class Value>
class Chain{
private:
	unsigned int (*func) (const Key);
	unsigned int size;	//Tamaño de la tabla
	unsigned int count;	//Ocupación de la tabla
	vector<Key> *keys;			
	vector<Value> *values;		
	long indexOf(const Key) const;
	
public:
	Chain(unsigned int, unsigned int (*f) (const Key));
	~Chain();
	bool full() const;
	bool put(Key, Value);
	string toString() const;
};

// Constructor de la tabla Chain
template <class Key, class Value>
Chain<Key, Value>::Chain(unsigned int sze, unsigned int (*f) (const Key)) {
	size = sze;
	keys = new vector<Key>[size];	//Creamos un arreglo de Key con tamaño size
	values = new vector<Value>[size];
	func = f;
	count = 0;
}

// Destructo de la tabla Chain
template <class Key, class Value>
Chain<Key, Value>::~Chain() {
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
bool Chain<Key, Value>::full() const {
	return (count >= size);
}

// Desplazamiento para el manejo de colisiones
template <class Key, class Value>
long Chain<Key, Value>::indexOf(const Key k) const {
	return func(k) % size;
}

// Agrega keys y valores
template <class Key, class Value>
bool Chain<Key, Value>::put(Key k, Value v) {
	unsigned int i, start;
	long pos;

	pos = indexOf(k);
	if (keys[pos].empty()) {
    	keys[pos].push_back(k);
		values[pos].push_back(v);
    	count++;
		return true;
	}

  	else{
		for(int i=0; i < keys[pos].size(); i++){
		if(keys[pos][i] == k){
			values[pos][i] = v;
			return true;
			}
		}
		keys[pos].push_back(k);
		values[pos].push_back(v);
		count++;
		return true;
	}
}

// Impresion en la clase chain
template <class Key, class Value>
std::string Chain<Key, Value>::toString() const {
	std::stringstream aux;
	for (int i = 0; i < size; i++){
			if (!keys[i].empty()){
				aux <<"(" << i ;
				for (int j = 0; j < keys[i].size(); j ++){
						 aux << " [" << keys[i][j] << " : " << values[i][j] << "]";
				}
				aux <<") ";
			}
	}
	return aux.str();
}

// Fin de la transmisión ////////////////////////////////////////////////////////////////////////////////////////
#endif /* CHAIN_H_ */