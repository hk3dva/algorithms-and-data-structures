#pragma comment(lib, "libgmp.lib")
#pragma warning( disable : 4146 )

#include <stdio.h>
#include <iostream>
#include <vector> 
#include <cmath>
#include <algorithm>
#include <ctime>  

#include <gmpxx.h>
#include <gmp.h>


using namespace std;

int getSum(const int num)
{
    int count = 0;
    int temp = num;
    do
    {
        count += temp % 10;
        temp /= 10;
    } while (temp);

    return count;
}

bool degreeDifference(const int num, int n)
{
    int ftemp = num;
    vector <int> numberList(n, 0);

    for (int i = 0; i < n; i++)
    {
        numberList[i] = ftemp % 10;
        ftemp /= 10;
    }

    for (int i = 0; i < numberList.size() - 1; i++)
    {
        if (numberList[i] - numberList[i + 1] > 1 || numberList[i] - numberList[i + 1] < -1)
            return false;
    }

    return true;
}


mpz_class LuckTick(mpz_class i, mpz_class j)
{
    if (i == 1 && j < 10)
    {
        return 1;
    }
    if (i == 1 && j >= 10)
    {
        return 0;
    }
    mpz_class res{};
    if (i > 1)
    {      
        for (int l = 0; l < 10 && j - l >= 0; l++)
        {
            res += LuckTick(i - 1, j - l);
        }
    }

    return res;
}

int main()
{
    mpz_class N;
    cin >> N;
    int start = clock();
    mpz_class res{};
    for (mpz_class j = 0; j < 9 * N; j++)
    {
         mpz_class t;
         t = LuckTick(N, j);
         res += t * t;
    }
        
    cout << res + 1 << endl;
    /*
    vector <int> digits;

    half = pow(10, 2 * N) / pow(10, N);
    int Max = pow(10, 2 * N);

    for(int i = 0; i < Max; ++i) // нахождение чисел
    {
        if (getSum(i / half) == getSum(i % half))
            if (degreeDifference(i, 2 * N))
                digits.push_back(i);
    }
    cout << digits.size() << endl;
    */
    int end = clock(); // засекаем время окончания
    int t = (end - start) / CLOCKS_PER_SEC;
    cout << t << " sec" << endl;
    return 0;
}
