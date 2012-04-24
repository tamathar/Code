#include <iostream>
#include <sstream>
using namespace std;

int main()
{
	stringstream ss;
	ss << "hello";
	ss << "yo";
	string output;
	
	ss >> output;
	cout << output << endl;
}