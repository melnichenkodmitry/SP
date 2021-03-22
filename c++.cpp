#include <iostream>
#include <cstdlib> 
#include <string>
using std::cout;
using std::endl;
using std::cin;
int main()
{
	setlocale(LC_ALL, "Russian");
	unsigned int elements[10];
	for (int i = 0; i < 10; i++)
	{
		cout << "[" << i + 1 << "]" << ": ";
		cin >> elements[i];

	}
	cout << "\nПолученный массив: ";
	for (int i = 0; i < 10; i++)
	{
		cout << elements[i] << " ";
	}
	cout << endl;
	unsigned int bitMask = 128;
	int sum = 0;
	for (int i = 0; i < 10; i++)
	{
		int result = bitMask & elements[i];
		if (result == bitMask)
		{
			elements[i] = (~elements[i] + 1); // инвертируем элемент массива
		}
		sum += elements[i];
	}
	cout << "Сумма элементов массива: " << sum;
	cout << endl;
	return 0;
}
