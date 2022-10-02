﻿#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;
/*
14.4. Казино (9)
Казино в день своего юбилея решило сделать подарок клиентам. Составляется список клиентов в порядке их прихода. Каждый клиент имеет общий баланс игры, выраженный положительным или отрицательным целым числом. Казино устраивает общий фуршет, затраты на который устанавливаются следующим образом. По списку клиентов формируется соответствующий список балансов. Значения двух соседних элементов списка заменяются разностью предыдущего и последующего элементов до тех пор, пока не останется единственное число, определяющее величину затрат на фуршет. Найти такую последовательность операций, чтобы оставшееся число было максимальным. Определить этот максимум.
Ввод из файла INPUT.TXT. В  первой  строке  указывается  количество  элементов  списка  N (3 ≤ N ≤ 105). Во второй строке через пробел задаются N элементов списка балансов A1, A2,…, AN (-104 ≤  Ai  ≤ 104).
Вывод в файл OUTPUT.TXT. В первой строке выводится итоговое максимальное значение. Во второй строке указываются через пробел N-1 целых чисел B1, B2,…, BN-1, определяющих последовательность операций. Выражение вычисляется следующим образом.  Из баланса с номером B1 = k вычитается ближайший следующий баланс, который еще не участвовал в предшествующих операциях в качестве вычитаемого. Результат замещает баланс Ak. Затем подобная операция проводится со значением B2  и т. д. Если имеется несколько решений, вывести любое из них.

Примеры
Ввод 1          Ввод 2
3               3
-5 3 2          2 -6 -3
Вывод 1         Вывод 2
-6              11
2 1             1 1
Шабалин Кирилл ПС - 23
Visual Studio 2022
*/

bool FileCor(std::ifstream& inpFile, std::ofstream& outFile) //проверка дял фалов
{
    if (!inpFile.is_open())
    {
        std::cout << "Failed to open Input file \n";
        return false;
    }
    if (inpFile.bad())
    {
        std::cout << "Failed to read data from input file \n";
        return false;
    }
    if (!outFile.flush())
    {
        std::cout << "Failed to write data to output file\n";
        return false;
    }
    if (!outFile.is_open())
    {
        std::cout << "Failed to open outputfile \n";
        return false;
    }
    return true;
}

void MaxMinus(vector<int>& vec, vector<int>& BVec)
{

    vector <int> t;
    vector <int> tempVec;
    for (int i = 0; i < vec.size() - 1; i++)
    {
        t.push_back(vec[i] - vec[i + 1]);
    }

    int maxElem = *std::max_element(t.begin(), t.end());
    for (int i = 0; i < vec.size(); i++)
    {
        if (vec[i] - vec[i + 1] == maxElem)
        {
            tempVec.push_back(vec[i] - vec[i + 1]);
            i++;
            BVec.push_back(i);
        }
        else
        {
            tempVec.push_back(vec[i]);
        }
    }
    vec.clear();
    for (int i = 0; i < tempVec.size(); i++)
    {
        vec.push_back(tempVec[i]);
    }
}

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "rus");
    if (argc != 3)
    {
        cout << "Неверное количество аргуметнов \n"
            << "Чтобы использовать: casino.exe <Input file> <Output file>" << endl;
        return 1;
    }

    ifstream inputFile;
    inputFile.open(argv[1]);

    std::ofstream outputFile;
    outputFile.open(argv[2]);
    if (!FileCor(inputFile, outputFile))
    {
        cout << endl;
        return 1;
    }
    int N{};
    inputFile >> N;
    if (N < 3 || N > 100000)
    {
        cout << "N не входит в границы 3 <= N <= 100000" << endl;
        return 1;
    }
    vector <int> costs{};
    vector <int> tempCosts{};
    for (int i = 0; i < N; i++)
    {
        int cost{};
        inputFile >> cost;
        if (cost < -10000 || cost > 10000)
        {
            cout << cost << ": Число не входит в границы -10000 <= A <= 10000" << endl;
            return 1;
        }
        costs.push_back(cost);
    }
    while (costs.size() != 1)
    {
        MaxMinus(costs, tempCosts);
    }
    outputFile << costs[0] << endl;
    for (int i = 0; i < tempCosts.size(); i++)
        outputFile << tempCosts[i] << " ";
    return 0;
}
