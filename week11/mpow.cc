
#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include <vector>
#include <cmath>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::list;
using std::vector;
using std::istringstream;
using std::ostream;

#include <math.h>
#include <stdlib.h>

#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define MAX(a,b) ((a) > (b) ? (a) : (b))

class nz {	    // one instance for every non-zero entry in matrix
public:
  nz() { ind = 0; val = 0.0; }
  nz(int i, double v) {	// constructor when given the two items of data
    ind = i;
    val = v;
  }
  int getInd() const { return ind; } // access to ind class member
  double getVal() const { return val; } // access to val class member
  friend istringstream& operator>>(istringstream& is, nz& base);
  friend ostream& operator<<(ostream &os, const nz& base);

private:
  int ind;
  double val;
};
istringstream& operator>>(istringstream& is, nz& base)
{
  is>> base.ind;
  is>> base.val;
  return is;
}
ostream& operator<<(ostream &os,const nz& base)
{
  os<< base.ind<< " "<< base.val<< " ";
  return os;
}

bool isInt(char *str){
  while (*str != 0){
    if (!isdigit(*str++)) {
	return false;
    }
  }
  return true;
}

typedef list<nz> sparseRow;
typedef vector<sparseRow> sparseMat;

sparseMat logPower(sparseMat, int);
void readMat(sparseMat&, int&);
void powerZero(int&);
void transpMat(const sparseMat, sparseMat);
sparseMat multMat(sparseMat, sparseMat);
double dotProd(const sparseRow, const sparseRow);
void outMat(const sparseMat);

double epsilon = 0.0;

int main(int argc, char *argv[])
{
  if(argc !=2){
    cout << "Incorrect input format; exiting." << endl;
    exit(0);
  }

  if(!isInt(argv[1])){
    cout << "Input must be an integer; exiting." << endl;
    exit(0);
  }
  
  float in = strtof(argv[1], 0);
  if (!(floor(in) == ceil(in))){
      cout << "Input must be an integer; exiting." << endl;
      exit(0);
  }
  
  int pow = in;
  if(pow < 0){
      cout << "Illegal exponent; exiting." << endl;
      exit(0);
  }
    
  int colct;
  sparseMat rows;
  readMat(rows, colct);

  if(pow == 0)
    powerZero(colct);
  else if(pow == 1)
    outMat(rows);
  else{
    /*sparseMat prod1=rows, prod2=rows;
    for(int i=1; i<pow; i++){
      multMat(rows, prod1, prod2);
      prod1=prod2;
    }
    outMat(prod2);*/
    outMat(logPower(rows, pow));
  }
}

sparseMat logPower(sparseMat rows, int pow){
  sparseMat prod, prodT;
  prod = logPower(rows, floor(pow/2));
  if(pow % 2 == 0){
    return multMat(prod, prod);
  }
  else{
    prodT = multMat(prod, prod);
    return multMat(prodT, rows);
  }
}

void readMat(sparseMat& rows, int& colct)
{
  colct = 0;
  string line;
  while (getline(cin, line))	// get next full line of text; NB: text
  {
    istringstream lstream(line);
    sparseRow row;

    nz next;
    while (lstream>> next) { // peel off values in this line, one at a time
      row.push_back(next);

      int col = next.getInd();
      if (colct < col) colct = col; // remember largest
    }

    rows.push_back(row);
  }
}

void powerZero(int& colct){
  for(int i = 0; i < colct; i++){
    cout << (i+1) << " " << "1" << endl;
  }
}

void transpMat(const sparseMat rows, sparseMat transp)
{
  for (unsigned int c = 0; c < rows.size(); c++)
  {
    sparseRow row;
    transp.push_back(row);	// initialise every row of transpose
  }

  vector<sparseRow>::const_iterator rit; // we only want to /read/ list
  int rowind;
  for (rit = rows.begin(), rowind = 1; rit != rows.end(); rit++, rowind++)
  {
    sparseRow row = *rit;
    sparseRow::const_iterator nzit;
    for (nzit = row.begin(); nzit != row.end(); nzit++)
    {
      int col = nzit->getInd();
      double val = nzit->getVal();
      transp[col-1].push_back(nz(rowind,val));
      //      cout<< "Put val from "<< rowind<< " on col "<< col<< endl;
    }
  }
}

sparseMat multMat(sparseMat m1, sparseMat m2)
{
  // remove every row of result, just in case anything there...
  // res.clear();
  sparseMat res;

  // initialise every row of result
  for (unsigned int c = 0; c < m1.size(); c++)
  {
    sparseRow row;
    res.push_back(row);	
  }

  sparseMat transp;
  transpMat(m2, transp);	// find transpose of second matrix, m2

  // now do the multiplications, based on dotproducts of rows
  //   of /both/ matrices, m1 and transp
  int rind1, rind2;
  sparseMat::const_iterator rit1; // we only want to /read/ list
  for (rit1 = m1.begin(), rind1 = 1; rit1 != m1.end(); rit1++, rind1++)
  {
    sparseMat::const_iterator rit2; // we only want to /read/ list
    for (rit2 = transp.begin(), rind2 = 1; rit2 != transp.end(); rit2++, rind2++)
    {
      //      cerr<< "["<< rind1<<", "<< rind2<< "]"<< endl;
      double val = dotProd(*rit1, *rit2); // the two rows

      if (epsilon < fabs(val))
	res[rind1-1].push_back(nz(rind2, val));
    }
  }
  return res;
}

double dotProd(const sparseRow r1, const sparseRow r2)
{
  sparseRow::const_iterator it1 = r1.begin(), e1 = r1.end();
  sparseRow::const_iterator it2 = r2.begin(), e2 = r2.end();

  double dp = 0;
  while (1)
  {
    int targetCol = MAX(it1->getInd(), it2->getInd());

    while (it1->getInd() < targetCol &&
	   it1 != e1)
      it1++;
    if (it1 == e1) break;

    while (it2->getInd() < targetCol &&
	   it2 != e2)
      it2++;
    if (it2 == e2) break;

    if (it1->getInd() == it2->getInd())
    {
      dp += it1->getVal() * it2->getVal(); // we finally found a macthing pair
      //      fprintf(stderr, "Updating dp with %.2f*%.2f (k=%d)\n", it1->getVal(), it2->getVal(),  it2->getInd());

      it1++;			// this is arbitrary
      if (it1 == e1) break;	// reached end of 
    }
  }
  return dp;
}

void outMat(const sparseMat mat)
{
  sparseMat::const_iterator rit; // we only want to /read/ list
  for (rit = mat.begin(); rit != mat.end(); rit++)
  {
    sparseRow row = *rit;
    // iterate over this row, only /read/
    sparseRow::const_iterator nzit;
    for (nzit = row.begin(); nzit != row.end(); nzit++)
    {
      cout<< *nzit;
    }

    cout<< endl;
  }
}

// http://www.codersource.net/c/c-miscellaneous/overloading-stream-operators.aspx
