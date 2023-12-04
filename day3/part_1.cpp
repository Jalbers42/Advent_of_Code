/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part_1.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbers <jalbers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/12/03 22:39:29 by jalbers          ###   ########.fr       */
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
        // std::cout << map[i] << std::endl;
        i++;
    }
    return (map); 
}

int is_symbol(std::vector<std::string> map, int y, int x)
{
    if (x < 0 || y < 0 || y == map.size() || x == map[y].size())
        return (0);
    if (map[y][x] != '.' && !isdigit(map[y][x]))
        return (1); 
    return (0);
}

int check_for_adjacent_symbol(std::vector<std::string> map, int y, int x)
{
    x -= 1;
    if (is_symbol(map, y, x))
        return (1);
    y += 1;
    if (is_symbol(map, y, x))
        return (1);
    x += 1;
    if (is_symbol(map, y, x))
        return (1);
    x += 1;
    if (is_symbol(map, y, x))
        return (1);
    y -= 1;
    if (is_symbol(map, y, x))
        return (1);
    y -= 1;
    if (is_symbol(map, y, x))
        return (1);
    x -= 1;
    if (is_symbol(map, y, x))
        return (1);
    x -= 1;
    if (is_symbol(map, y, x))
        return (1); 
    return (0);
}

long long get_total_part_numbers(std::string file_name)
{
    std::vector<std::string>    map;
    long long                      total = 0;
    int                         current_num;
    int                         touches_symbol;

    map = get_map(file_name);
    for (size_t y = 0; y < map.size(); y++)
    {
        std::cout << y + 1 << ": ";
        touches_symbol = 0;
        current_num = 0;
        for (size_t x = 0; x < map[y].size(); x++)
        {
            if (isdigit(map[y][x]))
            {
                current_num *= 10;
                current_num += map[y][x] - '0';
                if (touches_symbol == 0 && check_for_adjacent_symbol(map, y,  x) == 1)
                    touches_symbol = 1;
            }
            else
            {
                if (touches_symbol == 1)
                {
                    total += current_num;
                    std::cout << current_num << " ";
                    touches_symbol = 0;
                }
                current_num = 0;
            }
        }
            if (touches_symbol == 1)
            {
                total += current_num;
                std::cout << current_num << " ";
                touches_symbol = 0;
            }
        std::cout << std::endl;
    }
    return (total);
}

int	main(void)
{
    std::cout << "Answer: " << get_total_part_numbers("input.txt") << std::endl;
    return (0);
}