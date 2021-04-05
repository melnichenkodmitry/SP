#include <iostream>

using namespace std;



int main()
{
	setlocale(LC_ALL, "Russian");
	char elements[10] = { '1', 'D', '3', '4', 'B', '6', 'T', '8', '9', 'Z' };
	char reversed[10];
	for (int i = 0; i < 10; i++)
	{
		cout << elements[i] << " ";
	}
	cout << endl;
	_asm
	{
	main:
			mov al, 0
			mov esi, 0 //объявление первого элемента
			mov edi, 9 //объявление последнего элемента
	cycle :
			mov al, [elements + edi] //помещает в регистр al последний байт (элемент) массива elements
			mov [reversed + esi], al //помещает в первый байт массива reversed значение из регистра al
			inc esi //увеличение значения на 1
			dec edi //уменьшение значения на 1
			cmp esi, 10 //выходит из цикла когда пройдет 10 элемент массива
			jne cycle
	}

	for (int i = 0; i < 10; i++)
	{
		cout << reversed[i] << " ";
	}
	cout << endl;
}
