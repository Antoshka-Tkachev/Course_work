#include "pch.h"
#include "Product.h"
#include "Verification_functions.h"
#include "SkladOptions.h"
#include <fstream>   // библиотека для использования файловых потоков

void output_spisok(vector <Product> &sklad, int SIZE)
{
	cout << "\nСписок товаров:" << endl;
	for (int i = 0; i < SIZE; i++)
	{
		cout << i + 1 << " товар: " << endl;
		sklad[i].get_info();
	}
}

void change(vector <Product> &sklad, int SIZE)
{
	int number; // номер товара
	int choice;
	cout << "\nВведите номер товара, в котором хотите произвести изменение: "; // номер товара
	number = Enter_number(SIZE); // вводим номер через функцию с проверкой

	cout << "\nВ какой графе хотите сделать изменение?\n" // где делать изменение?
		<< "1. Название товара\n"
		<< "2. Артикул товара\n"
		<< "3. Цена товара\n"
		<< "4. Количество товара на складе (в шт.)\n"
		<< "Введите номер выбранного варианта: ";
	choice = Enter_choice(4); //// вводим вариант через функцию с проверкой
	//РЕАЛИЗАЦИЯ ИЗМЕНЕНИЯ
	switch (choice) // выбор изменения в зависимости от выбранного
	{
	case 1:
	{
		cout << "\nВведите новое название товара: ";
		cin.ignore(32767, '\n');    // игнорим "Enter" для getline
		sklad[number - 1].name = Enter_string(); // вводим новое название с помощью функции с проверкой
	}
	break;

	case 2:
	{
		cout << "\nВведите новое значение артикула товара: ";
		cin.ignore(32767, '\n');  // игнорим "Enter" для getline
		sklad[number - 1].artikul = Enter_string(); // вводим новый артикул с помощью функции с проверкой
	}
	break;

	case 3:
	{
		cout << "\nВведите новую цену товара: ";
		sklad[number - 1].price = Enter_float(); // вводим новую цену с помощью функции с проверкой
	}
	break;

	case 4:
	{
		cout << "\nВведите новое значения кол-ва товара на складе (в шт.): ";
		sklad[number - 1].volume = Enter_int(); // вводим новое кол-во товара с помощью функции с проверкой
	}
	break;

	default:
		break;
	}
}


void sort(vector <Product> &sklad, int SIZE)
{
	int choice;
	cout << "\nХотите сортировать товар по:\n" // выбор метода сортировки
		<< "1. Названию\n"
		<< "2. Артикулу\n"
		<< "3. Цене\n"
		<< "4. Количеству\n"
		<< "Выберете желаемый вариант: ";
	choice = Enter_choice(4); // вводим вариант через функцию с проверкой

	/*РЕАЛИЗАЦИЯ СОРТИРОВКИ (в зависимости от метода)*/
	switch (choice)
	{
	case 1: //сортировка по алфавиту
	{
		for (int i = 0; i < sklad.size(); i++) {
			for (int j = 0; j < sklad.size() - i - 1; j++) {
				if (sklad[j].name.compare(sklad[j + 1].name) > 0) {
					swap(sklad[j], sklad[j + 1]);
				}
			}
		}
	}
	break;

	case 2: //сортировка по артикулу (возрастание)
	{
		for (int i = 0; i < sklad.size(); i++) {
			for (int j = 0; j < sklad.size() - i - 1; j++) {
				if (sklad[j].artikul.compare(sklad[j + 1].artikul) > 0) {
					swap(sklad[j], sklad[j + 1]);
				}
			}
		}
	}
	break;

	case 3: //сортировка по цене (возрастание)
	{
		for (int i = 0; i < sklad.size(); i++) {
			for (int j = 0; j < sklad.size() - i - 1; j++) {
				if (sklad[j].price > sklad[j + 1].price) {
					swap(sklad[j], sklad[j + 1]);
				}
			}
		}
	}
	break;

	case 4: //сортировка по количеству (возрастание)
	{
		for (int i = 0; i < sklad.size(); i++) {
			for (int j = 0; j < sklad.size() - i - 1; j++) {
				if (sklad[j].volume > sklad[j + 1].volume) {
					swap(sklad[j], sklad[j + 1]);
				}
			}
		}
	}

	default:
		break;
	}
}

void delete_sklad_i(vector <Product> &sklad, int SIZE)
{
	int number; // номер товара
	cout << "\nВведите номер товара, который хотите удалить: ";
	number = Enter_number(sklad.size());     // ввод номера товара через функцию с проверкой
	sklad.erase(sklad.begin() + number - 1); // удаляем элемент массива с данным номером(номер - 1)
}

void search(vector <Product> &sklad, int SIZE)
{
	string bufer; // будет хранить название искомого товара
	int k = 0;     //счетчик
	cout << "\nВведите название товара: ";
	cin.ignore(32767, '\n');    // игнорим "Enter" для getline
	getline(cin, bufer);        // вводим название искомого товара
	cout << endl;
	for (int i = 0; i < sklad.size(); i++) // в цикле сравниваем введенное название с названиями товаров
	{
		if (bufer == sklad[i].name) // если введенное название = названию товара, то выводим его
		{
			cout << i + 1 << " товар: " << endl;
			sklad[i].get_info(); // вывод информации о товаре
			k++;                 // увеличиваем счетчик
		}
	}

	if (k == 0) // если счетчик остался 0, то выводим предупреждение
		cout << "Товар с данным названием не найден!" << endl;
}

void save(vector <Product> &sklad, int SIZE)
{

	string fileName;		// переменная будет хранить названия файлов
	bool flag = false;		// индикатор ошибки открытия/записи/чтения файла

	ofstream fout;			// открываем поток записи в файл

	fout.open("Names.txt"); // открываем файл с названиями товаров "Names.txt"
	if (!fout.is_open())    // если файл не открылся
	{
		flag = true;        // делаем флаг "true"
	}
	else                    // если файл открылся
	{
		for (int i = 0; i < sklad.size(); i++) // записываем все названия товаров в него
		{
			if (i != sklad.size() - 1)         // последний товар записываем без перехода на новую строку
				fout << sklad[i].name << "\n";
			else
				fout << sklad[i].name;
		}
	}
	fout.close(); // закрываем файл с названиями товаров "Names.txt"

	for (int i = 0; i < sklad.size(); i++) // для всех товаров
	{
		fileName = sklad[i].name + ".txt"; // устанавливаем название файла относительно названию товаров
		fout.open(fileName);               // открываем файл товара
		if (!fout.is_open())               // если не открылся
		{
			flag = true;                   // делаем флаг "true"
		}
		else // если файл открылся записываем в него
		{
			fout << sklad[i].artikul << "\n"; // артикул товара
			fout << sklad[i].price << "\n";   // цену товара
			fout << sklad[i].volume << "\n";  // кол-во товара на складе
		}
		fout.close(); // закрываем файл товара
	}

	if (flag) // если флаг "true" выводим ошибку
	{
		cout << "\nОшибка сохранения данных!\n";
	}
	else     // если флаг "false" выводим успех
	{
		cout << "\nДанные успешно сохранились!\n";
	}
}