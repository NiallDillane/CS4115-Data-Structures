#include <fstream>
#include <iostream>
#include <sstream>
#include <list>
#include <vector>
#include <algorithm>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::ofstream;
using std::list;
using std::vector;
using std::sort;

#include <math.h>
#include <stdlib.h>

class Nz{
	public:
	int rowNo, colNo; double val;

	public :
	Nz(){}
	Nz(int colNo, double val){
		this->colNo=colNo;
		this->val=val;
	}

	void transpose(){
		int temp=0;
		temp=this->colNo;
		this->colNo=this->rowNo;
		this->rowNo=temp;
	}

	friend std::istringstream& operator>>(std::istringstream&, Nz&);
	friend std::ostream& operator<<(std::ostream&, const Nz&);
};

bool compare_entry( const Nz & e1, const Nz & e2) {
  if( e1.rowNo != e2.rowNo)
	 return (e1.rowNo < e2.rowNo);
  return (e1.colNo < e2.colNo);
}

std::istringstream& operator >>(std::istringstream& is, Nz& next){
	is >> next.colNo >> next.val;
	return is;
}

std::ostream& operator <<(std::ostream& os, const Nz& next){
	os << next.colNo << " " << next.val << " ";
	return os;
}


int main(int argc, char *argv[]){
        int r=0;
	vector<Nz> valsTran;

	std::string line;
	while (getline(cin, line)){
		r++;
		std::istringstream lstream(line);
		Nz next;
		while (lstream>> next){
			next.rowNo=r;
			next.transpose();
			valsTran.push_back(next);
		}
	}
	
	std::stable_sort(valsTran.begin(), valsTran.end(), compare_entry);

	
	int c=0, prev=1;
	for(vector<Nz>::iterator it = valsTran.begin(); it != valsTran.end(); ++it){
		while(prev < (*it).rowNo){
			cout << endl;
			prev++;
			c++;
		}
		cout << *it;
	}
	while(c < r){
	  cout << endl;
	  c++;
	}
}
