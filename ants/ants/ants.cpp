#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
/*
7.4. Муравьи (8)
Юный натуралист Билл изучает муравьев. Его муравьи питаются исключительно яблоками, растущими на диких яблонях. Имеется карта с координатами N муравейников и N яблонь. Муравьи из каждого муравейника добираются до яблони кратчайшим путем по прямой. Требуется так распределить яблони между муравейниками, чтобы
у каждого муравейника была единственная яблоня;
каждая яблоня принадлежала только одному муравейнику;
пути муравьев из разных муравейников к своим яблоням не пересекались.
Ввод из файла INPUT.TXT. Первая строка единственное целое число N (1 ≤ N ≤ 100). Далее в N строках заданы через пробел координаты Xi, Yi (-10000 ≤ Xi, Yi ≤ 10000) муравейников. В последующих N строках заданы координаты яблонь. Никакие три точки не лежат на одной прямой.
Вывод в файл OUTPUT.TXT состоит из N строк по одному целому числу в строке. Число в i-й строке определяет номер яблони, предназначенной для i-го муравейника.

Шабалин Кирилл Пс-23

Visual Studio 2022
*/
using namespace std;

const int EPS = 0.00001;

struct Point
{
    string type;
    int numb;
    int x;
    int y;
};

map <int, int> PAIRS;

bool FileCor(std::ifstream& inpFile, std::ofstream& outFile) //проверка для фалов
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

double len2(Point a)
{
    return a.x * a.x + a.y * a.y;
}

double PolarAngle(Point p)
{
    return atan2(1.0 * p.y, 1.0 * p.x);
}

bool PolAngleSort(Point a, Point b)
{
    if (fabs(PolarAngle(a) - PolarAngle(b)) < EPS)
        return len2(a) < len2(b);
    return PolarAngle(a) < PolarAngle(b);
}

bool PushMass(std::ifstream& inpFile, vector <Point>& mass, int N, string type)
{
    for (int i = 0; i < N; i++)
    {
        int x{};
        int y{};
        inpFile >> x >> y;
        if ((x < -10000 || x > 10000) && (y < -10000 || y > 10000))
        {
            cout << x << " " << y << ": Число не входит в границы -10000 <= x, y <= 10000" << endl;
            return false;
        }
        mass.push_back({ type, i + 1, x, y });
    }
    return true;
}

void MoveAll(vector <Point>& coord)
{
    Point were = coord[0];
    for (int i = 0; i < coord.size(); i++)
    {
        if (coord[i].y < were.y)
            were = coord[i];
        if (coord[i].y == were.y)
            if (coord[i].x < were.x)
                were = coord[i];
    }
    for (int i = 0; i < coord.size(); i++)
    {
        coord[i].x -= were.x;
        coord[i].y -= were.y;
    }
}

void addRevPair(Point a, Point b)
{
    if (a.type == "Ant")
    {
        PAIRS[a.numb] = b.numb;
    }
    else
    {
        PAIRS[b.numb] = a.numb;
    }
}

bool DivMas(vector <Point>& masAll, vector <Point>& firPart, vector <Point>& secPart)
{
    int countAnt{};
    int countTree{};
    int countAntRigth = masAll.size() / 2;
    int countTreeRigth = masAll.size() / 2;
    int stop{};
    for (int i = 0; i <= masAll.size(); i++)
    {
        if ((countTree == countTreeRigth && countAnt == countAntRigth) || (countTree == countAnt && countAnt != 0))
        {
            stop = i;
            break;
        }
        if (masAll[i].type == "Ant")
        {
            countAnt++;
            countAntRigth--;
        }
        if (masAll[i].type == "Tree")
        {
            countTree++;
            countTreeRigth--;
        }
    }
    if (stop != 0 && stop != masAll.size())
    {
        for (int i = 0; i < stop; i++)
            firPart.push_back(masAll[i]);

        for (int i = stop; i < masAll.size(); i++)
            secPart.push_back(masAll[i]);
    }
    else
    {
        if (masAll[0].type != masAll[masAll.size() - 1].type)
        {
            firPart.push_back(masAll[0]);
            firPart.push_back(masAll[masAll.size() - 1]);
            for (int i = 1; i < masAll.size() - 1; i++)
                secPart.push_back(masAll[i]);
        }

    }
    if (firPart.size() == 0 || secPart.size() == 0)
        return false;
    return true;
}
void ShowAnser(std::ofstream& outFile)
{
    map <int, int> ::iterator it = PAIRS.begin();
    for (int i = 0; it != PAIRS.end(); i++, it++)
        outFile << it->second << endl;
}

bool scanLine(vector <Point>& mas)
{
    vector <Point> moved = mas;
    //Перенести начало координат в самую левую точку из самых нижних
    MoveAll(moved);

    //Отсортировать точки по полярному углу
    sort(moved.begin(), moved.end(), PolAngleSort);

    //Разделение на половины
    if (moved.size() == 2)
    {
        addRevPair(moved[0], moved[1]);
        return true;
    }
    vector <Point> temp1{};
    vector <Point> temp2{};
    if (DivMas(moved, temp1, temp2))
    {
        scanLine(temp1);
        scanLine(temp2);
    }
    return true;
}

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        cout << "Неверное количество аргуметнов \n"
            << "Чтобы использовать: Ants.exe <Input file> <Output file>" << endl;
        return 1;
    }

    ifstream inputFile;
    inputFile.open(argv[1]);

    std::ofstream outputFile;
    outputFile.open(argv[2]);

    if (!FileCor(inputFile, outputFile))
        return 1;

    int N{};
    inputFile >> N;
    if (N < 1 || N > 100)
    {
        cout << "N не входит в границы 1 <= N <= 100" << endl;
        return 1;
    }
    vector <Point> anthills{};
    vector <Point> trees{};
    if (!PushMass(inputFile, anthills, N, "Ant") || !PushMass(inputFile, trees, N, "Tree"))
        return 1;

    vector <Point> allMas{};
    for (int i = 0; i < anthills.size(); i++)
    {
        allMas.push_back(anthills[i]);
        allMas.push_back(trees[i]);
    }
    scanLine(allMas);
    ShowAnser(outputFile);
    return 0;
}
