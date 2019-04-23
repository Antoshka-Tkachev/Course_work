#pragma once
#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Product
{
private:
	/*string name;    // название 
	string artikul; // артикул 
	float price;    // цена 
	int volume;     // кол-во в шт.*/
public:
	string name;    // название 
	string artikul; // артикул 
	float price;    // цена 
	int volume;     // кол-во в шт.
	Product();		// конструктор без параметров
	void set_info();
	void get_info();
	friend void output_spisok (vector <Product> &sklad, int SIZE);
	friend void change        (vector <Product> &sklad, int SIZE);
	friend void sort          (vector <Product> &sklad, int SIZE);
	friend void search        (vector <Product> &sklad, int SIZE);
	friend void save          (vector <Product> &sklad, int SIZE);
};

