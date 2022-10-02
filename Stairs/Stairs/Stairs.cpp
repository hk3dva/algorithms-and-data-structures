/******************************************************************************
19.19. Лестница (3)
По широкой лестнице с разной скоростью спускаются N человек. В начальный момент они находятся на разных ступенях. Обгоны запрещены, но если человек A догнал человека B, который идет с более низкой скоростью, то до конца лестницы человек A идет вместе с человеком B. При этом на одной ступени лестницы может помещаться сколько угодно человек. Требуется рассчитать время, за которое каждый человек спустится по лестнице.
Ввод из файла INPUT.TXT. В первой строке записано число N (1 ≤ N ≤1000). В следующих N строках заданы пары целых чисел ti, wi (1 ≤ ti, wi ≤ 1000) – время прохода одной ступени в секундах и количество ступеней до конца лестницы. Изначально всем людям остается идти различное число ступеней.
Вывод в файл OUTPUT.TXT - N строк. В i-ой строке выводится время в секундах, через которое i-ый человек сойдет с лестницы.
Примеры
Ввод 1       Ввод 2
3            3
2 10         2 11
3 11         3 12
1 12         5 4
Вывод 1      Вывод 2
20           22
33           36
33           20


----  ----  ПС - 23
Visual Studio 2022
*******************************************************************************/
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;
struct Person
{
	int time;
	int stair;
	int num;
	int timeDown;
};
int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");
	if (argc != 3)
	{
		cout << "Usage: Stairs.exe <Input file> <Output file>" << endl;
		return 1;
	}

	ifstream inputFile(argv[1]);

	int N{};
	inputFile >> N;
	int time{}, stair{};
	vector <Person> mans;
	Person temp;
	for (int i = 1; i <= N; i++)
	{
		inputFile >> temp.time >> temp.stair;
		temp.num = i;
		temp.timeDown = 0;
		mans.push_back(temp);
	}

	sort(mans.begin(), mans.end(), [](Person a, Person b) { return a.stair < b.stair; });

	int step = 1;
	while (mans[mans.size() - 1].stair != 0)
	{
		for (int i = 0; i < mans.size(); i++)
		{
			if (mans[i].stair != 0 && step % mans[i].time == 0)
			{
				mans[i].stair--;
				mans[i].timeDown += mans[i].time;
			}
		}
		for (int i = 1; i <= mans.size(); i++)
		{
			if (mans[i].stair < mans[i - 1].stair)
			{
				mans[i].stair = mans[i - 1].stair;
			}
		}
		step++;
	}
	sort(mans.begin(), mans.end(), [](Person a, Person b) { return a.num < b.num; });

	ofstream outputFile(argv[2]);
	for (auto i : mans)
	{
		outputFile << i.timeDown << endl;
	}

	return 0;
}
