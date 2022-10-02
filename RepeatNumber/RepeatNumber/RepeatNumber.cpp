#include <iostream>
#include <vector>
#include <fstream>
#include <map>
using namespace std;

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Russian");
    unsigned int start_time = clock();
    if (argc != 3)
    {
        cout << "Usage: RepeatNumber.exe <Input file> <Output file>" << endl;
        return 1;
    }

    ifstream inputFile(argv[1]);
    map <int, int> vec;
    int N{}, k{};

    inputFile >> N;
    for (int i = 0; i < N; i++)
    {
        inputFile >> k;
        auto it = vec.find(k);
        if (it != vec.end())
        {
            it->second++;
        }
        else
        {
            vec[k] = 1;
        }
    }
    int max = INT32_MIN;
    int num = INT32_MAX;
    for (auto i : vec)
    {
        if (i.second > max)
        {
            max = i.second;
            num = i.first;
        }
        if (i.first < num && max == i.second)
        {
            max = i.second;
            num = i.first;
        }
    }
    cout << num << " " << max << endl;
}

