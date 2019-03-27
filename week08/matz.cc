#include <fstream>
#include <iostream>
#include <sstream>
#include <list>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::ofstream;
using std::list;

#include <math.h>
#include <stdlib.h>

class Nz{
  public:
  int col; double val;
  
  public :
  Nz(int col, double val){
    this->col=col;
    this->val=val;
  }
};

int main(int argc, char *argv[])
{
   int c; 
   bool first;
   double epsilon=0;
   list<Nz> row;
   list< list<Nz> > rows;

   if (argc > 1 && std::string(argv[1]) == "-e")
      epsilon = fabs(strtod(argv[2], 0));

   std::string line;
   while (getline(cin, line))
   {
      c=0;
      std::istringstream lstream(line) ;
      double val;
      // peel off values in this line, one at a time
      while (lstream>> val)
      {
         c++;
         // row = new list<Nz>;
         if(val!=0 && abs(val)>epsilon){
            Nz nz(c, val);
            row.push_back(nz);
         }
      }
      rows.push_back(row);
      row.clear();
   }

   list<Nz>::iterator itRow;
   list< list<Nz> >::iterator itRows;

   for(itRows = rows.begin(); itRows != rows.end(); itRows++){
      for(itRow = itRows->begin(); itRow != itRows->end(); itRow++){
         cout << itRow->col << " " << itRow->val << " ";
      }
   cout << endl;
   }
}