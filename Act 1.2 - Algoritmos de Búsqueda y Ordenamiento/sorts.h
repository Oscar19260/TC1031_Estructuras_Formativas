#ifndef SORTS_H_
#define SORTS_H_

#include <vector>
#include <list>

template <class T>
class Sorts {
private:
	void swap(std::vector<T>&, int, int);
  void copiarArreglo(std::vector<T>&, std::vector<T>&, int, int);
  void arregloMerge(std::vector<T>&, std::vector<T>&, int, int, int);
	void splitMerge(std::vector<T>&, std::vector<T>&, int, int);
	int busqBin_aux(std::vector<T>&, int, int, int);
public:
	std::vector<T> ordenaSeleccion(std::vector<T>&);
	std::vector<T> ordenaBurbuja(std::vector<T>&);
	std::vector<T> ordenaMerge(std::vector<T>&);

  int busqSecuencial(std::vector<T>&, int);
  int busqBinaria(std::vector<T>&, int);
};

// Swap ////////////////////////////////////////
template <class T>
void Sorts<T>::swap(std::vector<T> &prueba, int i, int j) {
	T aux = prueba[i];
	prueba[i] = prueba[j];
	prueba[j] = aux;
}

// Selection Sort ////////////////////////////////////////
template <class T>
std::vector<T> Sorts<T>::ordenaSeleccion(std::vector<T>& prueba) {
	int pos;
	for(int i = 0; i < prueba.size(); i++){
		pos = i;
		for(int j = i+1; j < prueba.size(); j++){
			if(prueba[j] < prueba[pos]){
				pos = j;
			}
		}
		if(pos != i){
		swap(prueba, i, pos);
		}
	}
	return prueba;
}

// Bubble Sort ////////////////////////////////////////
template <class T>
std::vector<T> Sorts<T>::ordenaBurbuja(std::vector<T>& prueba) {
	for(int i = 0; i < prueba.size()-1; i++){
		for(int j = 0; j < prueba.size()-i-1; j++){
			if(prueba[j] > prueba[j+1]){
				swap(prueba, j, j+1);
			}
		}
	}
	return prueba;
}

// Merge Sort ////////////////////////////////////////
template <class T>
void Sorts<T>::copiarArreglo(std::vector<T> &A, std::vector<T> &B, int low, int high) {
	for(int i = low; i <= high; i++){
		A[i] = B[i];
	}
}

template <class T>
void Sorts<T>::arregloMerge(std::vector<T> &A, std::vector<T> &B, int low, int mid, int high) {
	int i,j,k;
	i = low;
	j = mid+1;
	k = low;
	while(i <= mid && j <= high){
		if(A[i] < A[j]){
			B[k] = A[i];
			i++;
		}
		else{
			B[k] = A[j];
			j++;
		}
		k++;
	}
	if(i > mid){
		for(; j <= high; j++){
			B[k++] = A[j];
		}
	}
	else{
		for(; i <= mid; i++){
			B[k++] = A[i];
		}
	}
}

template <class T>
void Sorts<T>::splitMerge(std::vector<T> &A, std::vector<T> &B, int low, int high) {
	int mid;
	if((high-low) < 1){
		return;
	}
	mid = (high+low)/2;
	splitMerge(A, B, low, mid);
	splitMerge(A, B, mid+1, high);
	arregloMerge(A, B, low, mid, high);
	copiarArreglo(A, B, low, high);
}

template <class T>
std::vector<T> Sorts<T>::ordenaMerge(std::vector<T>& prueba) {
	std::vector<T> tmp(prueba.size());
	splitMerge(prueba, tmp, 0, prueba.size()-1);
	return prueba;
}

// Busq Secuencial ////////////////////////////////////////
template <class T>
int Sorts<T>::busqSecuencial(std::vector<T> &prueba, int val) {
	int no = -1;
	for (int i = 0; i < prueba.size(); i++) {
		if (val == prueba[i]) {
			return i;
		}
	}
	return no;
}

// Busq Binaria ////////////////////////////////////////
template <class T>
int Sorts<T>::busqBin_aux(std::vector<T> &prueba, int low, int high, int val) {
	int mid;

	if (low <= high){
		mid = (high+low)/2;
		if (val == prueba[mid]){
			return mid;
		}
		else if (val < prueba[mid]){
			return busqBin_aux(prueba,low,mid-1,val);
		}
		else if (val > prueba[mid]){
			return busqBin_aux(prueba,mid+1,high,val);
		}
	}
	return low-1;
}

template <class T>
int Sorts<T>::busqBinaria(std::vector<T> &prueba, int val) {
	return busqBin_aux(prueba, 0, prueba.size()-1, val);
}

// Fin de la transmisión ////////////////////////////////////////
#endif /* SORTS_H_ */
