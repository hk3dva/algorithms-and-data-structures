#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> RES(3);
/*
10.7. Симпсон Гомер (9)
Гомер Симпсон пожертвовал N долларов на распространение дисков с фильмами о себе. Имеется 3 вида дисков, которые продаются по ценам C1, C2 и C3  долларов. Требуется купить как можно больше дисков так, чтобы осталась неизрасходованной как можно меньшая сумма денег.
Ввод из файла INPUT.TXT. В первой строке задается значение N (1 ≤ N ≤ 2×109). Во второй строке C1, C2 и C3 через пробел (1 ≤ C1, C2 , C3 ≤ 2×109). Все числа целые.
Вывод в файл OUTPUT.TXT. В первой строке вывести общее количество покупаемых дисков. Во второй строке выводится остаток средств. В третьей строке через пробел выводится число покупаемых  дисков каждого вида соответственно.

Шабалин Кирилл Пс-23

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

int AmountFinder(vector <int>& prises, const long long cost)
{
    int maxStep = cost / *min_element(prises.begin(), prises.end());
    int minStep = cost / *max_element(prises.begin(), prises.end());
    int f{}, s{}, t{};
    int prevMax{};
    int cprevMax{};
    int newMax{};
    int maxNum{};
    int newMaxNum{};
    RES[2] = cost / prises[2];
    for (int i = 0; i <= maxStep; i++)
    {
        for (int k = 0; k - (cost - i * prises[0]) / prises[1] <= 0; k++)
        {
            f = i;
            s = (cost - i * prises[0]) / prises[1] - k;
            t = (cost - i * prises[0] - s * prises[1]) / prises[2];
            prevMax = RES[0] * prises[0] + RES[1] * prises[1] + RES[2] * prises[2];
            newMax = f * prises[0] + s * prises[1] + t * prises[2];
            newMaxNum = f + s + t;
            if (newMaxNum != maxStep)
                break;
            bool corr = (f >= 0 && s >= 0 && t >= 0);
            if (newMax <= cost && newMaxNum == maxStep && newMax >= prevMax && corr)
            {
                RES[0] = f;
                RES[1] = s;
                RES[2] = t;
                cprevMax = newMax;
                maxNum = newMaxNum;
            }
            if (cprevMax == cost)
                return 0;
        }
    }

    return  0;
}
int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        cout << "Неверное количество аргуметнов \n"
            << "Чтобы использовать: Homer_Simpson.exe <Input file> <Output file>" << endl;
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
    long long cash{};
    inputFile >> cash;
    if (cash < 1 || cash > 2000000000)
    {
        cout << "N не входит в границы 1 <= N <= 2*10^9" << endl;
        return 1;
    }
    vector <int> costs{};
    for (int i = 0; i < 3; i++)
    {
        int cost{};
        inputFile >> cost;
        if (cost < 1 || cost > 2000000000)
        {
            cout << cost << ": Число не входит в границы 1 <= C <= 2*10^9" << endl;
            return 1;
        }
        costs.push_back(cost);
    }

    int balance{};
    AmountFinder(costs, cash);
    outputFile << RES[0] + RES[1] + RES[2] << endl;
    outputFile << cash - (costs[0] * RES[0] + costs[1] * RES[1] + costs[2] * RES[2]) << endl;
    for (int i = 0; i < 3; i++)
    {
        outputFile << RES[i] << " ";
    }
    return 0;
}