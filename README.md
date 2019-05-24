# OpenMPI Laplace Expansion Implementation in C++

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
In summary, Laplace expansion is a method that uses determinants of smaller matrices to find the determinant of a larger square matrix. For a good mathematical explanation you can check the [CliffsNotes](https://www.cliffsnotes.com/study-guides/algebra/linear-algebra/the-determinant/laplace-expansions-for-the-determinant) demonstration. 


## Built With

* [OpenMPI](https://www.open-mpi.org/) - OpenMPI official website
* [GCC](https://gcc.gnu.org/) - GCC, the GNU Compiler Collection
* [Brew](https://brew.sh/) - The missing package manager for macOS (or Linux)

## Versioning

We use [SemVer](http://semver.org/) for versioning. For the versions available, see the [tags on this repository](https://github.com/your/project/tags). 

## Authors

* **Raphael Costa** - [Raphael Costa](https://github.com/raphacosta27)

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* Thanks for some good ideas with this readme style **Billie Thompson** - [PurpleBooth](https://github.com/PurpleBooth)
* Inspiration
* etc 
