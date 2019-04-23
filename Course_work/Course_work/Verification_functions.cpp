﻿#include "pch.h"
#include "Verification_functions.h"

int Enter_choice(int diapason) //функция для проверки ввода "выбора" (передаем кол-во вариантов)
{
	string str;
	diapason += 48; // код значения символа верхней границы диапазона
again:              // метка на повторный ввод
	cin >> str;     // вводим строку
	if ((str[0] < '1' || str[0] > diapason) || str[1] != '\0') // если число не в нужном диапазоне
	{
		cout << "Ошибка ввода!\nВведите число заново: "; // выводим ошибку
		goto again; // метка к повторному вводу
	}
	return stoi(str); // конвертируем Int
}

int Enter_number(int diapason) // функция для проверки ввода номера числа (передаем кол-во товаров)
{
	string str;
	int number;
again:          // метка на повторный ввод
	cin >> str; // вводим строку
	for (int i = 0; i < str.length(); i++) // проходим по всей строке
	{
		if (str[i] < '0' || str[i] > '9') // если есть символы не цифр
		{
			cout << "Ошибка ввода!\nВведите число заново: "; // выводим ошибку
			goto again; // метка к повторному вводу
		}
	}
	number = stoi(str); // конвертируем и присваиваем номер в переменную
	if (number < 1 || number > diapason) // если номер не в диапазоне существующих товаров
	{
		cout << "Товара с таким номером нет на складе!\nВведите число заново: "; // выводим ошибку
		goto again; // метка к повторному вводу
	}
	return number;  // возвращаем номер товара
}

string Enter_string() // функция для проверки ввода названия и артикула товара
{
	string str;
again: // метка на повторный ввод
	getline(cin, str); // вводим строку
	if (str.length() > 100) // если длина строки больше 100
	{
		cout << "Длина превышает 100 символов, введите заново: "; // выводим ошибку
		goto again; // метка к повторному вводу
	}
	return str; // возвращаем строку
}

int Enter_int() // функция для проверки ввода кол-ва товаров на складе
{
	string str;
again: // метка на повторный ввод
	cin >> str; // вводим строку
	for (int i = 0; i < str.length(); i++) // проходим по всей строке
	{
		if (str[i] < '0' || str[i] > '9') // есть символы не цифр
		{
			cout << "Ошибка ввода!\nВведите число заново: "; // выводим ошибку
			goto again; // метка к повторному вводу
		}
	}
	return stoi(str); // конвертируем Int
}

float Enter_float() // функция для проверки ввода цены товара
{
	string str;

again:              // метка на повторный ввод
	int tochka = 0; // счетчик запятых
	cin >> str;     // вводим строку

	if (str[0] == ',') // проверка на 1 символ, если он ','
	{
		cout << "Ошибка ввода!\nВведите число заново: "; // то выводим ошибку
		goto again;    // метка к повторному вводу
	}

	for (int i = 0; i < str.length(); i++) // проходим по всей строке
	{
		if ((str[i] < '0' || str[i] > '9') && str[i] != ',') // если число не цифра и не запятая
		{
			cout << "Ошибка ввода!\nВведите число заново: "; // выводим ошибку
			goto again; // метка к повторному вводу
		}

		if (str[i] == ',') // счетчик ','(если встретилась ',')
			tochka++;      // увеличиваем счетчик

		if (tochka == 2)   // если кол-во запятых = 2
		{
			cout << "Ошибка ввода!\nВведите число заново: "; // выводим ошибку
			goto again;    // метка к повторному вводу
		}
	}
	return stof(str); // конвертируем в float  
}