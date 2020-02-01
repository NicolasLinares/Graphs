#include <stdlib.h>  // Funcion exit
#include <string.h>  // Funcion memset
#include <iostream>  // Variables cin y cout
#include <queue>
using namespace std;

#define MAX_NODOS 26

//////////////////////////////////////////////////////////////
////////////        VARIABLES GLOBALES        ////////////////
//////////////////////////////////////////////////////////////

int nnodos;                   // Numero de nodos del grafo
int naristas;                 // Numero de aristas del grafo
bool G[MAX_NODOS][MAX_NODOS]; // Matriz de adyacencia
bool visitado[MAX_NODOS];     // Marcas de nodos visitados

//////////////////////////////////////////////////////////////
////////////     FUNCIONES DEL PROGRAMA       ////////////////
//////////////////////////////////////////////////////////////


void leeGrafo (void)
// Procedimiento para leer un grafo de la entrada
{
  cin >> nnodos >> naristas;
  if (nnodos<0 || nnodos>MAX_NODOS) {
    cerr << "Numero de nodos (" << nnodos << ") no valido\n";
    exit(0);
  }
  memset(G, 0, sizeof(G)); // pone a 0 toda la matriz
  char c1, c2;
  for (int i= 0; i<naristas; i++) {  //lee los char y escribe un 1 en la posicion que 
    cin >> c1 >> c2;                 //le corresponde en la matriz
    G[c1-'A'][c2-'A']= true;    
  }
}

void bpp(int v)
// Procedimiento recursivo de la busqueda primero en profundidad
//   v - primer nodo visitado en la bpp
{
  visitado[v]= true;
  cout << char(v +'A');
  for (int w= 0; w<nnodos; w++)
    if (!visitado[w] && G[v][w])
      bpp(w);
}

void busquedaPP (void)
// Procedimiento principal de la busqueda en profundidad
{
  memset(visitado, 0, sizeof(visitado));
  for (int v= 0; v<nnodos; v++)
    if (!visitado[v])
      bpp(v);
  cout << endl;
}

void bpa(int v)
// Procedimiento recursivo de la busqueda primero en anchura
//   v - primer nodo visitado en la bpa
{
  visitado[v]= true;
  //crear cola
  queue<int> C;
  //insertamos en la cola C, el elemento v
  C.push(v);
  //while(cola C no sea vacia) {
  while (!C.empty()){
  //  x= frente de C
	  int x = C.front();
	  cout << char(x + 'A') ;
  //  suprimeCola C
	  C.pop();
	  
	  for (int w= 0; w< nnodos; w++)
		if (!visitado[w] && G[x][w]){
		  visitado[w]= true;
		  //inserta en la cola C, el elemento w
		  C.push(w);
	  }
  }
	
}

void busquedaPA (void)
// Procedimiento principal de la busqueda en anchura
{
  memset(visitado, 0, sizeof(visitado));
  for (int v= 0; v<nnodos; v++)
    if (!visitado[v])
      bpa(v);
  cout << endl;
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
		busquedaPA();
	  }
}
