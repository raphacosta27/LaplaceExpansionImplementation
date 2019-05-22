#include <iostream>
#include <cmath>
using namespace std;

#define N 4

double ** createTestMatrix(int n){
    double **m = new double *[n];
    int c = 1;
    for (int i = 0; i < n; ++i) m[i] = new double[n];
    for (int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            m[i][j] = c;
            c++;
        }
    }  
    return m;
}

double ** alocMatrix(int n){
    double **m = new double *[n];
    for (int i = 0; i < n; ++i) m[i] = new double[n];
    for (int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            m[i][j] = 0;
        }
    } 
    
    return m;
}

void deleteMatrix(double **m, int n){
    for (int i = 0; i < n; ++i) delete [] m[i];
    delete [] m;
}

void printMatrix(double **m, int n){
    for (int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("| %f  ", i, j, m[i][j]);
        }
        printf("\n");
    } 
    printf("\n");
}

double cofactor(double **matriz, int p, int n){
    printf("p: %d\n", p);
    // matriz: matriz
    // p: posicao que esta sendo calculada
    // n: tamanho da matriz
    if(n == 1){
        return matriz[0][0];
    }
    else{
        int nextSize = n-1;
        //primeiro: prepara matriz sem a linha e a coluna da posicao
        //segundo: faz a determinante pro cofactor
        printf("Cofactor, p: %d, n: %d\n", p, n);
        int g, h = 0; // helpers para inserir na nova matriz, g: linha e h: coluna
        double **parcial = alocMatrix(N);
        for(int i=1; i<N; i++){ //comeca do 1 pq sempre eliminamos a linha 0, pois fazemos laplace extensor pra primeira linha
            for(int j=0; j<N; j++){
                if(j != p){
                    // printf("adding to parcial matrix. [%d, %d]: %ld\n", i, j, matriz[i][j]);
                    parcial[g][h] = matriz[i][j];
                    h++;
                    if(h > nextSize-1){
                        g++;
                        h = 0;
                    }
                }
            }
        }
        printMatrix(parcial, N);
        return parcial[0][0];
    }
}

double determinant(double **matriz){
    double det = 0;
    double **m2;
    cofactor(matriz, 1, N);
    // for(int i = 0; i < N; i++){ // p/ cada elemento da primeira linha da matriz
    //     cofactor(matriz, i, N);
    // }
    return det;
}

int main(){
    int i, j;
    
    double **m1 = createTestMatrix(N);
    

    // m1[0][0] = (double) 1;
    // m1[0][1] = (double) 2;
    // m1[0][2] = (double) 3;
    // m1[1][0] = (double) 4;
    // m1[1][1] = (double) 5;
    // m1[1][2] = (double) 6;
    // m1[2][0] = (double) 7;
    // m1[2][1] = (double) 8;
    // m1[2][2] = (double) 9;
    printf("Calculating Determinant for the matrix: \n");
    printMatrix(m1, N);

    determinant(m1);
    // std::cout << determinant(m1, n) << std::endl;

    deleteMatrix(m1, N);
}