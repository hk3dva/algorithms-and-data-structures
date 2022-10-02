
#include <stdio.h>
#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>


#include <ctime>

using namespace std;
/*
13.3. Алгоритм Бойера – Мура (6)
Требуется найти все вхождения образца в текстовом файле методом Бойера – Мура. В файле нет переноса слов. Образец может включать пробелы и переходить с одной строки файла на другую. Конец строки файла может интерпретироваться как пробел. Результаты поиска не должны зависеть от регистра букв, то есть каждая буква в образце и файле может быть как строчной, так и прописной.
Ввод из файла INPUT.TXT. Первая строка файла является образцом и имеет длину от 1 до 255. Вторая строка задает имя текстового файла.
Вывод в файл OUTPUT.TXT. Вывести в каждой строке через пробел последовательность номеров строк и позиций в строке, начиная с которых образец входит в текст. Нумерация строк и позиций в строке начинается с 1. Если вхождений нет, вывести No.
Шабалин Кирилл ПС-23

Visual Studio 2022
*/

void StopChar(string& str, map <char, int>& m)
{
    string s = str;
    reverse(s.begin(), s.end());
    for (size_t i = 1; i < s.size(); i++)
    {
        if (m.find(s[i]) == m.end())
        {
            m[s[i]] = i;
        }
    }
    if (m.find(s[0]) == m.end())
    {
        m[s[0]] = s.size();
    }
}

int check(const string& text, const string& sample, map<char, int>& m, const size_t pos)
{  
    string str = text.substr(pos, sample.size());
    string samp = sample;

    for (int i = samp.size() - 1; i > 0 ; i--)
    {
        if (char(tolower(str[i])) != samp[i])
        {
            if (m.find((char(tolower(str[i])))) != m.end())
                return m.find(char(tolower(str[i])))->second;
            return i;
        }
    }
    return -1;
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

    string text{};
    string sample{};
    getline(inputFile, sample);
    transform(sample.begin(), sample.end(), sample.begin(), ::tolower);
    map <char, int> stop;
    StopChar(sample, stop);

    inputFile >> text;

    ofstream outputFile;
    outputFile.open(argv[2]);

    ifstream readFile;
    readFile.open(text);

    size_t i = 0;
    text = "";

    string helpString{};
    int row = 1;

    bool find = false;

    vector <size_t> size;
    size.push_back(0);

    while (getline(readFile, helpString))
    {
        text += helpString + " ";
        size.push_back(helpString.size() + 1);

        while (i + sample.size() < text.size())
        {
            int dop = check(text, sample, stop, i);
            if (dop == -1)
            {
                outputFile << row << " " << i + 1 << endl;//вывод
                find = true;
                i++;
            }
            else
            {
                i += dop;
            }
            if (i >= size[row])
            {
                i -= size[row];
                text = text.substr(size[row]);
                row++;
            }
        }
    }
    if (!find)
    {
        outputFile << "No" << endl;
    }

    int end = clock(); // засекаем время окончания
    cout << (end - start) / CLOCKS_PER_SEC << " seconds"; // вывод результата работы на экран
    return 0;
}

