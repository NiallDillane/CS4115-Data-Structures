#include <fstream>
#include <iostream>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::ofstream;

#include <math.h>
#include <stdlib.h>

void readArr(int, int, double **);
void multArrs(int, double **, int, double **, int, double **);

int main(int argc, char *argv[])
{
  int ar = atoi(argv[1]);
  int ac = atoi(argv[2]);
  int br = atoi(argv[3]);
  int bc = atoi(argv[4]);

  if (ac != br)
  {
    cerr<< "Matrix dimensions mismatch; exiting.\n";
    exit(-1);
  }

  // reserve space for the three arrays
  double **A = new double*[ar];  // each el. of this points to a row of A
  for (int i = 0; i < ar; i++)
    A[i] = new double[ac]; // a row of 'ac' floats

  double **B = new double*[br];
  for (int i = 0; i < br; i++)
    B[i] = new double[bc]; // a row of 'bc' floats

  double **C = new double*[ar];  
  for (int i=0; i<ar; i++)
   C[i] = new double[bc]; // ar rows, bc cols

  readArr(ar, ac, A);
  readArr(br, bc, B);

  multArrs(ar, A, bc, B, ac, C);

  // print out answer
  for(int i=0; i<ar; i++){
      for(int j=0; j<bc; j++){
         cout << C[i][j] << " ";
      }
      cout << endl;
   }
}

// read from kbd into this array, row by row
//  for a total of r * c entries;
void readArr(int r, int c, double **arr)
{
  for(int i=0; i<r; i++){
    for(int j=0; j<c; j++){
      cin >> arr[i][j];
    }
  }
}

void multArrs(int ar, double **A, int bc, double **B, int br, double **C)
{
   for(int i=0; i<ar; i++){
      for(int j=0; j<bc; j++){
         for(int k=0; k<br; k++){
            C[i][j]+=A[i][k]*B[k][j];
         }
      }
   }
}
