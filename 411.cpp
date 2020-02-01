#include <stdlib.h>  // Funcion exit
#include <string.h>  // Funcion memset
#include <iostream>  // Variables cin y cout
#include <queue>
using namespace std;

#define MAX_NODOS 1000

//////////////////////////////////////////////////////////////
////////////        VARIABLES GLOBALES        ////////////////
//////////////////////////////////////////////////////////////

int npersonas;                   // Numero de personas
int npares;                 	 // Numero de pares de personas
int islas;
bool G[MAX_NODOS][MAX_NODOS]; // Matriz de adyacencia
bool visitado[MAX_NODOS];     // Marcas de nodos visitados
int procedencia[MAX_NODOS];   // Apunta la procedencia de cada persona

//////////////////////////////////////////////////////////////
////////////     FUNCIONES DEL PROGRAMA       ////////////////
//////////////////////////////////////////////////////////////


void leeGrafo (void)
// Procedimiento para leer un grafo de la entrada
{
  cin >> npersonas >> npares;
  if (npersonas<0 || npersonas>MAX_NODOS) {
    cerr << "Numero de personas (" << npersonas << ") no valido\n";
    exit(0);
  }
  
  memset(G, 0, sizeof(G)); 
  
  int p1, p2;
  for (int i= 0; i<npares; i++) { 
    cin >> p1 >> p2;                 
    G[p1-1][p2-1] = true;     //grafo no dirigido 
	G[p2-1][p1-1] = true;
  }
}

void bpp(int v)
// Procedimiento recursivo de la busqueda primero en profundidad
//   v - primer nodo visitado en la bpp
{
  if (!visitado[v]) procedencia[v]= islas;
  visitado[v]= true;
  
  for (int w= 0; w<npersonas; w++)
    if (!visitado[w] && G[v][w])
      bpp(w);
}

void busquedaPP (void)
// Procedimiento principal de la busqueda en profundidad
{
  islas = 0;
  memset(procedencia, 0, sizeof(procedencia));
	
  memset(visitado, 0, sizeof(visitado));
  for (int v= 0; v<npersonas; v++)
    if (!visitado[v]){
	  islas++;
      bpp(v);
    }
    
    
  //SALIDA
  cout << islas <<  endl;
  for(int i = 0 ; i < npersonas ; i++){
	cout << procedencia[i] << endl;
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
		cout << "Caso " << i+1 << endl;
		leeGrafo();
		busquedaPP();
	  }
}
