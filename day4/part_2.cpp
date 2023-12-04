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

struct Card {
    int                 card_num;
    std::vector<int>    winning_numbers;
    std::vector<int>    player_numbers;
    int                 copies;
};

int extract_card_num(std::string str)
{
    int start = str.find_first_of(" ");
    int end = str.find_first_of(":");

    return (std::stoi(str.substr(start, end - start)));
}

std::vector<int>    split_to_int_vector(std::string str, char delimeter)
{
    std::vector<int>    int_vector;
    int                 current_num = 0;
    size_t              i = 0;

    while (i < str.size())
    {
        if (str[i] != delimeter && isdigit(str[i]))
        {
            current_num *= 10;
            current_num += str[i] - '0';
        }
        if ((str[i] == delimeter || i == str.size() - 1) && current_num != 0)
        {
            int_vector.push_back(current_num);
            current_num = 0;
        }
        i++;
    }
    return (int_vector);
}

std::vector<int>    extract_winning_numbers(std::string str)
{
    int start = str.find_first_of(":") + 2;
    int end = str.find_first_of("|") - 1;

    return (split_to_int_vector(str.substr(start, end - start), ' '));
}

std::vector<int>    extract_player_numbers(std::string str)
{
    int start = str.find_first_of("|") + 2;
    int end = str.size();

    return (split_to_int_vector(str.substr(start, end - start), ' '));
}
        
std::vector<Card>   get_cards_vector(std::string file_name)
{
    std::vector<Card>   cards;
    Card                current_card;
    std::ifstream       file(file_name);
    std::string         line;

    if (!file.is_open())
        return (cards);
    while (getline(file, line))
    {
        current_card.card_num = extract_card_num(line);
        current_card.winning_numbers = extract_winning_numbers(line);
        current_card.player_numbers = extract_player_numbers(line);
        current_card.copies = 1;
        cards.push_back(current_card);
    }
    return (cards);
}

int get_copies_won(Card card)
{
    int copies_won = 0;

    for (size_t i = 0; i < card.player_numbers.size(); i++)
    {
        for (size_t j = 0; j < card.winning_numbers.size(); j++)
        {
            if (card.winning_numbers[j] == card.player_numbers[i])
                copies_won++;
        }
    }
    return (copies_won);
}

long long   get_card_points(std::string file_name)
{
    std::vector<Card>   cards;
    int                 copies_won;
    long long           total_copies = 0;
    size_t              i;

    cards = get_cards_vector(file_name);
    for (i = 0; i < cards.size(); i++)
    {
        copies_won = get_copies_won(cards[i]);
        for (int j = 1; j <= copies_won; j++)
            cards[i + j].copies += 1 * cards[i].copies;
    }
    for (i = 0; i < cards.size(); i++)
        total_copies += cards[i].copies;
    return (total_copies);
}

int	main(void)
{
    long long   total_points;

    total_points = get_card_points("input.txt");
    std::cout << "Total: " << total_points << std::endl;
    return (0);
}