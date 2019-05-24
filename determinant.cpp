#include <iostream>
#include <cmath>
#include <x86intrin.h> //Extensoes SSE
#include <bits/stdc++.h> //Bibliotecas STD
using namespace std;
using namespace std::chrono;

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
    if(n == 1){
        return matriz[0][0];
    }
    else{
        int nextSize = n-1;
        int g = 0;
        int h = 0;
        double **parcial = alocMatrix(n-1);
        for(int i=1; i<n; i++){
            for(int j=0; j<n; j++){
                if(j != p){
                    parcial[g][h] = matriz[i][j];
                    h++;
                    if(h > nextSize-1){
                        g++;
                        h = 0;
                    }
                }
            }
        }
        double calc = 0;
        for (int i=0; i<nextSize; i++){
            calc +=  pow(-1, p) * cofactor(parcial, i, nextSize);
        }
        deleteMatrix(parcial, nextSize);
        return calc;
    }
}

double determinant(double **matriz, int N){
    double det = 0;
    double **m2;
    for(int i = 0; i < N; i++){
        double cof = cofactor(matriz, i, N);
        // printf("Cofactor of %f: %f\n", matriz[0][i], cof);
        det += matriz[0][i] * cof;
    }
    return det;
}

int main(int argc, char** argv){
    if (argc != 2) {
        std::cerr << "Uso: ./gettingProcesses tamanho matriz\n";
        exit(1);
    }
    int N = atoi(argv[1]);

    int i, j;

    double **m1 = createTestMatrix(N);
    
    printf("Calculating Determinant for the matrix: \n");
    printMatrix(m1, N);
    auto now = high_resolution_clock::now();
    double d = determinant(m1, N);
    auto end_time = duration_cast<duration<double>>(high_resolution_clock::now() - now).count();
    std::cout << "D |m| = "<< d << std::endl;
    std::cout << "Time: " << end_time << "\n";
    deleteMatrix(m1, N);
}