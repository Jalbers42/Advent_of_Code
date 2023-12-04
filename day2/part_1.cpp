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

int calc_possible_games(std::vector<std::vector<std::string> > games)
{
    int                         total_ids = 0;
    std::vector<std::string>    array;

    for (size_t i = 0; i < games.size(); i++)
    {
        size_t j;
        for (j = 1; j < games[i].size(); j++)
        {
            array = split_string(games[i][j], " ");
            if (array[1][0] == 'r' && stoi(array[0]) > 12)
                break;
            else if (array[1][0] == 'g' && stoi(array[0]) > 13)
                break;
            else if (array[1][0] == 'b' && stoi(array[0]) > 14)
                break;
        }
        if (j == games[i].size())
        {
            array = split_string(games[i][0], " ");
            total_ids += stoi(array[1]);
        }
    }
    return (total_ids);
}

int	main(void)
{
    std::ifstream                           file("input.txt");
    std::vector<std::vector<std::string> >  games;
    std::string                             read_line;
    int                                     total_ids;

    if (file.is_open())
    {
        while (getline(file, read_line))
            games.push_back(split_string(read_line, ":,;"));
        total_ids = calc_possible_games(games);
        std::cout << "Total IDs: " << total_ids << std::endl;
        file.close();
    } 
    else
        std::cerr << "Unable to open file" << std::endl;
    return (0);
}