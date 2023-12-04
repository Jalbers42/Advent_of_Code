/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part_2.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbers <jalbers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/12/01 17:45:42 by jalbers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
// #include <stdio.h>
#include <string.h>

int get_number(std::string line, int index, int direction)
{
    const char  *number_strings[9] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    int         line_len = line.length();
    int         num_str_len;
    
    if (isdigit(line[index]))
        return (line[index] - '0');
    for (int i = 0; i < 9; i++)
    {
        num_str_len = strlen(number_strings[i]);
        if (direction == -1 && index >= num_str_len -1)
            index -= num_str_len -1;
        if (strncmp(line.c_str() + index, number_strings[i], num_str_len) == 0)
            return (i + 1);
        if (direction == -1)
            index += num_str_len - 1;
    }
    return (-1);
}

int get_first_number(std::string &line)
{
    int length = line.length();
    int number;
    int i = 0;
    
    while (i < length)
    {
        number = get_number(line, i, 1);
        if (number != -1)
        {
            std::cout << number << " ";   
            return (number);
        }
        i++;
    }
    return (0);
}

int get_last_number(std::string &line)
{
    int number;
    int i = line.length() - 1;
    
    while (i >= 0)
    {
        number = get_number(line, i, -1);
        if (number != -1)
        {
            std::cout << number << " ";   
            return (number);
        }
        i--;
    }
    return (0);
}

int get_sum_of_calibration_values(std::string filename)
{
    std::ifstream   me_file;
    std::string     line;
    int             total;
    
    total = 0;
    me_file.open(filename); 
    if (me_file.is_open())
    {
        while (getline(me_file, line, '\n'))
        {
            total += get_first_number(line) * 10;
            total += get_last_number(line);
            std::cout << total << " - " << line << std::endl;
        }
    }
    else
        std::cout << "Error opening file\n";    
    return (total);
}

int	main(void)
{
    int total;

    total = get_sum_of_calibration_values("input.txt");
    std::cout << "Total: " << total << std::endl; 
    return (0);
}