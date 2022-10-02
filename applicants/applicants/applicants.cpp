// 14.6. Абитуриенты (8)
// В институт поступают M абитуриентов на N специальностей. По каждой специальности известно число вакантных мест для зачисления абитуриентов.
// Каждый абитуриент имеет право участвовать в конкурсе как по одной, так и по нескольким специальностям до всех N включительно.Для участия в конкурсе по специальности 
// абитуриент должен иметь конкурсный балл.Баллы на разные специальности могут быть различны.Помимо этого, абитуриент для каждой выбранной специальности указывает приоритет, 
// задаваемый целым числом, начиная с 1 (высший приоритет).
// Задача приемной комиссии зачислить абитуриента на специальность с максимально высоким для него приоритетом.Известно, что на каждой специальности баллы поступающих на нее абитуриентов оказались различными.
// Написать программу для зачисления абитуриентов.
// Леухин Максим ПС-23
// Visual Studio 2022 C++17

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <set>

using namespace std;

struct Person
{
	int bal;
	int num;
	int preor;
};

void deleteListEl(vector <vector<Person>>& list, set<int>& res)
{
	for (int i = 0; i < list.size(); i++)
	{
		for (int pers = 0; pers < list[i].size(); pers++)
		{
			if (list[i][pers].num != 0)
			{
				if (res.find(list[i][pers].num) != res.end())
				{
					list[i][pers].num = 0;
					list[i][pers].bal = 0;
					list[i][pers].preor = 0;
					//cout << " personNum:" << el.num << " Bal:" << el.bal << " preor: " << el.preor << endl;

				}
			}
		}
	}
}
void CorMaxAbitur(vector <int>& MaxAbitur, vector <int> resVec)
{
	for (int i = 0; i < resVec.size(); i++)
	{
		MaxAbitur[i] -= resVec[i];
	}
}
set<int> PreorSet(vector <vector<Person>>& list, vector <int>& vec)
{
	set <int> res;

	for (int i = 0; i < list.size(); i++)
	{
		for (auto el : list[i])
		{
			if (el.num != 0)
			{
				if (vec[i] == 0)
				{
					res.insert(el.num);
				}
			}
		}
	}
	return res;
}
void PreorFix(vector <vector<Person>>& list, set <int>& Abitr)
{
	for (int i = 0; i < list.size(); i++)
	{
		for (int pers = 0; pers < list[i].size(); pers++)
		{
			if (list[i][pers].num != 0)
			{
				if (Abitr.find(list[i][pers].num) != Abitr.end())
				{
					list[i][pers].preor--;
				}
			}
		}
	}
}
void CorList(vector <vector<Person>>& list, vector <int>& MaxAbitur, set<int>& res, vector <int>& pos, vector <vector<Person>>& resVec)
{
	deleteListEl(list, res);
	CorMaxAbitur(MaxAbitur, pos);
	set <int> subSet = PreorSet(list, MaxAbitur);
	PreorFix(list, subSet);
}

void Priem(vector <vector<Person>>& list, vector <int>& MaxAbitur, set<int>& enrolled, vector <int>& pos, vector <vector<Person>>& resVec)
{
	for (int i = 0; i < list.size(); i++)
	{
		int count = 0;
		for (auto el : list[i])
		{
			if (el.num != 0)
			{
				if (el.preor == 1 && count < MaxAbitur[i])
				{
					resVec[i].push_back(el);
					enrolled.insert(el.num);
					pos[i] += 1;
				}
				count++;
			}
		}
	}
}
bool FreeSpace(vector <int>& AbitList)
{
	int count = 0;

	for (int i = 0; i < AbitList.size(); i++)
	{
		if (AbitList[i] != 0)
			count += AbitList[i];
	}
	if (count > 0)
	{
		return true;
	}
	return false;
}

void ShowList(vector <vector<Person>>& res)
{
	int k = 0;
	for (auto i : res)
	{
		sort(i.begin(), i.end(), [](Person p1, Person p2) {return p1.bal > p2.bal; });
		for (auto el : i)
			if (el.num != 0)
				cout << k << " personNum:" << el.num << " Bal:" << el.bal << " preor: " << el.preor << endl;
		k++;
		cout << endl;
	}
}

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");
	if (argc != 3)
	{
		cout << "Неверное количество аргуметнов \n"
			<< "Чтобы использовать: applicants.exe <Input file> <Output file>" << endl;
		return 1;
	}
	fstream input;
	input.open(argv[1], ios_base::in);
	if (!input.is_open())
	{
		cout << "Failed to open input file" << endl;
		return 1;
	}

	int special, abitur;
	input >> abitur >> special;
	vector <int> MaxAbitur;
	MaxAbitur.push_back(0);
	for (int i = 1; i <= special; i++)
	{
		int t;
		input >> t;
		MaxAbitur.push_back(t);
	}

	Person temp;
	vector <Person> tt;
	vector <vector<Person>> list;
	for (int i = 0; i < MaxAbitur.size(); i++)
	{
		tt.resize(0);
		list.push_back(tt);
	}

	for (int i = 1; i <= abitur; i++)
	{
		int t;
		input >> t;
		for (int j = 1; j <= t; j++)
		{
			int spec{}, bal{};
			input >> spec >> bal;
			temp.bal = bal;
			temp.num = i;
			temp.preor = j;
			list[spec].push_back(temp);
		}
	}

	vector <vector<Person>> res;
	for (int i = 0; i < MaxAbitur.size(); i++)
	{
		tt.resize(0);
		res.push_back(tt);
	}
	set <int> enrolled;
	vector <int> pos;
	pos.resize(MaxAbitur.size());
	int k = 0;
	while (FreeSpace(MaxAbitur) && k < 1000000)
	{

		for (int i = 0; i < list.size(); i++)
		{
			sort(list[i].begin(), list[i].end(), [](Person p1, Person p2) {return p1.bal > p2.bal; });
			pos[i] = 0;
		}
		ShowList(list);
		Priem(list, MaxAbitur, enrolled, pos, res);
		CorList(list, MaxAbitur, enrolled, pos, res);
		enrolled.clear();
		k++;
		cout << "---------------" << endl;
	}

	for (int i = 0; i < res.size(); i++)
	{
		sort(res[i].begin(), res[i].end(), [](Person p1, Person p2) {return p1.bal > p2.bal; });
	}

	fstream output;
	output.open(argv[2], ios_base::out);
	for (int i = 1; i < res.size(); i++)
	{
		if (res[i].size() == 0 && i != 0)
		{
			output << "No";
		}
		else
		{
			for (int pers = 0; pers < res[i].size(); pers++)
			{
				if (res[i][pers].num != 0)
				{
					output << res[i][pers].num << " ";
				}
			}
		}
		output << endl;
	}

	return 0;
}
