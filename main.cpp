#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <clocale>

using std::cout;
using std::cin;

std::ifstream fin("data.txt");
std::ofstream fout("results.txt");

std::vector< std::pair<std::string, std::string> > data;
// 3 - type
// 5 - name


// Средние значения количества въездов для каждого вида поселения
const double city_entry_counter = 8.2; // Город
const double village_entry_counter = 2.2; // Деревня
const double farm_entry_counter = 1.6; // Хутор
const double urban_village_entry_counter = 3.6; // Городской поселок
const double agro_entry_counter = 3.4; // Агрогородок
const double township_entry_counter = 3.4; // Поселок
const double station_entry_counter = 2; // Станция
const double working_entry_counter = 3.3; // Рабочий поселок

std::string getWord(std::string &str, uint16_t word_number, const char &divider = '\t') // Функция, вырезающее слово из строки
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

void initialize() // Игнорирование вводной строки
{
    std::string str;
    getline(fin, str);
}

void processLine() // Обработка одной строки с населенным пунктом
{
    std::string str;
    getline(fin, str);
    size_t i = 0;
    data.push_back(std::make_pair("%NOTYPE%", "%NONAME%"));

    while (!str.empty())
    {
        std::string word = getWord(str, '\t');

        if (i == 3) // Запись 2его столбика с типом поселения
        {
            data[data.size() - 1].first = word;
        }
        else if (i == 5) // Запись 4ого столбика с названием поселения на белорусском
        {
            data[data.size() - 1].second = word;
            break; // Больше нам ничего не надо в этой строке
        }

        i++;
    }
}


int main()
{
    setlocale(LC_ALL, "Russian");

    double result = 0; // Итоговое количество символов

    initialize();

    while (!fin.eof()) // Обработка всей базы
    {
        processLine();
    }

    data.pop_back(); // Последняя строка пустая

    // Счетчики количества представителей каждого типа населенного пункта
    uint16_t city_counter = 0;
    uint16_t village_counter = 0;
    uint16_t farm_counter = 0;
    uint16_t urban_village_counter = 0;
    uint16_t agro_counter = 0;
    uint16_t township_counter = 0;
    uint16_t station_counter = 0;
    uint16_t working_counter = 0;

    for (size_t i = 0; i < data.size(); i++) // Подсчет результата из имеющейся информации
    {
        double entry_counter = 1;

        if (data[i].first == "г.") // Город
        {
            entry_counter = city_entry_counter;
            city_counter++;
        }
        else if (data[i].first == "в." || data[i].first == "мяст.") // Деревня
        {
            entry_counter = village_entry_counter;
            village_counter++;
        }
        else if (data[i].first == "х.") // Хутор
        {
            entry_counter = farm_entry_counter;
            farm_counter++;
        }
        else if (data[i].first == "г. п." || data[i].first == "к. п.") // Городской поселок
        {
            entry_counter = urban_village_entry_counter;
            urban_village_counter++;
        }
        else if (data[i].first == "аг.") // Агрогородок
        {
            entry_counter = agro_entry_counter;
            agro_counter++;
        }
        else if (data[i].first == "п.") // Поселок
        {
            entry_counter = township_entry_counter;
            township_counter++;
        }
        else if (data[i].first == "ст." || data[i].first == "рзд" || data[i].first == "раз’езд" ) // Станция
        {
            entry_counter = station_entry_counter;
            station_counter++;
        }
        else if (data[i].first == "р. п.") // Рабочий поселок
        {
            entry_counter = working_entry_counter;
            working_counter++;
        }
        else
        {
            fout << "|" << "UNNKOWN!!! " << data[i].first << "|\n"; // На случай неучтенного типа поселения
        }

        uint16_t symbol_counter = data[i].first.length() + 1 + data[i].second.length(); // Сокращение типа города + пробел + название на белорусском
        result += symbol_counter * entry_counter; // Перемножение символов на кол-во въездов
    }


    // Вывод
    fout << "There are " << (long)result << " symbols on road entry signs.\n";
    fout << "There are " << data.size() << " settlements.\n";
    fout << city_counter << " cities.\n";
    fout << village_counter << " villages.\n";
    fout << farm_counter << " farms.\n";
    fout << urban_village_counter << " urban villages.\n";
    fout << agro_counter << " agro-towns.\n";
    fout << township_counter << " townships.\n";
    fout << station_counter << " stations.\n";
    fout << working_counter << " working towns.\n";

    cout << "There are " << (long)result << " symbols on road entry signs.\n";
    cout << "There are " << data.size() << " settlements.\n";
    cout << city_counter << " cities.\n";
    cout << village_counter << " villages.\n";
    cout << farm_counter << " farms.\n";
    cout << urban_village_counter << " urban villages.\n";
    cout << agro_counter << " agro-towns.\n";
    cout << township_counter << " townships.\n";
    cout << station_counter << " stations.\n";
    cout << working_counter << " working towns.\n";

    return 0;
}
