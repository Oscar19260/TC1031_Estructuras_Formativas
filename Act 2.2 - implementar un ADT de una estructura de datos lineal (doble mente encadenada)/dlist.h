#ifndef DLIST_H_
#define DLIST_H_

#include <string>
#include <sstream>
#include "exception.h"

template <class T> class DList;

// Clase DLink //////////////////////////////////////////
template <class T>
class DLink {
	private:
		T value;
		DLink<T> *previous;
		DLink<T> *next;
		DLink(T);
		DLink(T, DLink<T>*, DLink<T>*);
		DLink(const DLink<T>&);
		friend class DList<T>;
};

template <class T>
DLink<T>::DLink(T val): value(val), previous(0), next(0) {}

template <class T>
DLink<T>::DLink(T val, DLink *prev, DLink* nxt): value(val), previous(prev), next(nxt) {}

template <class T>
DLink<T>::DLink(const DLink<T> &source): value(source.value), previous(source.previous), next(source.next) {}

// Clase DList //////////////////////////////////////////
template <class T>
class DList{
	private:
		DLink<T> *head;
		DLink<T> *tail;
		int size;
	public:
		DList();
		DList(const DList<T>&) throw (OutOfMemory);
		~DList();

		bool empty() const;
		void addFirst(T) throw (OutOfMemory);
		void add(T) throw (OutOfMemory);
		T find(T) const;
		void update(int, T);
		T removeFirst() throw (NoSuchElement);
		T remove(int) throw (IndexOutOfBounds);
		std::string toStringForward() const;
		std::string toStringBackward() const;
		// void operator= (const DList&) throw (OutOfMemory);
}; 

template <class T>
DList<T>::DList(): head(0), tail(0), size(0) {}

template <class T>
DList<T>::~DList() {
	DLink<T> *p, *q;
	p = head;
	while (p != 0) {
		q = p->next;
		delete p;
		p = q;
	}
	head = 0;
	tail = 0;
	size = 0;
}

template <class T>
bool DList<T>::empty() const {
	return (head == 0 && tail == 0);
}

// Add ////////////////////////////////////////////////
template <class T>
void DList<T>::addFirst(T val) throw (OutOfMemory) {
	DLink<T> *newDLink;
	newDLink = new DLink<T>(val);
	if (newDLink == 0) {
		throw OutOfMemory();
	}
	if(empty()){
		head = newDLink;
		tail = newDLink;
	}
	else{
		newDLink->next = head;
		head->previous = newDLink;
		head = newDLink;
	}
	size++;
}

template <class T>
void DList<T>::add(T val) throw (OutOfMemory) {
	DLink<T> *newDLink;
	newDLink = new DLink<T>(val);
	if (newDLink == 0) {
		throw OutOfMemory();
	}
	if (empty()) {
		head = newDLink;
		tail = newDLink;
	}
	else{
		tail->next = newDLink;
		newDLink->previous = tail;
		tail = newDLink;
	}
	size++;
}

// Find ///////////////////////////////////////////////
template <class T>
T DList<T>::find(T val) const {
	DLink<T> *p;
	p = head;
    T pos = 0;
	while (p != 0) {
		if (p->value == val) {
			return pos;
		}
		p = p->next;
        pos++;
	}
	return -1;
}

// Update /////////////////////////////////////////////
template <class T>
void DList<T>::update(int move, T val) {
    DLink<T> *p;
    p = head;
	int pos = 0;
    while(pos != move){
        p = p->next;
        pos++;
    }
    p->value = val;
}


// Remove /////////////////////////////////////////////
template <class T>
T DList<T>::removeFirst() throw (NoSuchElement) {
	T val;
	DLink<T> *p;
	if (empty()) {
		throw NoSuchElement();
	}
	p = head;
	val = p->value;
	if(head == tail){
		head = 0;
		tail = 0;
	}
	else{
		head = p->next;
		p->next->previous = 0;
	}
	delete p;
	size--;
	return val;
}

template <class T>
T DList<T>::remove(int move) throw (IndexOutOfBounds) {
    int pos;
	T val;
	DLink<T> *p;
	if(move < 0 || move >= size ){
		throw IndexOutOfBounds();
	}
	if(move == 0){
		return removeFirst();
	}
	p = head;
	pos = 0;
	while(pos != move){
		p = p->next;
		pos++;
	}
	val = p->value;
	p->previous->next = p->next;
	if(p->next != 0){
		p->next->previous = p->previous;
	}
	size--;
	delete p;
	return val;
}

// Incluye estos funciones en tu dlist.h para poder imprimir tus respuestas
// en formatos compatibles con el main
template <class T>
std::string DList<T>::toStringForward() const {
	std::stringstream aux;
	DLink<T> *p;
	p = head;
	aux << "[";
	while (p != 0) {
		aux << p->value;
		if (p->next != 0) {
			aux << ", ";
		}
		p = p->next;
	}
	aux << "]";
	return aux.str();
}

template <class T>
std::string DList<T>::toStringBackward() const {
	std::stringstream aux;
	DLink<T> *p;
	p = tail;
	aux << "[";
	while (p != 0) {
		aux << p->value;
		if (p->previous != 0) {
			aux << ", ";
		}
		p = p->previous;
	}
	aux << "]";
	return aux.str();
}

// Fin de la transmision ////////////////////////////////////////////
#endif /* DLIST_H_ */