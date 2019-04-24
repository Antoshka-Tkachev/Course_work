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
	choice = Enter_choice(4); // вводим вариант через функцию с проверкой
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
	string bufer;  // будет хранить название искомого товара
	int k = 0;     //счетчик
	cout << "\nВведите название товара: ";
	cin.ignore(32767, '\n');    // игнорим "Enter" для getline
	getline(cin, bufer);        // вводим название искомого товара
	cout << endl;
	for (int i = 0; i < sklad.size(); i++) // в цикле сравниваем введенное название с названиями товаров
	{
		if (bufer == sklad[i].name)        // если введенное название = названию товара, то выводим его
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

void delete_base()
{
	ifstream fin;    // открываем поток считывания
	Product buffer;  // временное хранилище данных обьекта класса
	string fileName; // имя файла
	vector <string> files; //хранит названия удаляемых файлов
	fin.open("Names.txt"); // открываем файл имен
	if (fin.is_open())     //если файл отклыт, то удаляем базу, если файл не открыт, значит его нет
	{
		while (!fin.eof()) // пока файл названий "Names.txt" не закончился
		{
			getline(fin, fileName);    // считываем названия в буфер
			files.push_back(fileName); // добавляем буфер в элемент массива
		}

		for (int i = 0; i < files.size(); i++) // в цикле по всем товарам удаляем их
		{
			fileName = files[i] + ".txt";              // записываем название файла исходя из названия товара
			char fileName_char[101];                   //преобразование из string в char
			strcpy_s(fileName_char, fileName.c_str()); // тк remove не работает со string
			remove(fileName_char);                     // удаляем файл
		}

		fin.close(); // закрываем файл имен "Names.txt"

		remove("Names.txt");                        // удаляем файл имен "Names.txt"
		for (int i = files.size() - 1; i >= 0; i--) // в цикле от последнего до первого товара в массиве
			files.erase(files.begin() + i);         // удаляем элементы из массива(товары)
	}
}

int add_base(vector <Product> &sklad)
{
	ifstream fin; // открываем поток считывания с файла
	string fileName;
	int choice;
	Product buffer;
	bool flag = false;

	fin.open("Names.txt"); // открываем файл в котором хранятся названия товаров
	if (!fin.is_open())    // если файл не открыт, то его не существует
	{
	emptyFile: // метка от перехода, если файл "Names.txt" пуст
		cout << "\nСуществующей базы данных не найдено!\n" // выводим предупреждение
			<< "1. Добавить товары заново\n"
			<< "2. Закрыть программу\n"
			<< "Выберете желаемый вариант: "; // делаем выбор
		choice = Enter_choice(2); // ввод варианта через функцию с проверкой

		if (choice == 1) // если хотим добавить товары заново
			return 2;    // то переходим по метке к "добавлению"
		else             // если хотим закрыть программу
			return 1;    // то завершаем
	}
	else   // если файл "Names.txt" с названиями товаров открылся
	{
		while (!fin.eof()) // пока файл имен не закончится
		{
			getline(fin, buffer.name); // считываем названия товаров/файлов
			sklad.push_back(buffer);   // добавляем считанное название в новый элемент массива
		}
		fin.close(); // закрываем файл в котором хранятся названия товаров


		// проверка на пустоту файла названий "Names.txt", если файл пуст, то нет базы данных
		if (sklad[0].name == "") // если первое название "пустое", то и файл пуст
		{
			remove("Names.txt");        // удаляем файл названий "Names.txt"
			sklad.erase(sklad.begin()); //удаляем элемент массива который заполнен пустым названием
			goto emptyFile;             // переход к части кода "Базы данных не существует"
		}
	}

	for (int i = 0; i < sklad.size(); i++) // цикл от первого до последнего товара в массиве товаров
	{
		fin.open(sklad[i].name + ".txt"); // открываем файл с названием считанным из файла
		if (!fin.is_open()) // если файл не открылся
		{
			flag = true;    // установить индикатор "true"
		}
		else // если файл открылся
		{
			fin >> sklad[i].artikul; // считываем артикул товара
			fin >> sklad[i].price;   // считываем цену товара
			fin >> sklad[i].volume;  // считываем кол-во товара
		}
		fin.close(); // закрываем файл с названием считанным из файла
	}

	if (flag) // если флаг "true", значит  ошибка
	{
		cout << "\nОшибка считывания данных!\n"; // выводим предупреждение об ошибке
		return 1; // завершить программу
	}
	else     // если флаг "false", значит успех
	{
		cout << "\nДанные успешно считались!\n"; // выводим информацию об успехе

		/*УДАЛЯЕМ ВСЕ ФАЙЛЫ*/
		if (remove("Names.txt") != 0) // удаляем файл названий "Names.txt"
			flag = true;              // если файл не удален делаем флаг "true"

		for (int i = 0; i < sklad.size(); i++) // цикл по всему массиву товаров
		{
			fileName = sklad[i].name + ".txt"; // записываем название файла исходя из названия товара
			char fileName_char[101];                       // преобразование из string в char
			strcpy_s(fileName_char, fileName.c_str());     // тк remove не работает со string
			if (remove(fileName_char) != 0)                // удаляем файлы товаров
				flag = true; // если файл не удален делаем флаг "true"
		}

		if (flag) // если флаг "true"
		{
			cout << "Ошибка!"; // выводим ошибку
			return 1;          // завершаем программу
		}

		return 0; //нормально отработало
	}
}