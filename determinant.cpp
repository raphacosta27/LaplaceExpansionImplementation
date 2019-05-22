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
    // printf("p: %d\n", p);
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
        // printf("Cofactor, p: %d, n: %d\n", p, n);
        int g = 0; // helpers para inserir na nova matriz, g: linha e h: coluna
        int h = 0;
        double **parcial = alocMatrix(n-1);
        for(int i=1; i<n; i++){ //comeca do 1 pq sempre eliminamos a linha 0, pois fazemos laplace extensor pra primeira linha
            for(int j=0; j<n; j++){
                if(j != p){
                    // printf("adding to parcial matrix. [%d, %d]: %f\n", g, h, matriz[i][j]);
                    parcial[g][h] = matriz[i][j];
                    h++;
                    if(h > nextSize-1){
                        g++;
                        h = 0;
                    }
                }
            }
        }
        // printMatrix(parcial, n-1);
        double calc = 0;
        for (int i=0; i<nextSize; i++){
            // printf("next cofactors: %f\n", parcial[0][i]);
            calc +=  pow(-1, p) * cofactor(parcial, i, nextSize);
        }
        return calc;
    }
}

double determinant(double **matriz){
    double det = 0;
    double **m2;
    // det = cofactor(matriz, 0, N);
    for(int i = 0; i < N; i++){ // p/ cada elemento da primeira linha da matriz
        double cof = cofactor(matriz, i, N);
        printf("Cof of %f: %f\n", matriz[0][i], cof);
        det += matriz[0][i] * cof;
    }
    return det;
}

int main(){
    int i, j;
    
    double **m1 = createTestMatrix(N);
    
    printf("Calculating Determinant for the matrix: \n");
    printMatrix(m1, N);
    std::cout << determinant(m1) << std::endl;

    deleteMatrix(m1, N);
}