#include <fstream>
#include <iostream>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::ofstream;

#include <math.h>
#include <stdlib.h>

int maxWidth = 0;
int numCount = 0;
void readArr(int, int, double **, double *);
void formatz(double **, double *, int, int);

int main(int argc, char *argv[])
{
  int r = atoi(argv[1]);
  int c = atoi(argv[2]);


  double **A = new double*[r];
  for (int i = 0; i < r; i++)
    A[i] = new double[c]; 
  
  double *rowCounts = new double[r];

  readArr(r, c, A, rowCounts);

  // print answer
  cout << r << endl;
  formatz(A, rowCounts, r, c);
  cout << numCount << endl;
}


void readArr(int r, int c, double **arr, double *rowCounts)
{
  for(int i=0; i<r; i++){
    int numRow = 0;
    for(int j=0; j<c; j++){
      cin >> arr[i][j];
      if(arr[i][j]!=0){
        numRow++;
        numCount++;
        if(j>maxWidth)
          maxWidth=j+1;
      }
    }
    rowCounts[i]=numRow;
  }
}

void formatz(double **input, double *rowCounts, int r, int c)
{
  for(int i = 0; i < r; i++){
    cout << rowCounts[i];
    for(int j = 0; j < c; j++){
      if(input[i][j] != 0){
        cout << " " << (j+1) << " " << input[i][j];
      }
    }
    cout << endl;
  }
}
