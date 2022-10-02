/******************************************************************************
11.12. А у нас в квартире газ (6)
В некотором районе проводится всеобщая газификация. Для этого прежде всего нужно построить газораспределительную станцию. Она может располагаться только на участке магистрального газопровода, соединяющего по прямой пункты A и B. На карте района известны координаты этих пунктов (u1, v1) и (u2, v2) соответственно. От станции протягиваются отдельные прямолинейные трубы к N (N ≤ 100) населенным пунктам c координатами (xi, yi) (-100 ≤ xi, yi  ≤ 100). Известно, что затраты на проведение газовой трубы равны квадрату длины трубы. Требуется указать такие координаты газораспределительной станции, чтобы общие затраты на трубы были минимальны.
Ввод из файла INPUT.TXT. В первой строке задается значения N. Во второй строке указываются через пробел u1, v1, u2, v2. В следующих N строках задаются через пробел координаты xi,  yi  населенных пунктов.
Вывод в файл OUTPUT.TXT. Вывести с десятью знаками после запятой: в первой строке координаты станции, во второй строке минимальную стоимость труб.
Пример
Ввод
2
0 0 4 4
1 1
3 3
Вывод
2.0000000000 2.0000000000
4.0000000000

Татьянина Мария ПС - 23

Visual Studio 2022
*******************************************************************************/

#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;

struct Point
{
    double x;
    double y;
};

double distance(Point a, Point b)
{
    return ((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
}

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Russian");
    unsigned int start_time = clock();
    if (argc != 3)
    {
        cout << "Usage: WeHaveGasAndWhatAboutUs.exe <Input file> <Output file>" << endl;
        return 1;
    }

    ifstream inputFile(argv[1]);

    double N{}, x{}, y{};
    Point pointA{}, pointB{}, point{};

    inputFile >> N;

    inputFile >> pointA.x >> pointA.y;
    inputFile >> pointB.x >> pointB.y;

    vector <Point> vec;

    for (int i = 0; i < N; i++)
    {
        inputFile >> x >> y;
        point.x = x;
        point.y = y;
        vec.push_back(point);
    }

    if (pointA.x > pointB.x || pointA.y > pointB.y)
        swap(pointA, pointB);

    Point v{};
    v.x = pointB.x - pointA.x;
    v.y = pointB.y - pointA.y;

    Point i{};
    i = pointA;

    Point resP{};
    double len = numeric_limits<double>::max();

    for (double t = 0; i.x <= pointB.x && i.y <= pointB.y; t += 0.0000001)
    {
        i.x = pointA.x + v.x * t;
        i.y = pointA.y + v.y * t;
        double count = 0;
        for (int el = 0; el < vec.size(); el++)
        {
            count += distance(i, vec[el]);
        }
        if (count < len)
        {
            resP = i;
            len = count;
            
        }
        
    }
    cout << i.x << " " << i.y << endl;
    ofstream outputFile(argv[2]);
    
    outputFile << fixed << setprecision(10);
    outputFile << round(resP.x * pow(10, 9) / pow(10, 9)) << " " << round(resP.y * pow(10, 9) / pow(10, 9)) << endl;
    outputFile << round(len * pow(10, 9) / pow(10, 9)) << endl;

}
