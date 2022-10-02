#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

int fill(vector <vector <int >>& fild, int i, int j)
{
    int count{};
    
    if (i - 1 >= 0 && j - 1 >= 0 && fild[i - 1][j - 1] == -1)
        count++;
    if (i - 1 >= 0 && fild[i - 1][j] == -1)
        count++;
    if (i - 1 >= 0 && j + 1 < fild[0].size() && fild[i - 1][j + 1] == -1)
        count++;

    if (j - 1 >= 0 && fild[i][j - 1] == -1)
        count++;
    if (j + 1 < fild[0].size() && fild[i][j + 1] == -1)
        count++;

    if (i + 1 < fild.size() && j - 1 >= 0 && fild[i + 1][j - 1] == -1)
        count++;
    if (i + 1 < fild.size() && fild[i + 1][j] == -1)
        count++;
    if (i + 1 < fild.size() && j + 1 < fild[0].size() && fild[i + 1][j + 1] == -1)
        count++;
  
    return count;
}

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Russian");
    if (argc != 3)
    {
        cout << "Usage: sapper.exe <Input file> <Output file>" << endl;
        return 1;
    }

    int M{}, N{};
    
    ifstream inputFile(argv[1]);
    char c{};
    inputFile >> M >> N;
    vector <vector <int >> fild;
    for (int i = 0; i < M; i++)
    {
        vector <int> t;
        for (int j = 0; j < N; j++)
        {
            inputFile >> c;
            if (c == '*')
            {
                t.push_back(-1);
            }
            else
            {
                t.push_back(0);
            }         
        }
        fild.push_back(t);
    }
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (fild[i][j] == 0)
            {
                fild[i][j] = fill(fild, i, j);
            }
        }
    }
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (fild[i][j] == -1)
                cout << '*' << " ";
            else
                cout << fild[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}

