/*
12.6. Жизнь на Марсе (7)
При высадке на Марс было основано N поселений. Каждое из них равномерно расширялось во все стороны на L марсианских миль в месяц. Постепенно поселения начали сливаться друг с другом, получая общее название. Какое минимальное время с момента высадки потребуется для того, чтобы на Марсе осталось не более K поселений?
Ввод из файла INPUT.TXT. В первой строке задаются через пробел  три целых положительных значения: начальное количество поселений N (1 ≤ N ≤ 1000), число K (1 ≤ K ≤ 10, K< N) и скорость роста поселений L (1 ≤ L ≤ 100). Далее в следующих N строках содержатся через пробел целые координаты поселений Xi , Yi (-1000 ≤ Xi , Yi ≤ 1000) в марсианских милях.
Вывод в файл OUTPUT.TXT.В единственной строке вывести с точностью до 2 знаков минимальное время в месяцах с момента высадки, необходимое для того, чтобы в результате слияния осталось не более K поселений.
Пример
Ввод
3 2 1
-1 1
2 1
2 5
Вывод
1.50

Татьянина Мария ПС - 23
Visual Stydio 2022
*/
//http://cendomzn.ucoz.ru/index/0-7640 идея
//https://www.youtube.com/watch?v=T7HUnh_CBd4 намек на реализацию
//http://mindhalls.ru/graphs-dfs-tasks/ возможная идея реализации
#include <iostream>
#include <vector>
#include <fstream>
#include <set>
#include <algorithm>
#include <iomanip>
#include <stack>

using namespace std;
const double EPS = 0.00001;
struct Point
{
	int num;
	int x;
	int y;
};

struct arc
{
	int from;
	int were;
	double time;
};

double distance(Point a, Point b)
{
	return sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
}
vector <int> order;
vector <bool> used;
vector <int> comp;

void dfs1(int v, vector <vector<int>>& g) 
{
	used[v] = true;
	for (size_t i = 0; i < g[v].size(); ++i)
		if (!used[g[v][i]])
			dfs1(g[v][i], g);
	order.push_back(v);
}

bool check(vector <vector<int>>& m, int k, int max)
{
	int t{};
	for (int i = 0; i < k; ++i)
		if (!used[i])
		{
			dfs1(i, m);
			t = 1;
			cout << order.size() << endl;
			for (int i = 0; i < order.size(); i++)
			{
				if (comp[order[i]] != --t)
					comp[order[i]] = t;
			}
			t++;
		}
	if (t == max)
		return false;
	return true;
}
int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");
	//if (argc != 3)
	//{
	//	cout << "Usage: mars.exe <Input file> <Output file>" << endl;
	//	return 1;
	//}

	ifstream inputFile;	//argv[1]

	inputFile.open("inp.txt");
	double N{}, k{}, l{};
	inputFile >> N >> k >> l;

	vector <Point> pointList;
	Point p{};

	for (int i = 0; i <= N; i++)
	{
		inputFile >> p.x >> p.y;
		p.num = i;
		pointList.push_back(p);
	}
	sort(pointList.begin(), pointList.end(), [](Point a, Point b) {return a.num < b.num; });
	
	vector <vector <int>> matr;
	vector <arc> listArc;
	arc Arc{};

	for (int i = 0; i < N; i++)
	{
		vector <int> t;
		t.resize(pointList.size());
		matr.push_back(t);
		for (int j = i + 1; j < N; j++)
		{
			Arc.from = i;
			Arc.were = j;
			Arc.time = distance(pointList[i], pointList[j]) / (2.0 * l);
			listArc.push_back(Arc);	
		}
	}
	sort(listArc.begin(), listArc.end(), [](arc a, arc b) {return a.time < b.time; });
	
	int temp = 0;
	bool needEnd = false;

	used.resize(N);
	comp.resize(N);
	//ofstream outputFile(argv[2]);
	//outputFile << fixed << setprecision(2);
	while (!needEnd)
	{
		int i{}, c{};
		for (int m = 0; m < N; m++)
			for (int n = 0; n < N; n++)
				matr[m][n] = 0;
		used.assign(N, false);
		comp.assign(N, 0);
		for (i = 0; listArc[i].time < listArc[temp].time; i++)
		{
			matr[listArc[i].from][listArc[i].were] = 1;
			matr[listArc[i].were][listArc[i].from] = 1;
			c++;
		}

		needEnd = check(matr, c, k);


		temp++;
		if (temp == listArc.size())
			break;
	}

	return 0;
}