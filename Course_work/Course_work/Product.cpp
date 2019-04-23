#include "pch.h"
#include "Product.h"
#include "Verification_functions.h"

Product::Product() // коструктор по умолчанию
{
	name = "NoName";
	artikul = "NoArtikul";
	price = 0;
	volume = 0;
}

void Product::set_info()
{
	cout << "\nВведите название товара: ";
	cin.ignore(32767, '\n');    // игнорим "Enter" для getline
	name = Enter_string();
	cout << "Введите артикул товара: ";
	artikul = Enter_string();
	cout << "Введите цену товара: ";
	price = Enter_float();
	cout << "Введите количество товара на складе (в шт.): ";
	volume = Enter_int();
}

void Product::get_info()
{
	cout << "Название товара: " << name << endl;
	cout << "Артикул товара: " << artikul << endl;
	cout << "Цена товара: " << price << endl;
	cout << "Количество товара на складе (в шт.): " << volume << endl;
	cout << endl;
}