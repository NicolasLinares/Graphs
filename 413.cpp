#include <stdlib.h>  // Funcion exit
#include <string.h>  // Funcion memset
#include <iostream>  // Variables cin y cout
#include <math.h>
using namespace std;

#define MAX_NODOS 1000
#define infinito 999999999
//////////////////////////////////////////////////////////////
////////////        VARIABLES GLOBALES        ////////////////
//////////////////////////////////////////////////////////////

int nnodos;                   // Numero de nodos del grafo
int C[MAX_NODOS][MAX_NODOS]; // Matriz de costes


//////////////////////////////////////////////////////////////
////////////     FUNCIONES DEL PROGRAMA       ////////////////
//////////////////////////////////////////////////////////////

struct Colonia {
	 int x;
	 int y;
};

void leeGrafo (void)
// Procedimiento para leer un grafo de la entrada
{
  cin >> nnodos;
  if (nnodos<0 || nnodos>MAX_NODOS) {
    cerr << "Numero de nodos (" << nnodos << ") no valido\n";
    exit(0);
  }
  
  memset(C, 0, sizeof(C)); // pone a 0 toda la matriz
  
  //guardo las coordenadas de las colonias
  Colonia * colonia = new Colonia[nnodos];
  for (int i= 0; i<nnodos; i++) {  
    cin >> colonia[i].x >> colonia[i].y;                 
  }
  
  //relleno la matriz de costes multiplicando todas las colonias entre si
  for (int i= 0; i<nnodos; i++) {  
    for (int j= 0; j<nnodos; j++) {   
		C[i][j]= (int)sqrt( (colonia[i].x-colonia[j].x)*(colonia[i].x-colonia[j].x)  +    (colonia[i].y-colonia[j].y)*(colonia[i].y-colonia[j].y));
	}    
  }
  
  delete[] colonia;
  
}

void Prim(){
	int menorCoste[nnodos];
	memset(menorCoste, 0, sizeof(menorCoste)); 
	int masCercano[nnodos];
	memset(masCercano, 0, sizeof(masCercano)); 
		
	int solucion = 0;
	
	for (int i= 1; i< nnodos; i++){
		menorCoste[i] = C[0][i];
		masCercano[i] = 0;
	}
	
	for (int i= 1; i< nnodos; i++){
		int min = menorCoste[1];
		int k = 1;
		for (int j= 2; j< nnodos; j++){
			if( menorCoste[j] < min){ 
				min= menorCoste[j];
				k=j;
			}
		}
		
		solucion= solucion + C[k][masCercano[k]]; //me guardo el coste

		menorCoste[k]= infinito; 
		for (int j= 1; j< nnodos; j++){
			if((C[k][j] < menorCoste[j]) && (menorCoste[j] != infinito)){
				menorCoste[j] = C[k][j];
				masCercano[j] = k;
			}
		}
		
	}

	cout << solucion << endl; 
	
}


//////////////////////////////////////////////////////////////
////////////        PROGRAMA PRINCIPAL        ////////////////
//////////////////////////////////////////////////////////////


int main (void)
{
  int ncasos;
  cin >> ncasos;
	  for (int i= 0; i<ncasos; i++) {
		leeGrafo();
		Prim();
	  }
}
