# Recursive Laplace Expansion optimised with OpenMPI in C++

The object of this project is to implement the Laplace Expansion (also called Cofactor Expansion) method for computing the determinant |A| of an n x n matrix A. Also, to study the tool of OpenMPI, there`s an optmised version using multicores and distributed memory. 

## Getting Started
To get a copy of the project, clone this repository.
```python
git clone https://github.com/raphacosta27/LaplaceExpansionImplementation
cd LaplaceExpansionImplementation
```

### Prerequisites

To run the file determinant.cpp, you just have to install g++. To compile it, I used the g++-9.
On Mac:
```
brew install gcc
g++-9 -v
```
Also, to use the MPI optmised version, you have to install the OpenMPI lib for gcc. 
On Mac:
```
brew install open-mpi 
```
For other OS, check the OpenMPI official website linked in some sections below for installation instructions.

### The Laplace Expansion method
In summary, Laplace expansion is a method that uses determinants of smaller matrices to find the determinant of a larger square matrix. For a good mathematical explanation you can check the [CliffsNotes](https://www.cliffsnotes.com/study-guides/algebra/linear-algebra/the-determinant/laplace-expansions-for-the-determinant) demonstration. Also, my version is able to calculate only the Laplace Expansion for the first line of a given matrix. In CliffsNotes explanation, you will see that you can find the determinant of a matrix using the method for any line or any column.

### Running raw implementation
As I said, to see the raw implementation of the method, you can compile and run determinant.cpp. 
```C++
g++-9 determinant.cpp -o determinant
./determinant N
```
It requires a N input in command line, which corresponds for the matrix size. The pattern is to test with a matrix of size N and values beggining in 1 and going until N. So:

```C++
./determinant 3
Calculating Determinant for the matrix: 
| 1.000000  | 2.000000  | 3.000000  
| 4.000000  | 5.000000  | 6.000000  
| 7.000000  | 8.000000  | 9.000000  

D |m| = 0
Time: 1.2e-05s
```

### The OpenMPI Implementation
The OpenMPI implementation is avaiable in the file determinantMpi.cpp. to run:
```C++
mpic++ determinantMpi.cpp -o determinantMpi
mpirun determinantMpi N
```
The same as the raw implementation, it also requires a N input corresponding for the size of the test matrix. Also, in MPI you can specify how much cores you want to distribute the execution. The example above will run with all avaiable cores in your machine. To use with a specific number of cores, you should run with mpirun -n nCores determinantMpi N.
```C++
mpirun -n 4 determinantMpi 3
```
The MPI optimisation
#### Master:
- Get the max cores avaiable 
- The number of jobs corresponds to the size of the input matrix.
- Determine how many and what Cofactors which core will calculate. Ex: For an 8x8 matrix, Worker 1 will calculate 2 cofactors and Workers 2 and 3 will calculate 3 cofactors. 
- Creates the matrix to be calculated.
- Uses MPI_Broadcast to send the matrix to its workers.
#### Workers:
- The workers do the number of jobs that the master determined for them. 
- Send back the local results via MPI_Reduce instruction
Finally, the master shows the final result and the report of the work. Eg:

```C++
----------WORKERS REPORT----------
Number of workers: 3
Worker 1
Jobs: 1
Positions in the first line calculated: 0 
-------
Worker 2
Jobs: 1
Positions in the first line calculated: 1 
-------
Worker 3
Jobs: 2
Positions in the first line calculated: 3 2 
-------
----------FINAL REPORT----------
Calculated Determinant for the matrix: 
| 1.000000  | 2.000000  | 3.000000  | 4.000000  
| 5.000000  | 6.000000  | 7.000000  | 8.000000  
| 9.000000  | 10.000000 | 11.000000 | 12.000000  
| 13.000000 | 14.000000 | 15.000000 | 16.000000  

DETERMINANT RESULT: 0.000000
```

## Built With

* [OpenMPI](https://www.open-mpi.org/) - OpenMPI official website
* [GCC](https://gcc.gnu.org/) - GCC, the GNU Compiler Collection
* [Brew](https://brew.sh/) - The missing package manager for macOS (or Linux)

## Authors

* **Raphael Costa** - [raphacosta27](https://github.com/raphacosta27)

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* Thanks for some good ideas with this readme style **Billie Thompson** - [PurpleBooth](https://github.com/PurpleBooth)
