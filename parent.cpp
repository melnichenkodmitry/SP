#include <iostream>
#include <string.h>
#include <fstream>
#include <sys/wait.h>
#include <unistd.h>

using namespace std;

int main()
{
	setlocale (LC_ALL, "Russian");
	int pos = 0, i = 0, freq = 0;
	string text, temp, trigram;

	cout << "Введите текст" << endl;
	getline(cin, text);

	cout << "Введите триграмму:" << endl;
	getline(cin, trigram);
	
	for (i = text.find(".", i++); i != string::npos; i = text.find(".", i + 1)) //разделение по предложениям
	{
		temp = text.substr (pos, i - pos); //какое предложение вошло (номер предложения)
		pos = i;

		char *arr_temp = new char[temp.length()]; //перевод переменной temp из string в char
		char *arr_trigram = new char[trigram.length()];
		stpcpy(arr_temp, temp.c_str()); //копирование данных из переменной в массив
		stpcpy(arr_trigram, trigram.c_str());

		pid_t pr;
		pr = fork();
		int status;

		if (pr == 0)
		{
			execl("child", "child", arr_temp, arr_trigram, NULL);
		}
		else if (pr > 0)
		{
			wait(&status);
		}
		delete[] arr_temp;
		delete[] arr_trigram;
	}

	fstream from_file;
	from_file.open("input.txt", ios::in);

	if (from_file)
	{
		string buf;
		while (getline(from_file, buf))
		{
			freq = freq + stoi(buf);
		}
	}
	from_file.close();
	remove("input.txt");
	cout << "\nЧастота '" << trigram << "'триграммы: " << freq << endl;

	return 0;
}
