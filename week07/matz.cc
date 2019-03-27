#include <fstream>
#include <iostream>
#include <sstream>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::ofstream;

#include <math.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
   int c; 
   bool first;
   double epsilon=0;
   if (argc > 1 && std::string(argv[1]) == "-e")
      epsilon = fabs(strtod(argv[2], 0));

   std::string line;
   while (getline(cin, line))
   {
      first=true;
      c=0;
      std::istringstream lstream(line) ;
      double val;
      // peel off values in this line, one at a time
      while (lstream>> val)
      {
         c++;
         if(!first && val!=0 && abs(val)>epsilon)
            cout << " ";
         if(val!=0 && abs(val)>epsilon){
            cout << c << " " << val;
            first=false;
         }
      }
      cout << endl;
   }
}
