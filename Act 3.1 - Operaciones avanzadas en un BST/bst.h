#ifndef BST_H_
#define BST_H_

#include <string>
#include <sstream>
#include <iostream>

template <class T> class BST;

// Clase TreeNode /////////////////////////////////////////////
template <class T>
class TreeNode {
	private:
		T value;
		TreeNode *left, *right;
		TreeNode<T>* predecesor();

	public:
		TreeNode(T);
		TreeNode(T, TreeNode<T>*, TreeNode<T>*);
		void add(T);
		bool find(T);
		void remove(T);
		void removeChilds();

		int whatlevelamI(T);
		bool ancestors(T, std::stringstream&) const;
		int height() const;

		void preorder(std::stringstream&) const;
		void inorder(std::stringstream&) const;
		void postorder(std::stringstream&) const;
		void showlevel(std::stringstream&, int) const;
		void levelbylevel(std::stringstream&) const;

		friend class BST<T>;
};

// Constructores TreeNode /////////////////////////////////////////////
template <class T>
TreeNode<T>::TreeNode(T val): value(val), left(0), right(0) {}

template <class T>
TreeNode<T>::TreeNode(T val, TreeNode<T> *le, TreeNode<T> *ri): value(val), left(le), right(ri) {}

// predecesor /////////////////////////////////////////////
template <class T>
TreeNode<T>* TreeNode<T>::predecesor(){
	TreeNode<T> *l, *r;		//Creamos los nodos l y r
	l = left;				//El puntero l apunta a la izquierda
	r = right;				//El puntero r apunta a la derecha
	if (left == 0) {		//Si mi izquierda es nulo
		if (right != 0) {	//Checo que mi derecha no sea nulo
			right = 0;		//La derecha la ponemos como nulo
		}
		return r;			//Regresamos r
	}
	if (left->right == 0) {	//Si en el lado izquierdo el derecho es nulo
		left = left->left;	//El izquierdo se regresa
		l->left = 0;		//El nodo en la izquierda se hace nulo
		return l;			//Regresamos l
	}
	TreeNode<T> *parent, *child;	//Creamos nodos parent y child
	parent = left;					//El nodo padre apunta a la izquierda
	child = left->right;			//El nodo hijo apunta a la siguiente posición de parent
	while (child->right != 0) {		//Mientras hijo se pueda seguir moviendo a la derecha
		parent = child;				//El padre se vuelve hijo
		child = child->right;		//Child se mueve a la derecha
	}
	parent->right = child->left;	//El padre a la derecha es igual al hijo en la izquierda
	child->left = 0;				//La posición del hijo a la izquierda se vuelve 0
	return child;					//Regresamos child
}

// Add /////////////////////////////////////////////
template <class T>
void TreeNode<T>::add(T val){
	if (val < value){				
		if (left != 0){
			left->add(val);
		} 
		else {
			left = new TreeNode<T>(val);
		}
	} 
	else {
		if (right != 0){
			right->add(val);
		} 
		else {
			right = new TreeNode<T>(val);
		}
	}
}

// Find /////////////////////////////////////////////
template <class T>
bool TreeNode<T>::find(T val){
	if (val == value){		//Si encuentra el valor en la raíz regresa true
		return true;
	} 
	else if (val < value){	//Si el valor es menor
		return (left != 0 && left->find(val));		//Se mueve a la izquierda hasta encontrar el valor
	} 
	else if (val > value){	//Si el valor es mayor
		return (right != 0 && right->find(val));	//Se mueve a la derecha hasta encontrar el valor
	}
	return false;			//Si no encuentra el valor regresa false
}

// Remove /////////////////////////////////////////////
template <class T>
void TreeNode<T>::remove(T val){
	TreeNode<T> * pred, *old;
	if (val < value) {
		if (left != 0) {
			if (left->value == val) {
				old = left;
				pred = left->predecesor();
				if (pred != 0) {
					pred->left = old->left;
					pred->right = old->right;
				}
				left = pred;
				delete old;
			} 
			else {
				left->remove(val);
			}
		}
	} 
	else if (val > value) {
		if (right != 0) {
			if (right->value == val) {
				old = right;
				pred = right->predecesor();
				if (pred != 0) {
					pred->left = old->left;
					pred->right = old->right;
				}
				right = pred;
				delete old;
			} 
			else {
				right->remove(val);
			}
		}
	}
}

// Remove Childs /////////////////////////////////////////////
template <class T>
void TreeNode<T>::removeChilds(){		//Borra un subárbol completo
	if (left != 0) {			//Si la izquierda es diferente de 0
		left->removeChilds();	//Hace una llamada recursiva a la izquierda
		delete left;			//Elimina left de forma recursiva
		left = 0;				//left se iguala a 0
	}
	if (right != 0) {			//Si la derecha es diferente de 0
		right->removeChilds();	//Hace una llamada recursiva a la derecha
		delete right;			//Elimina right de forma recursiva
		right = 0;				//right se iguala a 0
	}
}

// What Level Am I /////////////////////////////////////////////
template <class T>
int TreeNode<T>::whatlevelamI(T val) {
	if (val == value) {			//Si el valor se encuentra en la raíz
		return 1;				//Regresa 1
	} else if (val < value) {	//Si el valor es menor que la raíz
		if(left != 0)			//Y el nodo a la izquierda no es nulo
			return left->whatlevelamI(val) + 1;	//Se mueve a la izquierda y se suma 1
	} else if (val > value) {	//Si el valor es mayor que la raíz
		if (right != 0)			//Y el nodo a la derecha no es nulo
		return right->whatlevelamI(val) + 1;	//Se mueve a la derecha y se suma 1
	}
	return -1;	//En caso de que no se encuentre nada regresamos -1
}

// Ancestors /////////////////////////////////////////////
template <class T>
bool TreeNode<T>::ancestors(T val, std::stringstream &aux) const{
	if (val == value) {		//Si el valor se encuentra en la raíz
	  return true;			//Regresamos true
	} 
	else if (val < value) {	//Si el valor es menor que la raíz
		if (aux.tellp() != 1){	
			aux << " ";
		}
		aux << value;
		return (left != 0 && left->ancestors(val,aux));	 //Si la izquierda es diferente de 0 se mueve a la izquierda
	} 
	else if (val > value) {
		if (aux.tellp() != 1) {
			aux << " ";
		}
		aux << value;
		return (right != 0 && right->ancestors(val,aux)); //Si la derecha es diferente de 0 se mueve a la izquierda
	}
	return false;	//Regresamos false
}

// Height /////////////////////////////////////////////
template <class T>
int TreeNode<T>::height() const {
	int leftl = 0;		//Inicializamos el nivel de la izquierda
	int rightl = 0;		//Inicializamos el nivel de la derecha
	if (left != 0) {	//Si izquierda no es nulo
		leftl = left->height() + 1;  //Se hace una suma recursiva al nivel de la izquierda
	}
	if (right != 0) {	//Si derecha no es nulo
		rightl = right->height() +1; //Se hace una suma recursiva al nivel de la derecha
	}
	if (leftl == 0 && rightl == 0)	 //Si ambos niveles son iguales a 0
		return 1;					 //Regresamos 1
	return (rightl > leftl) ? rightl : leftl;	//Regresamos el nivel mayor
}

// Preorder /////////////////////////////////////////////
template <class T>
void TreeNode<T>::preorder(std::stringstream &aux) const{
	aux << value;				//Entramos a un nodo
	if (left != 0) {			//Si la izquierda no es nula
		aux << " ";				
		left->preorder(aux);	//Imprimimos los valores de la izquierda de manera recursiva
	}
	if (right != 0) {			//Si la derecha no es nula
		aux << " ";
		right->preorder(aux);	//Imprimimos los valores de la derecha de manera recursiva
	}
}

// Inorder /////////////////////////////////////////////
template <class T>
void TreeNode<T>::inorder(std::stringstream &aux) const{
	if (left != 0) {			//Si la izquierda no es nula
		left->inorder(aux);		//Imprimimos los valores de la izquierda de manera recursiva
	}
	if (aux.tellp() != 1) {		//Mientras pueda seguir avanzando 
		aux << " ";
	}
	aux << value;				//Imprimimos el valor
	if (right != 0) {			//Si la derecha no es nula
		right->inorder(aux);	//Imprimimos los valores de la derecha de manera recursiva
	}
}

// Postorder /////////////////////////////////////////////
template <class T>
void TreeNode<T>::postorder(std::stringstream &aux) const{
	if (left != 0) {			//Si la izquierda no es nula
		left->postorder(aux);	//Imprimimos los valores de la izquierda de manera recursiva
	}
	if (right != 0) {			//Si la derecha no es nula
		right->postorder(aux);	//Imprimimos los valores de la derecha de manera recursiva
	}
	if (aux.tellp() != 1) {
			aux << " ";
	}
	aux << value;				//Imprimimos el valor
}

// Show Level /////////////////////////////////////////////
template <class T>
void TreeNode<T>::showlevel(std::stringstream &aux, int level) const{
	if(level == 0){
		if (aux.tellp() != 1) {
				aux << " ";
		}
		aux << value;
	}
	if (left != 0) {
		left->showlevel(aux, level -1);
	}
	if (right != 0) {
		right->showlevel(aux, level -1);
	}
}

// Level by level /////////////////////////////////////////////
template <class T>
void TreeNode<T>::levelbylevel(std::stringstream &aux) const{
	int level = height();
	for(int i = 0; i < level; i++){
			showlevel(aux, i);
	}
}

// Clase BST /////////////////////////////////////////////
template <class T>
class BST{
	private:
		TreeNode<T> *root;

	public:
		BST();
		~BST();
		bool empty() const;
		void add(T);
		bool find(T) const;
		void remove(T);
		void removeAll();

		int whatlevelamI(T);
		std::string ancestors(T) const;
		int height() const;
		
		std::string inorder() const;
		std::string preorder() const;
		std::string postorder() const;
		std::string levelbylevel() const;
		std::string visit();
};

// Constructor BST /////////////////////////////////////////////
template <class T>
BST<T>::BST(): root(0) {}

// Destructor BST /////////////////////////////////////////////
template <class T>
BST<T>::~BST(){
	removeAll();	//Limpiamos el árbol
}

// Empty /////////////////////////////////////////////
template <class T>
bool BST<T>::empty() const{
	return (root == 0);	//El árbol esta vacio
}

// Add /////////////////////////////////////////////
template<class T>
void BST<T>::add(T val){
	if (root != 0){				//Revisamos que el árbol no este vacio	
		if (!root->find(val)){	//Si el valor no se encuentra en el árbol	
			root->add(val);		//Se incerta un nuevo valor al arból
		}
	} 
	else {
		root = new TreeNode<T>(val);	//Se pone el valor como raíz
	}
}

// Find /////////////////////////////////////////////
template <class T>
bool BST<T>::find(T val) const{
	if (root != 0){					//Revisamos que el árbol no este vacio	
		return root->find(val);		//Regresamos true si se encuentra el valor
	}
	else {							//Si no encontramos el valor regresamos false
		return false;				
	}
}

// Remove /////////////////////////////////////////////
template <class T>
void BST<T>::remove(T val){
	if (root != 0) {							//Revisamos que el árbol no este vacio
		if (val == root->value) {				//Revisar si estamos trabajando con la raiz
			TreeNode<T> *pred = root->predecesor();	//Sacamos el valor directamente del predecesor de la raiz
			if (pred != 0) {					//Si el predecesor no es nulo
				pred->left = root->left;		//El predecesor a la izquierda es la raiz a la izquierda
				pred->right = root->right;		//El predecesor a la derecha es la raiz a la derecha
			}
			delete root;						//Se borra la raiz
			root = pred;						//Marcamos a root como el nuevo predecesor					
		} 
		else {									
			root->remove(val);
		}
	}
}

// Remove All /////////////////////////////////////////////
template <class T>
void BST<T>::removeAll(){
	if (root != 0){				//Revisamos que el árbol no este vacio
		root->removeChilds();	//La raíz se mueve para borrar subárboles
	}
	delete root;				//Se borra la raíz
	root = 0;					//La raíz se iguala a 0
}

// What Level Am I /////////////////////////////////////////////
template <class T>
int BST<T>::whatlevelamI(T val){
	if (root != 0) {						//Revisamos que el árbol no este vacio
	 	int num = root->whatlevelamI(val);	//Vemos el nivel desde la raíz hasta el valor
		if(num < 0) return -1;				//Si el número es menor que 0 regresa -1
		return num;							//Regresa el nivel en el que se encuentra el árbol
	}
	else {
		return -1;							//Si el árbol esta vacio, su nivel es -1
	}
}

// Ancestors /////////////////////////////////////////////
template <class T>
std::string BST<T>::ancestors(T val) const {
	std::stringstream aux;	//Converitmos los datos en string
	aux << "[";	
	if (!empty()) {			//Si el árbol no esta vacio
		if(!root->ancestors(val, aux))
			return "[]";
	}
	aux << "]";
	return aux.str();		//Regresa los datos en string
}

// Height /////////////////////////////////////////////
template <class T>
int BST<T>::height() const {
	return root->height();	//Regresamos la altura
}

// Preorder /////////////////////////////////////////////
template <class T>
std::string BST<T>::preorder() const{
	std::stringstream aux;	//Converitmos los datos en string
	aux << "[";
	if (!empty()) {			//Si el árbol no esta vacio
		root->preorder(aux);	//Imprime los datos en preorder
	}
	aux << "]";
	return aux.str();		//Regresa los datos en string
}

// Inorder /////////////////////////////////////////////
template <class T>
std::string BST<T>::inorder() const{
	std::stringstream aux;	//Converitmos los datos en string
	aux << "[";
	if (!empty()) {			//Si el árbol no esta vacio
		root->inorder(aux);	//Imprime los datos en inorder
	}
	aux << "]";
	return aux.str();		//Regresa los datos en string
}

// Postorder /////////////////////////////////////////////
template <class T>
std::string BST<T>::postorder() const{
	std::stringstream aux;	//Converitmos los datos en string
	aux << "[";
	if (!empty()) {			//Si el árbol no esta vacio
		root->postorder(aux);	//Imprime los datos en postorder
	}
	aux << "]";
	return aux.str();		//Regresa los datos en string
}

// Level by level /////////////////////////////////////////////
template <class T>
std::string BST<T>::levelbylevel() const {
	std::stringstream aux;	//Converitmos los datos en string
	aux << "[";
	if (!empty()) {			//Si el árbol no esta vacio
		root->levelbylevel(aux);	//Imprime los datos en nivel a nivel
	}
	aux << "]";
	return aux.str();		//Regresa los datos en string
}

// Visit /////////////////////////////////////////////
template <class T>
std::string BST<T>::visit() {
	std::stringstream aux;		//Converitmos los datos en string
	aux << preorder() << "\n";	//Se imprime preorder
	aux << inorder() << "\n";	//Se imprime inorder
	aux << postorder() << "\n";	//Se imprime postorder
	aux << levelbylevel();		//Se imprime el nivel a nivel
	return aux.str();			//Se regresan los datos en string
}

#endif /* BST_H_ */
