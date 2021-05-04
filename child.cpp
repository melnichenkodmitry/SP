#include <iostream>
#include <string>
#include <unistd.h>
#include <fstream>
using namespace std;

int main(int argc, char *argv[])
{
	int j = 0, z = 0;
	string str = argv[1]; //переданное предложение
	string trigram = argv[2]; //переданная триграмма
	ofstream to_file;
	to_file.open("input.txt", ios::app);

	int i = str.find(trigram, 0);
	while (i != string::npos)
	{
		i = str.find(trigram, i + 1);
		j++;
	}
	to_file << j << endl;
	to_file.close();
	return 0;
}
