/* Татьянина Мария, ПС-23 vs2022 c++
10.2. Последовательность 2 (5)
Каждый член последовательности десятичных цифр d1, d2, d3..., начиная с четвёртого, вычисляется по формуле di  = (di-3 + di-2  + di-1) mod x.
По заданным d1, d2, d3, x найти N-й член последовательности.
Ввод из файла INPUT.TXT. В первой строке находятся d1, d2, d3, x, разделённые пробелами, во второй - число N.
Вывод в файл OUTPUT.TXT. Вывести одну цифру - dN.
Ограничения: 1 ≤ N ≤ 10 ^ 30, 2 ≤  x ≤ 10, время 1 с.
Примеры
Ввод 1    Ввод 2
1 4 8 10  5 5 5 10
4         1000000000000000
Вывод 1   Вывод 2
3         5
*/
#pragma comment(lib, "libgmp.lib")
#pragma warning( disable : 4146 )

#include <iostream>
#include <fstream>
#include <ctime> 

#include <gmpxx.h>
#include <gmp.h>

using namespace std;

int x{};
mpz_class globEnd;

mpz_class rec(mpz_class N, int& a, int& b, int& c)
{
    if (N != globEnd)
    {
        cout << N << endl;
        int t = (a + b + c) % x;
        a = b, b = c, c = t;
        return rec(N + 1, a, b , c );
    }
    cout << "res: " << a << ' ' << b << " " << c << endl;
    return c;
}

int main(int argc, char* argv[])
{
    int start = clock(); // засекаем время старта
    setlocale(LC_ALL, "Russian");
    if (argc != 3)
    {
        cout << "Неверное количество аргуметнов \n"
            << "Чтобы использовать: Boyer-Myr.exe <Input file> <Output file>" << endl;
        return 1;
    }

    ifstream inputFile;
    inputFile.open(argv[1]);

    ofstream outputFile;
    outputFile.open(argv[2]);

    mpz_class N = 3;
    int a{}, b{}, c{};
    inputFile >> a >> b >> c >> x;
    inputFile >> globEnd;

    cout << rec(N, a ,b ,c)<< endl;

    int end = clock(); 
    cout << (end - start) / CLOCKS_PER_SEC << " seconds"; 

    return 0;
}