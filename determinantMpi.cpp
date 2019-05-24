#include <iostream>
#include <cmath>
#include <mpi.h>
#include <vector>

using namespace std;

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

typedef struct Worker{
    int rank;
    int jobs;
    std::vector<int> positions;
} Worker;

int main(int argc, char** argv){
    if (argc != 2) {
        std::cerr << "Uso: ./gettingProcesses tamanho matriz\n";
        exit(1);
    }
    int N = atoi(argv[1]);

    MPI_Init(&argc, &argv);
    int world_rank; MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    int n_processors; MPI_Comm_size(MPI_COMM_WORLD, &n_processors);

    double **m1;

    Worker workers[n_processors-1];
    int remaining_processes = N;
    int remaining_workers = n_processors-1;
    std::vector<int> cofactors (N);
    for (int i=0; i<N; ++i) cofactors[i]=i;
    for (int i = 0; i < n_processors-1; i++){
        int jobs_to_do = ceil(remaining_processes/remaining_workers);
        workers[i].rank = i+1;
        workers[i].jobs = jobs_to_do;
        remaining_processes -= jobs_to_do;
        remaining_workers--;
        for(int j = 0; j < jobs_to_do; j++){
            workers[i].positions.insert(workers[i].positions.begin(), cofactors[0]);
            cofactors.erase(cofactors.begin());
        }
    }
    double det_local = 0;
    double det_total = 0;

    if(world_rank == 0){
        m1 = createTestMatrix(N);

        for(int i = 0; i<N; i++) {
            MPI_Bcast(&(m1[i][0]), N, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        }
        
    }
    else{
        m1 = alocMatrix(N);
        for (int i = 0; i < N; i++){
            MPI_Bcast(&(m1[i][0]), N, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        }

        int workers_index = world_rank-1;
        int jobs = workers[workers_index].jobs;
        
        for (int j = 0; j < jobs; j++){
            int pos = workers[workers_index].positions[j];
            det_local += m1[0][pos] * cofactor(m1, pos, N);
        }
    }

    MPI_Reduce(&det_local, &det_total, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if(world_rank == 0){
        printf("----------WORKERS RELAT ----------\n");
        printf("Number of workers: %d\n", n_processors-1);
        for (int i = 0; i < n_processors-1; i++){
            printf("Worker %d\n", workers[i].rank);
            printf("Jobs: %d\n", workers[i].jobs);
            if(workers[i].jobs > 0){
                printf("Positions in the first line calculated: ");
                for (int j = 0; j < workers[i].jobs; j++){
                    printf("%d ", workers[i].positions[j]);
                }
                printf("\n");
            }
            printf("-------\n");
        }
        printf("----------FINAL RELAT----------\n");
        printf("Calculated Determinant for the matrix: \n");
        printMatrix(m1, N);
        printf("DETERMINANT RESULT: %f\n", det_total);
    }

    deleteMatrix(m1, N);
    MPI_Finalize();
}