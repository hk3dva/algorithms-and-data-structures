#include <stdio.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <map>
using namespace std;
/*
19.23. Грибы (4)
Вася и Петя любят собирать грибы. Вася придумал, что подарить на день рождения Пети. День рождения отмечается на Петиной даче. Рядом с дачей проходит заросшая лесная тропинка. Грибы растут прямо на ней. Накануне дня рождения Вася проехал на велосипеде по тропинке. На его велосипеде имеется счетчик, поэтому Вася записал координаты точек, где есть грибы. Для большей точности он проехал еще несколько раз, добавляя в список координаты не замеченных ранее грибов. Полученный список был торжественно вручен Пете.
Петя сказал, что грибы не велосипеде не собирают, а праздничные хлопоты ограничивают его во времени. Он собирается пройти с корзинкой ровно d метров и попросил Васю найти такую ближайшую к даче точку, чтобы на следующих d метрах тропинки грибов оказалось как можно больше. Помогите Васе.
Ввод из файла INPUT.TXT. В первой строке содержатся количество обнаруженных грибов n и расстояние d (1 ≤ n ≤ 105; 1 ≤ d ≤ 109). Во второй строке заданы через пробел координаты грибов x1, x2, …, xn (0 ≤ xi ≤ 109). Некоторые грибы растут кучками, поэтому координаты могут повторяться. Все значения целые.
Вывод в файл OUTPUT.TXT. В первой строке выводится наименьшая координата y такая, что на отрезке [y, y + d], включая его концы, находится наибольшее количество “грибных” точек. Во второй строке выдается количество грибов на отрезке [y, y + d].
Примеры
Ввод
6 2
4 2 3 1 2 4

Шабалин Кирилл Пс-23

Visual Studio 2022
*/

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Russian");
    if (argc != 3)
    {
        cout << "Неверное количество аргуметнов \n"
            << "Чтобы использовать: Mushrooms.exe <Input file> <Output file>" << endl;
        return 1;
    }

    ifstream inputFile;
    inputFile.open(argv[1]);
    ofstream outputFile;
    outputFile.open(argv[2]);

    int N{}, Len{};
    inputFile >> N >> Len;

    map <int, int> cord;
    int k{};
    for (int i = 0; i < N; i++)
    {
        inputFile >> k;
        if (cord.find(k) != cord.end())
        {
            cord.find(k)->second += 1;
        }
        else
        {
            cord[k] = 1;
        }
    }
    map <int, int> ::iterator it = cord.begin();
    int countMax{};
    int pos{};
    map <int, int> ::iterator itNext;
    for (int i = 0; it != cord.end(); it++, i++)
    { 
        int count{};
        itNext = it;
        count += itNext->second;
        itNext++;
        while (itNext->first - it->first <= Len && itNext != cord.end())
        {
            count += itNext->second;
            itNext++;
        }
        if (count > countMax)
        {
            itNext--;
            pos = itNext->first - Len;
            countMax = count;
        }
    }
    outputFile << pos << endl;
    outputFile << countMax << endl;
    return 0;
}
