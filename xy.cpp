#include <iostream>
#include <fstream>
#include "vector.cpp"
#include "sfml.cpp"

using std::cout;
using std::endl;
int main()
{
	std::ifstream fin("points.txt");
	
	vector <double> a;
	
	while (!fin.eof())
	{
		double tmp;
		fin >> tmp;
		a.append(tmp);
	}
	
	//~ sfRunWindow(640, 480, "TEST");
	
	a.dump("a", "stdout");
	//~ cout << a[0] << endl;
	return 0;
}
