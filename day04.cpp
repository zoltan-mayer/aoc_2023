#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

// static void print(const char * s)
// {
//     std::cout << s << std::endl;
// }

class Card {
    public:
        Card() : points{0}, matches{0} { winners.clear(); owneds.clear(); }
        std::vector<int> winners;
        std::vector<int> owneds;
        int points;
        int matches;
};


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


// static bool starts_with(const std::string& full_string, const std::string& prefix)
// {
//     return full_string.compare(0, prefix.length(), prefix) == 0;
// }


int main()
{
    //std::ifstream file("text_day04_0.txt");
    std::ifstream file("text_day04_1.txt");

    if (file.is_open())
    {
        std::string line;
        std::vector<std::string> file_lines;
        std::vector<Card> cards;
        std::vector<int> inst_counts;

        while (std::getline(file, line))
        {
            file_lines.push_back(line);
        }

        for (int i = 0; i < static_cast<int>(file_lines.size()); ++i)
        {
            std::string curr_line = file_lines[i];
            Card card;

            std::vector<std::string> parts = split_string(curr_line, ':');
            std::string strnums = parts[1];
            parts.clear();
            parts = split_string(strnums, '|');
            strnums.clear();
            strnums = parts[0];
            std::vector<std::string> wins = split_string(strnums, ' ');
            for (std::string& wn : wins)
            {
                if (0 < wn.size())
                {
                    card.winners.push_back(std::stoi(wn));
                }
            }
            strnums.clear();
            strnums = parts[1];
            std::vector<std::string> owns = split_string(strnums, ' ');
            for (std::string& on : owns)
            {
                if (0 < on.size())
                {
                    int owned = std::stoi(on);
                    card.owneds.push_back(owned);

                    auto it = std::find(card.winners.begin(), card.winners.end(), owned);
                    if (it != card.winners.end())
                    {
                        ++card.matches;
                    }
                }
            }
            card.points = std::pow(2, (card.matches - 1));

            cards.push_back(card);
            inst_counts.push_back(1);
        }

        int result = 0;
        for (auto& c : cards)
        {
            result += c.points;
        }

        std::cout << std::endl;
        std::cout << "1 Result: " << result << std::endl;
        std::cout << std::endl;
//--------------------------------------------------------------------
        for (int i = 0; i < static_cast<int>(cards.size()); ++i)
        {
            Card& curr_card = cards[i];
            int& curr_inst = inst_counts[i];

            for (int k = 0; k < curr_inst; ++k)
            {
                for (int inc_idx = 0; inc_idx < curr_card.matches; ++inc_idx)
                {
                    inst_counts[i + inc_idx + 1] += 1;
                }
            }
        }

        result = 0;
        for (auto& c : inst_counts)
        {
            result += c;
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