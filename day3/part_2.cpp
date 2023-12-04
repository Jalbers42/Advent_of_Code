/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part_2.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbers <jalbers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/12/03 23:55:51 by jalbers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <vector>

std::vector<std::string>    get_map(std::string file_name)
{
    std::vector<std::string>    map;
    std::ifstream               file(file_name);
    std::string                 line;
    int                         i;
    
    if (!file.is_open())
        return (map);
    i = 0;
    while (std::getline(file, line))
    {
        map.push_back(line);
        i++;
    }
    return (map); 
}

struct Point {
    int y;
    int x;
};

int is_digit(std::vector<std::string> map, int y, int x)
{
    if (x < 0 || y < 0 || y == map.size() || x == map[y].size())
        return (0);
    if (isdigit(map[y][x]))
        return (1);
    return (0);
}

std::vector<Point> find_adjacent_numbers(std::vector<std::string> map, int y, int x)
{
    std::vector<Point>  numbers;
    
    x -= 1;
    if (is_digit(map, y, x))
        numbers.push_back(Point{y, x});
    y += 1;
    if (is_digit(map, y, x))
        numbers.push_back(Point{y, x});
    x += 1;
    if (is_digit(map, y, x) && !isdigit(map[y][x - 1]))
        numbers.push_back(Point{y, x});
    x += 1;
    if (is_digit(map, y, x) && !isdigit(map[y][x - 1]))
        numbers.push_back(Point{y, x});
    y -= 1;
    if (is_digit(map, y, x))
        numbers.push_back(Point{y, x});
    y -= 1;
    if (is_digit(map, y, x))
        numbers.push_back(Point{y, x});
    x -= 1;
    if (is_digit(map, y, x) && !isdigit(map[y][x + 1]))
        numbers.push_back(Point{y, x});
    x -= 1;
    if (is_digit(map, y, x) && !isdigit(map[y][x + 1]))
        numbers.push_back(Point{y, x});
    return (numbers);
}

long long   calc_number(std::vector<std::string> map, Point point)
{
    int     y = point.y;
    int     x = point.x;
    long    number = 0;

    while (x >= 0 && isdigit(map[y][x - 1]))
        x--;
    while (x < map[y].size() && isdigit(map[y][x]))
    {
        number *= 10;
        number += map[y][x] - '0';
        x++;
    }
    std::cout << number << " ";
    return (number);
}

long long   get_gear(std::vector<std::string> map, int y, int x)
{
    int                  gear = 0;
    std::vector<Point>   numbers;

    numbers = find_adjacent_numbers(map, y, x);
    if (numbers.size() == 2)
    {
        gear = calc_number(map, numbers[0]) * calc_number(map, numbers[1]);
        std::cout << " ____ "; 
    }
    return (gear); 
}

long long get_total_gear_numbers(std::string file_name)
{
    std::vector<std::string>    map;
    long long                      total = 0;
    int                         current_num;
    int                         touchesdigit;

    map = get_map(file_name);
    for (size_t y = 0; y < map.size(); y++)
    {
        std::cout << y + 1 << ": ";
        for (size_t x = 0; x < map[y].size(); x++)
        {
            if (map[y][x] == '*')
                total += get_gear(map, y, x);
        }
        std::cout << std::endl;
    }
    return (total);
}

int	main(void)
{
    std::cout << "Answer: " << get_total_gear_numbers("input.txt") << std::endl;
    return (0);
}