#include "Binary_tree.h"
using namespace std;

vector<double> readFrom(int variant)
{
    auto stringToDouble = [](string line_numbers){
        // подсчет количества чисел
        int number_counter = 1;
        for(int i = 0; i < line_numbers.size(); i++)
        {
            if (line_numbers[i]==';')
                number_counter++;
        }
        vector<string> str_numbers(number_counter);
        vector<double> numbers;
        int str_numbers_index = 0;
        // создание массива строк с числами
        for (int i = 0; i < line_numbers.size(); i++)
        {
            if (line_numbers[i] != ';')
                str_numbers[str_numbers_index].push_back(line_numbers[i]);
            if (line_numbers[i] == ';')
                str_numbers_index++;
        }
        // преобразование строк в числа
        for (int i = 0; i < str_numbers.size(); i++)
        {
            numbers.push_back(strtod(str_numbers[i].data(), nullptr));
        }
        return numbers;
    };

    string line;
    vector<string> lines;
    ifstream in("E:\\123.csv");
    if (in.is_open())
    {
        while (getline(in, line))
        {
            lines.push_back(line);
        }
    }
    in.close();
    return stringToDouble(lines[variant-1]);
}

int main() {
    Binary_tree<int> tree;
    /*vector<double> numbers = readFrom(1);

    for(int i = 0; i < numbers.size(); i++)
        tree.add_elem(numbers[i]);*/
    for (int i = 0; i < 15; i++)
        tree.add_elem(rand()%20);
    tree.printTree();
    return 0;
}
