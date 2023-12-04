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
// #include <iostream>

std::vector<std::string>    split_string(std::string line, const char *delimeter_symbols)
{
    std::vector<std::string>    array;
    int                         start = 0;
    int                         end = line.find_first_of(delimeter_symbols);

    while (end != std::string::npos)
    {
        if (start < end)
            array.push_back(line.substr(start, end - start));
        start = end + 1;
        end = line.find_first_of(delimeter_symbols, start);
    }
    if (start != line.size())
        array.push_back(line.substr(start, line.size() - start));
    return (array);
}

int calc_power_of_single_game(std::vector<std::string> game)
{
    std::vector<std::string>    array;
    int                         min_red = 0;
    int                         min_green = 0;
    int                         min_blue = 0;
    
    for (size_t j = 1; j < game.size(); j++)
    {
        array = split_string(game[j], " ");
        if (array[1][0] == 'r' && stoi(array[0]) > min_red)
            min_red = stoi(array[0]);
        else if (array[1][0] == 'g' && stoi(array[0]) > min_green)
            min_green = stoi(array[0]);
        else if (array[1][0] == 'b' && stoi(array[0]) > min_blue)
            min_blue = stoi(array[0]);
    }
    std::cout << game[0] << " " << (min_red * min_green * min_blue) << std::endl;
    return (min_red * min_green * min_blue);
}

int calc_total_power(std::vector<std::vector<std::string> > games)
{
    int                         total_power = 0;

    for (size_t i = 0; i < games.size(); i++)
        total_power += calc_power_of_single_game(games[i]);
    return (total_power);
}

int	main(void)
{
    std::ifstream                           file("input.txt");
    std::vector<std::vector<std::string> >  games;
    std::string                             read_line;
    int                                     total_power;

    if (file.is_open())
    {
        while (getline(file, read_line))
            games.push_back(split_string(read_line, ":,;"));
        total_power = calc_total_power(games);
        std::cout << "Total IDs: " << total_power << std::endl;
        file.close();
    } 
    else
        std::cerr << "Unable to open file" << std::endl;
    return (0);
}