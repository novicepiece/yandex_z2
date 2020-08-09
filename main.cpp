#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <clocale>

using std::cout;
using std::cin;

std::ifstream fin("data.txt");
std::ofstream fout("out.txt");

std::vector<std::pair<std::string, std::string>> data;
// 3 - type
// 5 - name

std::string getWord(std::string &str, const char &divider)
{
    std::string result = "";

    int i;
    for (i = 0; i < str.length() && str[i] != divider; i++)
    {
        result += str[i];
    }

    str.erase(0, i + 1);
    return result;
}

void initialize()
{
    std::string str;
    getline(fin, str);

    while (!str.empty())
    {
        getWord(str, '\t');
    }
}

void processLine()
{
    std::string str;
    getline(fin, str);
    size_t i = 0;
    std::pair<std::string, std::string> pair_in;

    while (!str.empty())
    {
        std::string word = getWord(str, '\t');

        if (i == 3)
        {
            pair_in.first = word;
        }
        else if (i == 5)
        {
            pair_in.second = word;
            data.push_back(pair_in);
        }

        i++;
    }
}


int main()
{
    setlocale(LC_ALL, "Russian");

    uint64_t result = 0;

    initialize();

    while (!fin.eof())
    {
        processLine();
    }

    for (size_t i = 0; i < data.size(); i++)
    {
        uint8_t mult = 1;

        if (data[i].first == "в.")
        {
            mult = 2;
        }
        else if (data[i].first == "г.")
        {
            mult = 7;
        }
        else if (data[i].first == "г. п.")
        {
            mult = 3;
        }

        result += (data[i].first.length() + 1 + data[i].second.length()) * mult;
        fout << data[i].first << ' ' << data[i].second << '\n';
    }

    cout << result << ' ' << data.size() << '\n';
    return 0;
}
