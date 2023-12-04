/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   day1.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbers <jalbers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/12/01 16:53:16 by jalbers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>

int get_first_number(std::string &line)
{
    int length = line.length();
    int i = 0;
    
    while (i < length)
    {
        if (isdigit(line[i]))
        {
            std::cout << line[i] << " ";   
            return (line[i] - '0');  
        }
        i++;
    }
    return (0);
}

int get_last_number(std::string &line)
{
    int i = line.length() - 1;
    
    while (i >= 0)
    {
        if (isdigit(line[i]))
        {
            std::cout << line[i] << " ";   
            return (line[i] - '0');  
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