#include <iostream>
#include <stack>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <time.h>

using namespace std;

// OMAR RODRIGUEZ ALVAREZ 48679912K

//Leer ficheros
int** leerfichero(int **coste, string ruta, int &tamanyo){

    ifstream fDatos;
    char linea[200], *tok, *tok2, *tok3;
    int aux1, aux2, aux3, n, i, j, **M; 
    
    fDatos.open(ruta);
    fDatos.getline(linea, 200);
    tok=strtok(linea, " \t\r\n");
    tamanyo = atoi(tok);

    // eservamos memoria para la matriz de costes
    coste = new int* [tamanyo+1];

    if(coste == NULL)
        return NULL;

    for( i = 0 ; i <= tamanyo ; i++ ){
        
        coste[i] = new int [tamanyo+1];
        if (coste[i] == NULL)
            return NULL;
    }

    // Rellenamos la matriz y la pintamos
    for(int k = 0; k <= tamanyo; k++)
    {
        for(int z = 0; z <= tamanyo; z++)
        {
            coste[k][z] = 9999;
            // cout << coste[k][z]; // muestra matriz infinita
        }
    }

    while(fDatos.peek() != EOF){
        fDatos.getline(linea, 200);         
        tok=strtok(linea, " \t\r\n");         
        aux1 = atoi(tok);         
        tok=strtok(NULL, " \t\r\n");         
        aux2 = atoi(tok);         
        tok=strtok(NULL, " \t\r\n");         
        aux3 = atoi(tok);          
        coste[aux1][aux2] = aux3;
    }

    fDatos.close();
    return coste;

}

void Mostrar_matriz(int **coste, int tamanyo){

    for(int k = 0; k <= tamanyo; k++)
    {
        for(int z = 0; z <= tamanyo; z++)
        {
            cout << coste[k][z] << " ";
        }

        cout << endl;
    }
}

int calcularcoste(int** coste, int* vector, int tamanyo){

    float suma = 0;
    int i;
    int k = 0;

    for (i = 1; i <= tamanyo; i++)
    {
        suma = suma + coste[k][vector[i]];
        k = vector[i];

        if (i == tamanyo)
        {
            suma = suma + coste[vector[i]][0];
        }
    }
    return suma;
}

bool ciclos(int* vector, int k){
    cout << "entra en ciclos??" << endl;
    int i, j;

    for( i = 1 ; i <= k ; i++){
        for( j = i + 1 ; j <= k ; j++){

            cout << "i: " << i << endl;
            cout << "j: " << j << endl;


            if(vector[j] == vector[i]){
                cout << endl << "devuelve true" << endl;
                return true;
            }
        }
    }   
    cout << endl << "devuelve false" << endl;
    return false;
}

// Viajante de comercio T6 VUELTA ATRAS

void f_viajante(int** coste, int* vector, int* voptimo, int &costeoptimo, int k, int tamanyo, int &x, int ocultar){
    
    int costev, i;
    vector[0] = 0;

    while(k>=1){
        if(vector[k] != tamanyo){

            vector[k] = vector[k]+1;
            cout << "valor de k " << k << endl;
            cout << "[k-1]=" << vector[k-1] << endl;
            cout << "[k]=" << vector[k] << endl;
            cout << "coste vector: " << coste[vector[k-1]][vector[k]] << endl;
            
           if(coste[vector[k-1]][vector[k]] != 9999 &&  ciclos(vector, k) == false){
               
                // cout << "entra2?" << endl;
                if( k == tamanyo ){
                    if(coste[k][0] != 9999){
                        // cout << "entra3?" << endl;
                        costev = calcularcoste(coste, vector, tamanyo);

                        for(int p=0; p<= tamanyo; p++){
                            cout << vector[p] << " ";
                        }
                        cout << endl;
                        if(costev < costeoptimo){
                            // cout << "entra4?" << endl;
                            costeoptimo = costev;
                            for(int y=0; y<= tamanyo; y++){
                                voptimo[y]=vector[y];
                            }
                        }
                    }
                }else{
                   k = k+1;
                   vector[k]=0;

                   cout << "k: " << k << endl;
                   cout << "vector [k]: " << vector[k] << endl;
                }   
            }  
        }
        else{
            // vector[k]=0;
            k = k-1;
        }
        
    }
    // system("pause");
}


int main(){

    //aux tem
    int uno=1;


    int **coste=NULL, costeoptimo = 9999, k = 1, i, j, x = 0, y;
    int opcion, tamanyo, ocultar=0;
    string ruta= "3clientes.txt";


    // siempre true
    while(uno = 1){

        cout << "1. Obtener lista de clientes" << endl; 
        cout << "2. Ocultar listado de recorridos en opcion" << endl;
        cout << "3. Listado de recorridos resaltando el mas corto" << endl;
        cout << "4. Recorrido mas corto (Algoritmo mejorado)" << endl;
        cout << "5. Salir" << endl;

        cin >> opcion;

        if(opcion == 1){
            cout << endl << "Por favor, diga el nombre del fichero.txt" << endl;
            // cin >> ruta;

            // procedemos a leer el fichero
            coste = leerfichero(coste, ruta, tamanyo);

            // Mostramos la matriz de adyacencia entre cada vertice y sus pesos 
            cout << endl << "Matriz [A] de pesos VERTICE - VERTICE" << endl;
            Mostrar_matriz(coste, tamanyo);
            
           cout << endl;

        }
        else if(opcion == 2){
            cout <<endl << "Activado modo oculto" << endl;
            // activamos modo oculto
            ocultar = 1;
        }
        else if(opcion == 3){
            
                // vector usado para hacer la vuelta atras
                int *vector = new int [tamanyo+1];

                // vector solucion
                int *voptimo = new int [tamanyo+1];

                // inicializamos los vectores
                for(i=0; i<= tamanyo; i++){
                    vector[i]=0;
                    voptimo[i]=0;
                }

                f_viajante(coste, vector, voptimo, costeoptimo, k, tamanyo, x, ocultar);

                cout << "Camino actual / final: " ;

                for(int y=0; y<= tamanyo; y++){

                    cout << voptimo[y] << " - ";

                }
                cout << "0." << endl;

        }
        else if(opcion == 4){
            cout << "opcion 4" << endl;
        }
        else if(opcion == 5){
            return -1;
        }

        //desactivamos modo oculto
        ocultar = 0;
        uno = 0;

    }
    
    system("pause");

}