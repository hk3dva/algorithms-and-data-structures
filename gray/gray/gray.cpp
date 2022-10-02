
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <string>

using namespace std;

//https://russianblogs.com/article/15401674893/
vector<string> gray_code(int n)
{
    if (n == 1)
    {
        vector<string> v;
        v.push_back("0");
        v.push_back("1");
        return v;
    }
    else
    {
        vector<string> v;
        vector<string> v1;
        v1 = gray_code(n - 1);

        for (int i = 0; i < v1.size(); i++)
        {
            v.push_back("0" + v1[i]);
        }
        for (int i = (v1.size() - 1); i > -1; i--)
        {
            v.push_back("1" + v1[i]);
        }
        return v;
    }
}

int main() 
{
    setlocale(LC_ALL, "Russian");
    // - выдать слова кода Грея
    //    заданной размерности, используя рекурсию
    //    и генерацию слов по их номерам;
    cout << "Введите длину слова грея" << endl;

    int n{};
    cin >> n;

    vector <string> gray = gray_code(n);

    for (int i = 0; i < gray.size(); i++)
        cout << gray[i] << endl;


    //-задано множество символов, выдать его
    //    подмножества из заданного числа элементов
    //    в лексикографическом порядке

    vector<string> set;
    cout << "Введите все символы" << endl;
    cout << "Для остановки ввода введите \" ...\"" << endl;

    string str{};
    while (str != "...")
    {
        cin >> str;
        set.push_back(str);
    }
    set.pop_back();
    sort(set.begin(), set.end());

    cout << "Введите длинну последовательности перестоновки" << endl;
    cin >> n;
    //https://translated.turbopages.org/proxy_u/en-ru.ru.88a252a0-62b8ec71-2e309599-74722d776562/https/stackoverflow.com/questions/62570987/using-next-permutation-to-get-all-combinations-of-length-n-c
    //тут я не уверен что надо указывать но на всякий случай 
    std::set<vector<string>> printSet;
    do 
    {
        printSet.emplace(set.begin(), set.begin() + n);
    } while (next_permutation(set.begin(), set.end()));

    for (auto c : printSet)
    {
        for (auto elem : c) 
            cout << elem;
        cout << endl;
    }

    return 0;
}
