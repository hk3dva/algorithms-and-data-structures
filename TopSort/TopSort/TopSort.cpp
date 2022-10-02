/* 12.8. Учебный план (5)
Учебный план включает перечень дисциплин. Задан список пар дисциплин. Отдельная пара показывает, что вторая дисциплина должна изучаться после  первой. Составить список дисциплин учебного плана в порядке их изучения. В том случае, когда задание некорректно, т.е. в списке пар имеются циклы, выдать хотя бы один из них.
Ввод из файла INPUT.TXT. В первой строке задается число пар дисциплин N (1 ≤ N ≤ 300). В каждой из следующих N строк указываются через пробел  два  натуральных  числа  Xi , Yi (Xi , Yi ≤ 1000), определяющих номера дисциплин.  Первая дисциплина должна изучаться раньше второй.
Вывод в файл OUTPUT.TXT. В первой строке вывести Yes  либо No – возможность расположения в списке дисциплин в порядке их изучения. При наличии такой возможности во второй строке выводится через пробел искомый список. Если задание некорректно, т.е. имеется цикл, то во второй строке выдается список номеров, образующих цикл. Первый и последний номера в этом списке должны совпадать.
Примеры
Ввод 1           Ввод 2
7                8
1 2              1 2
1 3              1 3
2 5              2 5
3 4              3 4
4 2              4 2
3 2              3 2
6 4              6 4
                 5 3
Вывод 1          Вывод 2
Yes              No
1 6 3 4 2 5      2 5 3 4 2

Шабалин Кирилл ПС-23

Visual Studio 2022

*/

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <set>
#include <list>

using namespace std;

int findHead(list<pair<int, int>>& ruls, int i) // i - вершина из которой начать поиск истока
{
    list<pair<int, int>> ::iterator it;
    for (it = ruls.begin(); it != ruls.end(); it++)
    {
        if (it->second == i)
        {
            return it->first;
        }
    }
    return -1;
}
void delRul(list<pair<int, int>>& ruls, int a)
{
    list<pair<int, int>> ::iterator it;
    for (it = ruls.begin(); it != ruls.end(); it++)
    {
        if (it->first == a)
        {
            ruls.erase(it);
        }
    }
}
int NextNod(vector <bool>& vis)
{
    for (int i = 1; i < vis.size(); i++)
    {
        if (vis[i] == false)
            return i;
    }
    return 0;
}

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Russian");
    if (argc != 3)
    {
        cout << "Неверное количество аргуметнов \n"
            << "Чтобы использовать: TopSort.exe <Input file> <Output file>" << endl;
        return 1;
    }

    ifstream inputFile;
    inputFile.open(argv[1]);

    ofstream outputFile;
    outputFile.open(argv[2]);

    list<pair<int, int>> ruls;

    set<int> dots;

    int N{}, X{}, Y{};
    inputFile >> N;
    for (int i = 0; i < N; i++)
    {
        inputFile >> X >> Y;
        dots.insert(X);
        dots.insert(Y);
        pair<int, int> temp;
        ruls.push_back(make_pair(X, Y));
    }
    vector <bool> vis{};
    for (int i = 0; i < dots.size(); i++)
        vis.push_back(false);

    int loop{};
    vector <int> loopElem;
    vector <int> topSortVector;
    while(int a = NextNod(vis))
    {
        while (findHead(ruls, a) != -1)
        {
            a = findHead(ruls, a);
            loop++;
            if (loop > dots.size())
            {
                if (loop > 2 * dots.size())
                    break;
                loopElem.push_back(a);
            }
        }
        topSortVector.push_back(a);
        delRul(ruls, a);
        vis[a] = true;
    }
    if (loopElem.size() != 0)
    {
        outputFile << "No" << endl;
        outputFile << loopElem[loopElem.size() - 1] << " ";
        for (int i = loopElem.size() - 2; i > 0; i--)
            if (loopElem[loopElem.size() - 1] != loopElem[i])
            {
                outputFile << loopElem[i] << " ";
            }
            else
            {
                outputFile << loopElem[loopElem.size() - 1] << " ";
                break;
            }
    }
    else
    {
        outputFile << "Yes" << endl;
        for (int i = 0; i < topSortVector.size(); i++)
                outputFile << topSortVector[i] << " ";
    }
    return 0;
}