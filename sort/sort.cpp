#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

struct Item						// Динамический список
{
	int item;					// Элемент
	Item* pr;					// Указатель на предыдущий
	Item* next;					// Указатель на следующий
};

class Stack
{
private:
	Item* last;					// Указатель на последний элемент
	Item* first;				// Указатель на первый элемент
	int size;					// Кол-во элементов
public:
	Stack();					// Конструктор
	~Stack();					// Деструктор

	void create();				// Создание списка
	void add(int a);			// Добавление элемента (a) в список
	int get(int x);				// Взять (x) элементов из списка и удалить их
	void print();				// Вывод элементов на экран
	void sort();				// Сортировка элементов
	void change(int n, int m);	// Заменить (m)ный элемент списка на значение n
};

Stack::Stack()
{
	size = 20;
	Item* last = NULL;
	Item* first = NULL;
}

Stack:: ~Stack()
{
	Item* k;
	for (int i = size - 1; i > 0; i--)
	{
		Item* k = first;
		first = first->next;
		delete(k);
		first->pr = NULL;
	}
	first = NULL;
	last = NULL;
	size = 0;
}

void Stack::create()
{
	vector<int> a;
	for (int i = 0; i < size; i++)
		a.push_back((int)rand() % 200 - 100);
	for (int i = size - 1; i >= 0; i--)
		add(a[i]);
}

void Stack::add(int a)
{
	Item* k;
	k = new Item;
	if (!last)
	{
		last = k;
		last->next = NULL;
	}
	else
		first->pr = k;
	k->item = a;
	k->next = first;
	first = k;
	first->pr = NULL;
}


int Stack::get(int x)
{
	vector<int>v;
	if (x != size - 1)
	{
		for (int i = x; i >= 0; i--)
		{
			Item* k = first;
			v.push_back(k->item);
			first = first->next;
			delete(k);
			first->pr = NULL;
		}
	}
	else
	{
		for (int i = x; i > 0; i--)
		{
			Item* k = first;
			v.push_back(k->item);
			first = first->next;
			delete(k);
			first->pr = NULL;
		}
		v.push_back(first->item);
		first = NULL;
		last = NULL;
	}
	for (int i = x; i >= 0; i--)
		add(v[i]);
	return v[x];
}

void Stack::print()
{
	Item* k = first;
	while (k)
	{
		cout << k->item << " ";
		k = k->next;
	}
	cout << endl;
}

void Stack::sort()
{
	int x, y;
	for (int j = 0; j < size; j++)
	{
		for (int i = size / 2 - 1 - j / 2; i > -1; i--)
		{
			if (2 * i + 2 <= size - 1 - j)
			{
				if (get(2 * i + 1) > get(2 * i + 2))
				{
					if (get(i) < get(2 * i + 1))
					{
						x = get(i);
						y = get(2 * i + 1);
						change(y, i);
						change(x, 2 * i + 1);
					}
				}
				else
					if (get(i) < get(2 * i + 2))
					{
						x = get(i);
						y = get(2 * i + 2);
						change(y, i);
						change(x, 2 * i + 2);
					}
			}
			else
				if (2 * i + 1 <= size - 1 - j)
					if (get(i) < get(2 * i + 1))
					{
						x = get(i);
						y = get(2 * i + 1);
						change(y, i);
						change(x, 2 * i + 1);
					}
		}
		x = get(0);
		y = get(size - 1 - j);
		change(y, 0);
		change(x, size - 1 - j);
	}
}

void Stack::change(int n, int m)
{
	vector<int>v;
	if (m != size - 1)
	{
		for (int i = m; i >= 0; i--)
		{
			Item* k = first;
			v.push_back(k->item);
			first = first->next;
			delete(k);
			first->pr = NULL;
		}
	}
	else
	{
		for (int i = m; i > 0; i--)
		{
			Item* k = first;
			v.push_back(k->item);
			first = first->next;
			delete(k);
			first->pr = NULL;
		}
		v.push_back(first->item);
		first = NULL;
		last = NULL;
	}
	v[m] = n;
	for (int i = m; i >= 0; i--)
		add(v[i]);
}

int main()
{
	setlocale(LC_ALL, "Rus");
	srand(time(0));

	Stack mystack;
	mystack.create();
	cout << "Первоначальный список:\n";
	mystack.print();
	mystack.sort();
	cout << "Отсортированный список:\n";
	mystack.print();
	return 0;
}