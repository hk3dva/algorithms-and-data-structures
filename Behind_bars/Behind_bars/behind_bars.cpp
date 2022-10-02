/******************************************************************************
11.11. �� �������� (6)
��� ��������, ���� � ����, ����� � ��������. ������ ����� � ��������� ������������� ������, ��� ����� ������� ��������, � ��������� ���������� ��������. ����� ������� �������� ����� ���� �����. ������� ����� ����� ������ ����������, � ���� ��������� ������� � ������� ���, ����� ��������� �����. ����� �������� � ����� ���� ��� ����� ���� (���� ���-����, ��� ��������� ����� ����), ���� ��������� ����� ����� ��������� ����� �������, ���������� ����� �������� ����������.
���� �� ����� INPUT.TXT. � ������������ ������ �������� ����� ������ ������ �����: ������� �������� ������ �������, ����� ������. ������ ������� �������� ������������ ������ (x1, y1, x2, y2). ��� ����� �����, �� ������ �� ������ 10000.
����� � ���� OUTPUT.TXT. � ������������ ������ ������� ����������� ����������, ������� ����� ���� ����� ����� � ������, ���� ������ ����� ������ ����� ����� �������. ���������� ������ ���� �������� � ����� ������� ����� �������.
������
����
0 1 0 5 1 -1 1 0
�����
1.414
������� ������ �� - 23

Visual Studio 2022
*******************************************************************************/
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <limits>
#include <fstream>
using namespace std;

#define PI 3.14159265

#define ld long double

struct Point
{
    ld x;
    ld y;
};
const ld EPS = 0.00001;
// https://ru.stackoverflow.com/questions/900577/���-�����-����������-����������-�����-�����-���������
ld distance(Point a, Point b)
{
    return sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
}

ld mindifference(Point a, Point b, Point c)
{
    Point t;
    ld l = distance(a, c);
    ld r = distance(b, c);
    for (int i = 0; i <= 100; i++)
    {
        if (l <= r)
        {
            t.x = (a.x + b.x) / 2;
            t.y = (a.y + b.y) / 2;
            r = distance(t, c);
            b.x = (a.x + b.x) / 2;
            b.y = (a.y + b.y) / 2;
        }
        else
        {
            t.x = (a.x + b.x) / 2;
            t.y = (a.y + b.y) / 2;
            l = distance(t, c);
            a.x = (a.x + b.x) / 2;
            a.y = (a.y + b.y) / 2;
        }
    }

    return l;
}
//https://e-maxx.ru/algo/segments_intersection_checking
inline int area(Point a, Point b, Point c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

inline bool intersect_1(int a, int b, int c, int d) {
    if (a > b)  swap(a, b);
    if (c > d)  swap(c, d);
    return max(a, c) <= min(b, d);
}

bool intersect(Point a, Point b, Point c, Point d) {
    return intersect_1(a.x, b.x, c.x, d.x)
        && intersect_1(a.y, b.y, c.y, d.y)
        && area(a, b, c) * area(a, b, d) <= EPS
        && area(c, d, a) * area(c, d, b) <= EPS;
}

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Russian");
    if (argc != 3)
    {
        cout << "�������� ���������� ���������� \n"
            << "����� ������������: \behind_bar.exe <Input file> <Output file>" << endl;
        return 1;
    }

    ifstream inputFile;
    inputFile.open(argv[1]);

    ld x1, y1, x2, y2;

    inputFile >> x1 >> y1 >> x2 >> y2;
    Point A1, B1, A2, B2;
    A1.x = x1;
    A1.y = y1;
    B1.x = x2;
    B1.y = y2;
    inputFile >> x1 >> y1 >> x2 >> y2;
    A2.x = x1;
    A2.y = y1;
    B2.x = x2;
    B2.y = y2;

    ld minLen = numeric_limits<ld>::max();

    if (intersect(A1, B1, A2, B2)) // �����������
    {
        minLen = 0;
        cout << "������������" << endl;
    }
    minLen = min(mindifference(A1, B1, B2), minLen);
    minLen = min(mindifference(A1, B1, A2), minLen);

    ofstream outputFile;
    outputFile.open(argv[2]);

    outputFile << fixed << setprecision(3) << minLen << endl;
    return 0;
}