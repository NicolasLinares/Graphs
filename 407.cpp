#include <stdlib.h>  // Funcion exit
#include <string.h>  // Funcion memset
#include <iostream>  // Variables cin y cout
#include <math.h>
#include <list>
using namespace std;

#define MAX_NODOS 200
//////////////////////////////////////////////////////////////
////////////        VARIABLES GLOBALES        ////////////////
//////////////////////////////////////////////////////////////

int nnodos;                   // Numero de nodos del grafo
int MC[MAX_NODOS][MAX_NODOS]; // Matriz de costes
string ciudades[MAX_NODOS];
int D[MAX_NODOS][MAX_NODOS];   //Costes de caminos mínimos
//////////////////////////////////////////////////////////////
////////////     FUNCIONES DEL PROGRAMA       ////////////////
//////////////////////////////////////////////////////////////

void leeGrafo (void)
// Procedimiento para leer un grafo de la entrada
{
  cin >> nnodos;
  if (nnodos<0 || nnodos>MAX_NODOS) {
    cerr << "Numero de nodos (" << nnodos << ") no valido\n";
    exit(0);
  }
  
  memset(MC, 9999999, sizeof(MC)); 
  
  cin.ignore();
  for (int i= 0; i<nnodos; i++) {  
    getline(cin, ciudades[i]);             
  }
  
  //relleno la matriz de costes
  int c1, c2, distancia;
  while((cin >> c1 >> c2 >> distancia )){
	if (c1 == 0 && c2 == 0 && distancia == 0) break;
	MC[c1][c2]= distancia;       //grafo no dirigido
	MC[c2][c1]= distancia;
  }
  
}


void calcularExcentricidad(){
	//calcular la excentricidad
	int indice = 0;
	int menorDistancia = 9999999; 
	string ciudad= "z";
	
	for (int i=0; i < nnodos ; i++){
		int mayorDistancia = 0;
		for (int j=0; j < nnodos ; j++){
			if ( D[i][j] > mayorDistancia  ){
				mayorDistancia = D[i][j];	
			}
		}
		
		if (menorDistancia > mayorDistancia ){
			menorDistancia = mayorDistancia; 
			ciudad=ciudades[i] ;
			indice = i;
		}else if (menorDistancia == mayorDistancia && ciudades[i] < ciudad){
			ciudad=ciudades[i] ;
			indice = i;
		}
		
	}

	cout << ciudades[indice] << endl << menorDistancia << endl;
}

void Floyd(){

	memset(D, 9999999, sizeof(D));
	
	for (int i=0; i < nnodos ; i++){
		for (int j=0; j < nnodos ; j++){
			D[i][j]= MC[i][j];
		}
		D[i][i] = 0;
	}
	
	for(int k=0; k < nnodos ; k++){
		for (int i=0; i < nnodos ; i++){
			for (int j=0; j < nnodos ; j++){
				if(D[i][j] > (D[i][k] + D[k][j]) && (D[i][k] + D[k][j]) > 0) {  
					D[i][j] = D[i][k] + D[k][j];
				}
			}	
		}

	}

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
		Floyd();
		calcularExcentricidad();
	  }
}
