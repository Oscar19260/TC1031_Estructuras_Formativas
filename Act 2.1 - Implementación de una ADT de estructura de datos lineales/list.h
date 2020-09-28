#ifndef List_H_
#define List_H_

#include <string>
#include <sstream>
#include "exception.h"

template <class T> class List;

// Clase Link //////////////////////////////////////////
template <class T>
class Link {
	private:
		T value;
		Link<T> *next;
		Link(T);
		Link(T, Link<T>*);
		Link(const Link<T>&);
		friend class List<T>;
};

template <class T>
Link<T>::Link(T val): value(val), next(0) {}

template <class T>
Link<T>::Link(T val, Link* nxt) : value(val), next(nxt) {}

template <class T>
Link<T>::Link(const Link<T> &source) : value(source.value), next(source.next) {}

// Clase List //////////////////////////////////////////
template <class T>
class List{
	private:
		Link<T> *head;
		int size;
	public:
		List();
		List(const List<T>&) throw (OutOfMemory);
		~List();

		bool empty() const;
		void addFirst(T) throw (OutOfMemory);
		void add(T) throw (OutOfMemory);
		T find(T) const;
		bool update(int, T);
		T removeFirst() throw (NoSuchElement);
		T remove(int) throw (IndexOutOfBounds);
		std::string toString() const;	
}; 

template <class T>
List<T>::List(): head(0), size(0) {}

template <class T>
List<T>::~List() {
    Link<T> *p = head;
    while(p != nullptr){
        head = head->next;
        delete p;
        p = head;
    }
}

template <class T>
bool List<T>::empty() const {
	return (head == 0);
}

// Add ////////////////////////////////////////////////
template <class T>
void List<T>::addFirst(T val) throw (OutOfMemory) {
	Link<T> *newLink;
	newLink = new Link<T>(val);
	if (newLink == 0) {
		throw OutOfMemory();
	}
	newLink->next = head;
	head = newLink;
	size++;
}

template <class T>
void List<T>::add(T val) throw (OutOfMemory) {
	Link<T> *newLink, *p;
	newLink = new Link<T>(val);
	if (newLink == 0) {
		throw OutOfMemory();
	}
	if (empty()) {
		addFirst(val);
		return;
	}
	p = head;
	while (p->next != 0) {
		p = p->next;
	}
	newLink->next = 0;
	p->next = newLink;
	size++;
}

// Find ///////////////////////////////////////////////
template <class T>
T List<T>::find(T val) const {
	Link<T> *p;
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
bool List<T>::update(int move, T val) {
    int pos;
    Link<T> *p;
    p = head;
    pos = 0;
    while(pos != move){
        p = p->next;
        pos++;
    }
    p->value = val;
    return true;
}

// Remove /////////////////////////////////////////////
template <class T>
T List<T>::removeFirst() throw (NoSuchElement) {
	T val;
	Link<T> *p;
	if (empty()) {
		throw NoSuchElement();
	}
	p = head;
	head = p->next;
	val = p->value;
	delete p;
	size--;
	return val;
}

template <class T>
T List<T>::remove(int move) throw (IndexOutOfBounds) {
    int pos;
	T val;
	Link<T> *p, *q;
	if(move < 0 || move >= size ){
		throw IndexOutOfBounds();
	}
	if(move == 0){
		return removeFirst();
	}
	q = 0;
	p = head;
	pos = 0;
	while(pos != move){
		q = p; 
		p = p->next;
		pos++;
	}
	val = p->value;
	q->next = p->next;
	size--;
	delete p;
	return val;
}

// Agregar un metodo toString a su clase.h ////////////////////////////////////////////
template <class T>
std::string List<T>::toString() const {
	std::stringstream aux;
	Link<T> *p;
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

// Fin de la transmision ////////////////////////////////////////////
#endif /* List_H_ */