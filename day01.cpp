#include "aoc.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

bool starts_with(const std::string& full_string, const std::string& prefix)
{
    return full_string.compare(0, prefix.length(), prefix) == 0;
}


void print(const char * s)
{
    std::cout << s << std::endl;
}


int main()
{
    std::ifstream file("text_day01.txt");
    //std::ifstream file("text_day01_0.txt");

    if (file.is_open())
    {
        std::vector<int> numbers;
        std::string line;
        int val = 0;

        while (std::getline(file, line))
        {
            int lsd_idx = -1;
            int msd_idx = -1;
            val = 0;

            std::reverse(line.begin(), line.end());

            for (int i = 0; i < static_cast<int>(line.length()); ++i)
            {
                char c = line[i];

                if ((49 <= static_cast<int>(c)) && (57 >= static_cast<int>(c)))
                {
                    if (-1 == lsd_idx) { lsd_idx = i; }
                    msd_idx = i;
                }
            }

            val = static_cast<int>(line[lsd_idx]) - 48;
            val += 10 * (static_cast<int>(line[msd_idx]) - 48);

            // std::reverse(line.begin(), line.end());
            // std::cout << val << "    " << line << std::endl;

            numbers.push_back(val);
        }

        int result = 0;
        for (auto& e : numbers)
        {
            result += e;
        }

        std::cout << std::endl;
        std::cout << "1 Result: " << result << std::endl;
        std::cout << std::endl;
//--------------------------------------------------------------------
        file.clear();
        file.seekg(0, std::ios::beg);
        numbers.clear();
        std::vector<std::string> ns = { "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
        std::vector<int> line_numbers = {};

        while (std::getline(file, line))
        {
            val = 0;
            line_numbers.clear();

            for (int i = 0; i < static_cast<int>(line.length()); ++i)
            {
                auto c = line[i];

                if ((49 <= static_cast<int>(c)) && (57 >= static_cast<int>(c)))
                {
                    line_numbers.push_back(static_cast<int>(c) - 48);
                }

                for (int j = 0; j < ns.size(); ++j)
                {
                    if (starts_with(line.substr(i), ns[j]))
                    {
                        line_numbers.push_back(j);
                        break;
                    }
                }
            }

            if (1 == line_numbers.size())
            {
                val = line_numbers[0] * 10;
                val += line_numbers[0];
            }
            else
            {
                val = line_numbers[0] * 10;
                val += line_numbers.back();
            }

            std::cout << val << "    " << line << std::endl;

            numbers.push_back(val);
        }

        result = 0;
        for (auto& e : numbers)
        {
            result += e;
        }

        std::cout << std::endl;
        std::cout << "2 Result: " << result << std::endl;
        std::cout << std::endl;

        file.close();
    }
    else
    {
        std::cout << "Unable to open file" << std::endl;
    }
}