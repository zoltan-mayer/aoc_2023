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
    return (0 == full_string.compare(0, prefix.length(), prefix));
}


static bool ends_with(const std::string& full_string, const std::string& suffix)
{
    std::string lluf(full_string.rbegin(), full_string.rend());
    std::string xiffus(suffix.rbegin(), suffix.rend());

    return starts_with(lluf, xiffus);
}


class Mapper {
    public:
        Mapper(long long rb, long long rt, long long md) : range_bottom{rb}, range_top{rt}, map_delta{md} { }
        long long is_val_in_range(long long val_in) {
            if ((range_bottom <= val_in) && (val_in <= range_top)) {
                return true;
            } else { return false; }
        }
        long long get_mapped_val(long long val_in) {
            if ((range_bottom <= val_in) && (val_in <= range_top)) {
                return (val_in + map_delta);
            } else {
                return val_in;
            }
        }
        long long range_bottom;
        long long range_top;
        long long map_delta;
};


int main()
{
    //std::ifstream file("text_day05_0.txt");
    std::ifstream file("text_day05_1.txt");

    if (file.is_open())
    {
        std::string line;
        std::vector<std::string> file_lines;

        while (std::getline(file, line))
        {
            file_lines.push_back(line);
        }

        std::vector<long long> seeds;
        std::string seedstr = split_string(file_lines[0], ':')[1];

        for (std::string& ss : split_string(seedstr, ' '))
        {
            if (0 < ss.size())
            {
                seeds.push_back(std::stoll(ss));
            }
        }

        int stage_idx = 0;
        std::vector<Mapper> stage_maps;
        std::vector<std::vector<Mapper>> stages;

        for (int i = 2; i < static_cast<int>(file_lines.size()); ++i)
        {
            std::string curr_line = file_lines[i];

            if (0 < curr_line.size())
            {
                if (true == ends_with(curr_line, "map:"))
                {
                    if (0 < stage_idx)
                    {
                        stages.push_back(stage_maps);
                        stage_maps.clear();
                    }
                    ++stage_idx;
                }
                else
                {
                    std::vector<std::string> valss = split_string(curr_line, ' ');
                    long long dst = std::stoll(valss[0]);
                    long long src = std::stoll(valss[1]);
                    long long len = std::stoll(valss[2]);
                    Mapper currmap = Mapper(src, (src + len - 1), (dst - src));
                    stage_maps.push_back(currmap);
                }
            }
        }
        stages.push_back(stage_maps);

        std::vector<long long> locations;
        long long v_in;
        long long v_out;
        for (auto& sd : seeds)
        {
            v_in = sd;
            for (auto& a_stage : stages)
            {
                for (auto& a_map : a_stage)
                {
                    if (true == a_map.is_val_in_range(v_in))
                    {
                        v_out = a_map.get_mapped_val(v_in);
                        break;
                    }
                    else
                    {
                        v_out = v_in;
                    }
                }
                v_in = v_out;
            }
            locations.push_back(v_out);
        }

        int result = 0;
        auto min_loc = std::min_element(locations.begin(), locations.end());

        std::cout << std::endl;
        std::cout << "1 Result: " << *min_loc << std::endl;
        std::cout << std::endl;
//--------------------------------------------------------------------

        result = 0;


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