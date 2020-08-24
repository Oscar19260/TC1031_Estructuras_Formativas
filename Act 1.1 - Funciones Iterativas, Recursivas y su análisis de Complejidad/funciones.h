
#ifndef FUNCIONES_H_
#define FUNCIONES_H_

#include <string>
#include <iostream>

using namespace std;

class Funciones{
 private:
   int n;
 public:
   long sumaIterativa(int n);
   long sumaRecursiva(int n);
   long sumaDirecta(int n);
};

long Funciones::sumaIterativa(int n){
  int sum = 0;
  for(int i=1; i<=n; i++){
  sum += i;
  }
  return sum;
}

long Funciones::sumaRecursiva(int n){
  if(n <= 1){
	 return n;
  }
	else{
	 return n+sumaRecursiva(n-1);
  }
}

long Funciones::sumaDirecta(int n){
  int sum;
  sum = ((n+1)*n)/2;
  return sum;
}


#endif /* FUNCIONES_H_ */
