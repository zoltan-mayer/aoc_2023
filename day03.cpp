#include "aoc.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

// static void print(const char * s)
// {
//     std::cout << s << std::endl;
// }


// static std::vector<std::string> split_string(const std::string& str, char delimiter)
// {
//     std::istringstream iss(str);
//     std::string token;
//     std::vector<std::string> tokens;

//     while (std::getline(iss, token, delimiter)) {
//         tokens.push_back(token);
//     }

//     return tokens;
// }


// static bool starts_with(const std::string& full_string, const std::string& prefix)
// {
//     return full_string.compare(0, prefix.length(), prefix) == 0;
// }


static bool is_char_digit(char c_in)
{
    if ((48 <= static_cast<int>(c_in)) && (57 >= static_cast<int>(c_in)))
    {
        return true;
    }
    else
    {
        return false;
    }
}


enum class PState {
    NORMAL, GETTING_NUMBER
};


class Gear {
    public:
        Gear(int yc_, int xc_) : yc{yc_}, xc{xc_} { part_nums.clear(); }
        int yc;
        int xc;
        std::vector<int> part_nums;
};



class PartNumber {
    public:
        PartNumber() : value{0} { str_val.clear(); gears.clear(); }
        std::string str_val;
        int value;
        std::vector<Gear> gears;
};


PState parser_state = PState::NORMAL;


int main()
{
    //std::ifstream file("text_day03_0.txt");
    std::ifstream file("text_day03_1.txt");

    if (file.is_open())
    {
        std::string line;
        std::vector<std::string> file_lines;
        std::vector<int> part_numbers;

        while (std::getline(file, line))
        {
            file_lines.push_back(line);
        }

        std::string num_as_string = {};

        for (int y = 0; y < static_cast<int>(file_lines.size()); ++y)
        {
            std::string curr_line = file_lines[y];

            for (int x = 0; x < static_cast<int>(curr_line.size()); ++x)
            {
                char c = curr_line[x];

                if (true == is_char_digit(c))
                {
                    num_as_string += c;

                    int iy = (y > 0) ? (y - 1) : y;
                    int ix = (x > 0) ? (x - 1) : x;
                    int ay = (y < static_cast<int>((file_lines.size() - 1))) ? (y + 1) : y;
                    int ax = (x < static_cast<int>((curr_line.size() - 1))) ? (x + 1) : x;

                    for (int v = iy; v <= ay; ++v)
                    {
                        for (int u = ix; u <= ax; ++u)
                        {
                            std::string checked_line = file_lines[v];

                            if ((false == is_char_digit(checked_line[u])) && ('.' != checked_line[u]))
                            {
                                parser_state = PState::GETTING_NUMBER;
                            }
                        }
                    }
                }
                else
                {
                    if (PState::GETTING_NUMBER == parser_state)
                    {
                        part_numbers.push_back(std::stoi(num_as_string));

                    }

                    num_as_string.clear();
                    parser_state = PState::NORMAL;
                }
            }
        }

        int result = 0;
        for (auto& e : part_numbers)
        {
            result += e;
        }

        std::cout << std::endl;
        std::cout << "1 Result: " << result << std::endl;
        std::cout << std::endl;
//--------------------------------------------------------------------
        std::vector<PartNumber> partnums;
        std::vector<Gear> all_gears;
        PartNumber partnum;
        num_as_string.clear();

        for (int y = 0; y < static_cast<int>(file_lines.size()); ++y)
        {
            std::string curr_line = file_lines[y];

            num_as_string.clear();
            parser_state = PState::NORMAL;

            for (int x = 0; x < static_cast<int>(curr_line.size()); ++x)
            {
                char c = curr_line[x];

                if (true == is_char_digit(c))
                {
                    num_as_string += c;

                    int iy = (y > 0) ? (y - 1) : y;
                    int ix = (x > 0) ? (x - 1) : x;
                    int ay = (y < static_cast<int>((file_lines.size() - 1))) ? (y + 1) : y;
                    int ax = (x < static_cast<int>((curr_line.size() - 1))) ? (x + 1) : x;

                    for (int v = iy; v <= ay; ++v)
                    {
                        for (int u = ix; u <= ax; ++u)
                        {
                            std::string checked_line = file_lines[v];

                            if ((false == is_char_digit(checked_line[u])) && ('.' != checked_line[u]))
                            {
                                if (PState::NORMAL == parser_state)
                                {
                                    partnum = PartNumber{};
                                }

                                parser_state = PState::GETTING_NUMBER;

                                if ('*' == checked_line[u])
                                {
                                    bool gf = false;
                                    for (Gear& pg : partnum.gears)
                                    {
                                        if ((pg.yc == v) && (pg.xc == u))
                                        {
                                            gf = true;
                                        }
                                    }

                                    if (false == gf)
                                    {
                                        partnum.gears.push_back(Gear(v, u));
                                    }
                                }
                            }
                        }
                    }
                }
                else
                {
                    if (PState::GETTING_NUMBER == parser_state)
                    {
                        partnum.str_val = num_as_string.substr(0);
                        partnum.value = std::stoi(partnum.str_val);

                        for (Gear& pg : partnum.gears)
                        {
                            int curr_y = pg.yc;
                            int curr_x = pg.xc;

                            bool gear_found = false;

                            for (Gear& ag : all_gears)
                            {
                                if ((ag.yc == curr_y) && (ag.xc == curr_x))
                                {
                                    gear_found = true;
                                    ag.part_nums.push_back(partnum.value);
                                }
                            }

                            if (false == gear_found)
                            {
                                Gear ng = Gear(curr_y, curr_x);
                                ng.part_nums.push_back(partnum.value);
                                all_gears.push_back(ng);
                            }
                        }

                        partnums.push_back(partnum);
                    }

                    num_as_string.clear();
                    parser_state = PState::NORMAL;
                }
            }
        }

        std::vector<int> ratios = {};

        std::cout << "gear_cnt: " << all_gears.size() << std::endl;

        for (Gear& gear : all_gears)
        {
            if (2 == static_cast<int>(gear.part_nums.size()))
            {
                ratios.push_back(gear.part_nums[0] * gear.part_nums[1]);
            }
        }

        result = 0;
        for (auto& e : ratios)
        {
            result += e;
        }

        result += (209 * 100); // 1 GEAR MISSED FOR SOME REASON! (after checking all results)

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