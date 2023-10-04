using namespace std;
#include <iostream>
#include <vector>
#include <fstream>
#include <limits>
const int INF = numeric_limits<int>::max();
int vertices = 0;
bool existenciaDeFuentesYpozos = false;

int retornarVertice(){
	return vertices;
}
void imprimirMatriz(vector<vector<int>>& matriz){
	//imprimir vertices horizontalmente
	cout<<"  ";
	for(int k = 0; k < vertices; k++){
		
    	char verticeColumnas = 'A' + k;
    	cout<<verticeColumnas<<" ";
	}
	cout<<endl;
		
	for (int i = 0; i < vertices; i++) {
    	//imprimir vertices verticalmente
    	char verticeFilas = 'A' + i;
    	cout<<verticeFilas<<" ";
			
        for (int j = 0; j < vertices; j++) {
            cout << matriz[i][j] << " ";
        }  
        cout << endl;
    }	
}

void determinarNodosFuentes(vector<vector<int>>& matriz){
    for (int i = 0; i < vertices; ++i) {
    	bool fuente = true;
		for(int j = 0; j < vertices; j++){
			if(matriz[j][i] != 0){
				fuente = false;
			}
		} 
		
		if(fuente){		
			for(int j = 0; j < vertices; j++){
				if(matriz[i][j]!=0){
					char verticeFuente= 'A' + i;
					cout<< "el vertice "<<verticeFuente<<" es un vertice fuente"<<endl;	
					existenciaDeFuentesYpozos = true;				
				}
			}
		} 
			  
    }
}

void determinarNodosPozos(vector<vector<int>>& matriz){

    for (int i = 0; i < vertices; ++i) {
    	bool pozo = true;
		for(int j = 0; j < vertices; j++){
			if(matriz[i][j]!=0){
				pozo = false;
			}
		}
		
		if(pozo){
			bool llegoAlgunaArista = false;
			for(int j = 0; j < vertices; j++){
				if(matriz[j][i]!=0){
					char verticeFuente= 'A' + i;
					cout<< "el vertice "<<verticeFuente<<" es un vertice pozo"<<endl;
					existenciaDeFuentesYpozos = true;
				}	
			}
		}
    }  
}



bool determinarGrafoConexo(vector<vector<int>>& matrizCierreTransitivo){
	bool conexo = true;
	for(int i = 0; i < vertices; i++){
		for(int j = 0; j < vertices; j++){
			if(i != j && matrizCierreTransitivo[i][j] != 0){
				conexo = false;
			}			
		}
	}


	if(conexo){
		for(int i = 0; i < vertices; i++){
			for(int j = 0; j < vertices; j++){
				if(i == j && matrizCierreTransitivo[i][j] == 0){
					conexo = false;
				}			
			}
		}
	}
	
	return conexo;
}



void crearMatrizDeCierreTransitivo(vector<vector<int>>& matriz){
	vector<vector<int>> matrizDeCierre(vertices, vector<int>(vertices, 0));
	
	for(int i = 0; i < vertices; i++){
		for(int j = 0; j < vertices ; j++){
			matrizDeCierre[i][j] = matriz[i][j];
		}
	}
	
    for(int r = 0; r < vertices; r++){
        for (int j = 0; j < vertices; j++) {     
            if(	matrizDeCierre[r][j]!=0){
            	matrizDeCierre[r][j]  = 1;       	
			}
           
        }	
	}		
	for(int k = 0; k < vertices; k++){
		for(int i = 0; i < vertices; i++){
			for(int j = 0; j  < vertices; j++){
				if(matrizDeCierre[k][j] == 1 && matrizDeCierre[i][k] == 1 ){
					matrizDeCierre[i][j] = 1;
				}
			}
		}
	}
	
	
	cout<<"matriz de cierre transitivo"<<endl;
	imprimirMatriz(matrizDeCierre);
	
	if(!determinarGrafoConexo(matrizDeCierre)){
		cout<<"no es conexo"<<endl;
		cout<<endl;
		cout<<"A partir de la matriz de adyasencia se puede determinar: "<<endl;
		determinarNodosFuentes(matriz);
		determinarNodosPozos(matriz);
		if(!existenciaDeFuentesYpozos){
			cout<<"No hay ningun pozo o fuente"<<endl;			
		}else{
			existenciaDeFuentesYpozos = false;
		}
		
		
	}else{
		cout<<"es conexo"<<endl;	
	}
	
}




void eliminarVertice(vector<vector<int>>& matriz){
	
	char verticeEliminar;
	cout<<"ingrese la letra del vertice que quieres eliminar: ";
	cin>>verticeEliminar;
	
	int indiceVerticeEliminar = verticeEliminar - 'A';

	for(int j = 0; j < vertices; j++){
		matriz[j][indiceVerticeEliminar] = 0;
	}
	
	for(int i = 0; i < vertices; i++){
		matriz[indiceVerticeEliminar][i] = 0;
	}
	
	cout<< "el vertice "<<verticeEliminar<<" ha sido eliminado"	<<endl;
	imprimirMatriz(matriz);
	
}


void dijkstra(vector<vector<int>>& matriz, int nodoInicio, int nodoDestino) {
    vector<int> distancia(vertices, INF);
    vector<bool> visitado(vertices, false);

    distancia[nodoInicio] = 0;

    for (int count = 0; count < vertices - 1; ++count) {
        int u = -1;
        for (int i = 0; i < vertices; ++i) {
            if (!visitado[i] && (u == -1 || distancia[i] < distancia[u])) {
                u = i;
            }
        }

        if (distancia[u] == INF) {
            break; 
        }

        visitado[u] = true;

        for (int v = 0; v < vertices; ++v) {
            if (!visitado[v] && matriz[u][v] && distancia[u] != INF &&
                distancia[u] + matriz[u][v] < distancia[v]) {
                distancia[v] = distancia[u] + matriz[u][v];
            }
        }
    }

    if (distancia[nodoDestino] == INF) {
        cout << "No hay camino entre los vertices " << char('A' + nodoInicio)
             << " y " << char('A' + nodoDestino) << endl;
    } else {
        cout << "La distancia mas corta entre los vertices " << char('A' + nodoInicio)
             << " y " << char('A' + nodoDestino) << " es: " << distancia[nodoDestino] << endl;
    }
}


void ingresarVerticesParaDjkastra(vector<vector<int>>& matriz){
	char nodoInicio;
	char nodoDestino;
    cout << "Ingrese el vertice de inicio: ";
    cin >> nodoInicio;
    cout << "Ingrese el vertice de destino: ";
    cin >> nodoDestino;

    int indiceInicio = nodoInicio - 'A';
    int indiceDestino = nodoDestino - 'A';

    dijkstra(matriz, indiceInicio, indiceDestino);

}

int main(){
	char origen;
	int peso;
	char destino;

	
	ifstream obj("arista.txt");
	bool primeraLinea = true;
	
	obj>>vertices;
	vector<vector<int>> matriz(vertices, vector<int>(vertices, 0));
	
	for(int i = 0; i < vertices; i++){
		for(int j = 0; j < vertices; j++){
			matriz[i][j] = 0;
		}
	}
	
	while(obj>>origen){
			obj>>destino;
			obj>>peso;
			
			//cout<<origen<<"-"<<destino<< "-" <<peso<<endl;
			matriz[origen - 'A'][destino- 'A'] = peso;
			
	}
	
	cout<<"matriz de adyascencia del grafo"<<endl;
	imprimirMatriz(matriz);
	cout<<endl;
	
	
	
	int opcion;
	while(opcion != 4 || opcion > 4 || opcion < 1){
		
		if(opcion > 4 || opcion < 1){
			cout<<"solo puedes digitar un numero del 1 al 4, intentalo denuevo"<<endl;
		}
		cout<<"1-Aplicar Warshall"<<endl;
		cout<<"2-eliminar vertice del grafo"<<endl;
		cout<<"3-Utilizar djkastra para determinar el camino mas corto entre 2 vertices"<<endl;
		cout<<"4-Salir"<<endl;	
		cout<<"digite la opcion que desea ejecutar: ";
		cin>>opcion;
		cout<<'\n';
		switch(opcion){
			case 1: 
				crearMatrizDeCierreTransitivo(matriz);
				break;
			case 2:
				eliminarVertice(matriz);
			
				break;
			case 3:
			 	ingresarVerticesParaDjkastra(matriz);	
				 break;	
		}
		
		cout<<endl;
	}

}
