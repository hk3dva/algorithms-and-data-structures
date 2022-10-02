
#include <iostream>
#include <vector>
#include <list>
#include <fstream>

using namespace std;

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");
	if (argc != 3)
	{
		cout << "Usage: olympiad.exe <Input file> <Output file>" << endl;
		return 1;
	}

	ifstream inputFile(argv[1]);
}
