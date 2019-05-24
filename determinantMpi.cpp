#include <iostream>
#include <cmath>
#include <mpi.h>

using namespace std;

// #define N 2
#define ERROR 0
#define READY 1

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
            printf("| %f  ", m[i][j]);
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



int main(int argc, char** argv){
    if (argc != 2) {
        std::cerr << "Uso: ./determinantMpi tamanho matriz\n";
        exit(1);
    }
    int N = atoi(argv[1]);
    MPI_Init(&argc, &argv);
    int world_rank; MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    int world_size; MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    double **m1;
    int ready = 0;
    double cof;
    
    if(world_rank == 0){
        m1 = createTestMatrix(N);
        printf("MASTER: Calculating Determinant for the matrix: \n");
        printMatrix(m1, N);

        printf("MASTER: Broadcasting...\n");
        
        for(int i = 0; i<N; i++) {
            MPI_Bcast(&(m1[i][0]), N, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        }

        double det = 0;
        for(int i = 0; i < N; i++){
            MPI_Recv(&cof, 1, MPI_DOUBLE, i+1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            det += m1[0][i] * cof;
        }
        
        std::cout << det << std::endl;
        deleteMatrix(m1, N);
    }
    else{
        printf("%d: waiting for the beggining flag\n", world_rank);
        m1 = alocMatrix(N);
        for (int i = 0; i < N; i++){
            MPI_Bcast(&(m1[i][0]), N, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        }
        printf("%d: starting computing, p: %d\n", world_rank, world_rank-1);
        cof = cofactor(m1, world_rank-1, N);
        MPI_Send(&cof, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    }
    MPI_Finalize();
}