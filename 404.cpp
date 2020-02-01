#include <stdlib.h>  // Funcion exit
#include <string.h>  // Funcion memset
#include <iostream>  // Variables cin y cout
using namespace std;


#define MAX_NODOS 2000


//////////////////////////////////////////////////////////////
////////////        VARIABLES GLOBALES        ////////////////
//////////////////////////////////////////////////////////////

int nnodos, naristas, A, B, C, resultadoCamino;
int MC[MAX_NODOS][MAX_NODOS]; // Matriz de costes

//////////////////////////////////////////////////////////////
////////////     FUNCIONES DEL PROGRAMA       ////////////////
//////////////////////////////////////////////////////////////


void leeGrafo (void)
{
	memset(MC, 0, sizeof(MC));
	
	cin >> nnodos;
	cin >> naristas;
	cin >> A >> B >> C;
	
	
	int n1, n2 , a;
	for(int i=0; i<naristas ; i++) {  
		cin >> n1 >> n2 >> a; 
		MC[n1-1][n2-1] = a;     
		MC[n2-1][n1-1] = a;
		
	}
	
}

bool Dijkstra(int nodoOrigen, int nodoLlegada){
	int D[nnodos];   //Costes de caminos mínimos
	memset(D, 0, sizeof(D));
	
	bool T[nnodos];  //Nodos escogidos
	memset(T, 0, sizeof(T));

	for (int i=0; i < nnodos  ; i++){
		D[i]= MC[nodoOrigen-1][i];
	}
	
	int v=nodoOrigen; 
	T[v-1] = true;
	
	for(int i=0; i < nnodos  ; i++){

		//v:= nodo con S[v]==FALSE y mínimo D[v]
		int j=0;
		int coste=9999999; //le asigno un numero muy grande para que coja el primero que sea menor que él
		while(j < nnodos ){		
			if( T[j] == false && 0 < D[j] && D[j] < coste){
				v=j+1;
				coste= D[j];
			}	
			j++;
		}
		
		T[v-1] = true;
		
		for(int w=0; w < nnodos  ; w++){
			
			if(T[w]== false && D[w]!= 0 && MC[v-1][w] != 0 &&  ((D[v-1] + MC[v-1][w]) < D[w])){
				D[w]= D[v-1] + MC[v-1][w];
			}else if (T[w]== false && D[w]== 0 && MC[v-1][w] != 0 ){  //agrego este caso ya que si en D el coste es 0 que es lo mismo que infinito debemos ponerlo tambien
				D[w]= D[v-1] + MC[v-1][w];							  //este caso solo lo utilizará en la primera iteracióin cuando hay huecos que son 0 (no asignados todavía)
			}
			

		}

	}

	
	if (nodoOrigen == nodoLlegada || D[nodoLlegada-1] != 0) {
		resultadoCamino = resultadoCamino + D[nodoLlegada-1];
		return true;
	}else return false;
}

//////////////////////////////////////////////////////////////
////////////        PROGRAMA PRINCIPAL        ////////////////
//////////////////////////////////////////////////////////////

int main (void)
{
	int ncasos;
	cin >> ncasos;
	for (int i= 0; i<ncasos; i++) {
		resultadoCamino=0;
		leeGrafo();
		
		
		if (Dijkstra(A, C)) {
			if (Dijkstra(C, B)){
				cout << resultadoCamino << endl;
			}else cout << "IMPOSIBLE" << endl;
		}else cout << "IMPOSIBLE" << endl;
	}
}
