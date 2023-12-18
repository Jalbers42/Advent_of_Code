/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*                                                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Jalbers42                                         #+#    #+#             */
/*   https://github.com/Jalbers42                     ###   ###########       */
/*                                                                            */
/******************************************************************************/


#include <iostream>
#include <fstream>

struct Data {
    std::vector<int>                seeds;
    std::vector<std::vector<int> >  seed_to_soil_map;
    std::vector<std::vector<int> >  soil_to_fertilizer_map;
    std::vector<std::vector<int> >  fertilizer_to_water_map;
    std::vector<std::vector<int> >  water_to_light_map;
    std::vector<std::vector<int> >  light_to_temperature_map;
    std::vector<std::vector<int> >  temperature_to_humidity_map;
    std::vector<std::vector<int> >  humidity_to_location_map;
};

// struct Map {
//     std:vector<Mapping>
// }
std::vector<int>    str_to_int_vector(std::string &str)
{
    std::vector<int>    vector;
    int                 start;
    int                 end;

    start = 0;
    end = str.find_first_of(' ', start + 1);
    while (end != std::string::npos)
    {
        if (end > start)
            vector.push_back(std::stoi(str.substr(start, end - start)));
        start = end;
        end = str.find_first_of(' ', start + 1);
    }
    if (start < str.size() - 1)
        vector.push_back(std::stoi(str.substr(start, end - start)));
    return (vector);
}

std::vector<int>    get_seeds(std::string &str)
{
    std::vector<int>    seeds;
    int                 start;

    start = str.find_first_of(':') + 2;
    str = str.substr(start, str.size() - start);
    seeds = str_to_int_vector(str);
    return (seeds);
}

std::vector<std::vector<int> >  get_map(std::ifstream &file)
{
    std::vector<std::vector<int> >  map;
    std::string line;

    while (getline(file, line) && !line.empty())
        map.push_back(str_to_int_vector(line));
    return (map);
}

Data    get_data(std::string file_name)
{
    Data            data;
    std::ifstream   file(file_name);
    std::string     line;
    const char      *line_cstr;

    getline(file, line);
    data.seeds = get_seeds(line);
    while (getline(file, line))
    {
        std::cout << line << std::endl;
        line_cstr = line.c_str();
        if (std::strncmp(line_cstr, "seed", 4) == 0)
            data.seed_to_soil_map = get_map(file);
        else if (std::strncmp(line_cstr, "soil", 4) == 0)
            data.soil_to_fertilizer_map = get_map(file);
        else if (std::strncmp(line_cstr, "fertilizer", 10) == 0)
            data.fertilizer_to_water_map = get_map(file);
        else if (std::strncmp(line_cstr, "water", 5) == 0)
            data.water_to_light_map = get_map(file);
        else if (std::strncmp(line_cstr, "light", 5) == 0)
            data.light_to_temperature_map = get_map(file);
        else if (std::strncmp(line_cstr, "temperature", 11) == 0)
            data.temperature_to_humidity_map = get_map(file);
        else if (std::strncmp(line_cstr, "humidity", 8) == 0)
            data.humidity_to_location_map = get_map(file);
    }
    return (data);
}

int find_closest_location(std::string file_name)
{
    Data    data;

    data = get_data(file_name);
    return (0);
}

int	main(void)
{
    int closest_location;

    closest_location = find_closest_location("test_input.txt");
    std::cout << "Closest Location: " << closest_location << std::endl;
    return (0);
}