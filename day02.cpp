#include "aoc.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

const int max_red   = 12;
const int max_green = 13;
const int max_blue  = 14;

// static void print(const char * s)
// {
//     std::cout << s << std::endl;
// }


static std::vector<std::string> split_string(const std::string& str, char delimiter)
{
    std::istringstream iss(str);
    std::string token;
    std::vector<std::string> tokens;

    while (std::getline(iss, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}


static bool starts_with(const std::string& full_string, const std::string& prefix)
{
    return full_string.compare(0, prefix.length(), prefix) == 0;
}



static bool is_set_valid(std::string set_in)
{
    bool ret_val = true;
    int red_cnt = 0;
    int green_cnt = 0;
    int blue_cnt = 0;

    std::vector<std::string> color_counts = split_string(set_in, ',');

    for (std::string a_color : color_counts)
    {
        a_color = a_color.substr(1); // Remove first space char.

        std::vector<std::string> count_name = split_string(a_color, ' ');

        if (starts_with(count_name[1], "red"))
        {
            red_cnt += std::stoi(count_name[0]);
        }

        if (starts_with(count_name[1], "green"))
        {
            green_cnt += std::stoi(count_name[0]);
        }

        if (starts_with(count_name[1], "blue"))
        {
            blue_cnt += std::stoi(count_name[0]);
        }
    }

    if (max_red < red_cnt)     { ret_val = false; }
    if (max_green < green_cnt) { ret_val = false; }
    if (max_blue < blue_cnt)   { ret_val = false; }

    return ret_val;
}


static void get_set_counts(std::string set_in, int * p_r, int * p_g, int * p_b)
{
    std::vector<std::string> color_counts = split_string(set_in, ',');

    for (std::string a_color : color_counts)
    {
        a_color = a_color.substr(1); // Remove first space char.

        std::vector<std::string> count_name = split_string(a_color, ' ');

        if (starts_with(count_name[1], "red"))
        {
            *p_r = std::stoi(count_name[0]);
        }

        if (starts_with(count_name[1], "green"))
        {
            *p_g = std::stoi(count_name[0]);
        }

        if (starts_with(count_name[1], "blue"))
        {
            *p_b = std::stoi(count_name[0]);
        }
    }
}


int main()
{
    //std::ifstream file("text_day02_0.txt");
    std::ifstream file("text_day02_1.txt");

    if (file.is_open())
    {
        std::string line;
        std::vector<int> valid_ids = {};

        int game_id = 0;

        while (std::getline(file, line))
        {
            ++game_id;

            std::vector<std::string> line_parts = split_string(line, ':');

            std::vector<std::string> line_sets = split_string(line_parts[1], ';');

            bool is_valid = true;

            for (std::string a_set : line_sets)
            {
                is_valid &= is_set_valid(a_set);
            }

            if (true == is_valid)
            {
                valid_ids.push_back(game_id);
            }
        }

        int result = 0;
        for (auto& e : valid_ids)
        {
            result += e;
        }

        std::cout << std::endl;
        std::cout << "1 Result: " << result << std::endl;
        std::cout << std::endl;
//--------------------------------------------------------------------
        file.clear();
        file.seekg(0, std::ios::beg);
        std::vector<int> game_powers = {};

        while (std::getline(file, line))
        {
            std::vector<std::string> line_parts = split_string(line, ':');

            std::vector<std::string> line_sets = split_string(line_parts[1], ';');

            int reds = 0;
            int greens = 0;
            int blues = 0;

            for (std::string a_set : line_sets)
            {
                int r = 0;
                int g = 0;
                int b = 0;
                get_set_counts(a_set, &r, &g, &b);
                if (reds < r) { reds = r; }
                if (greens < g) { greens = g; }
                if (blues < b) { blues = b; }
            }

            game_powers.push_back(reds * greens * blues);
        }

        result = 0;
        for (auto& e : game_powers)
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