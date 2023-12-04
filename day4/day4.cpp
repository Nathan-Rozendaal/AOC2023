//
// Created by nathan on 01-12-23.
//
#include "stdio.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <algorithm>

struct card{
    std::set<int> winningNumbers;
    std::set<int> gotNumbers;
    int copies = 1;
};
void runpart1() {
    std::ifstream infile("../day4/input.txt");
    std::string line;
    int result = 0;
    std::vector<card> cards;
    // parsing
    while (std::getline(infile, line)){
        card currentCard;
        std::istringstream stream(line);
        std::string input;
        std::getline(stream, input,':');
        std::getline(stream, input,'|');
        std::istringstream winningNumbers(input);
        while (!winningNumbers.eof()){
            int number;
            winningNumbers >> number;
            currentCard.winningNumbers.insert(number);
        }
        while (!stream.eof()){
            int number;
            stream >> number;
            currentCard.gotNumbers.insert(number);
        }
        cards.push_back(currentCard);

    }
    for (const auto& card:cards) {
        std::vector<int> v_intersection;
        std::set_intersection(card.winningNumbers.begin(), card.winningNumbers.end(),
                              card.gotNumbers.begin(), card.gotNumbers.end(),
                              std::back_inserter(v_intersection));
        if(!v_intersection.empty()){
            int value = 1;
            int iterations = v_intersection.size() -1;
            for (int i = 0; i < iterations; ++i) {
                value = value << 1;
            }
            result += value;
        }
    }

    std::cout<<result<<std::endl;
}
void runpart2() {
    std::ifstream infile("../day4/input.txt");
    std::string line;
    int result = 0;
    std::vector<card> cards;
    // parsing
    while (std::getline(infile, line)){
        card currentCard;
        std::istringstream stream(line);
        std::string input;
        std::getline(stream, input,':');
        std::getline(stream, input,'|');
        std::istringstream winningNumbers(input);
        while (!winningNumbers.eof()){
            int number;
            winningNumbers >> number;
            currentCard.winningNumbers.insert(number);
        }
        while (!stream.eof()){
            int number;
            stream >> number;
            currentCard.gotNumbers.insert(number);
        }
        cards.push_back(currentCard);

    }
    result = cards.size();
    std::reverse(cards.begin(), cards.end());
    while (!cards.empty()){
        card current = cards.back();

        for (int i = 0; i < current.copies; ++i) {
            std::vector<int> v_intersection;
            std::set_intersection(current.winningNumbers.begin(), current.winningNumbers.end(),
                                  current.gotNumbers.begin(), current.gotNumbers.end(),
                                  std::back_inserter(v_intersection));

            int nextCardIndex = cards.size() -2;
            int lastCardIndex= nextCardIndex - v_intersection.size();
            for (int j = nextCardIndex; j > lastCardIndex; --j) {
                cards[j].copies ++;
                result ++;
            }
        }
        cards.pop_back();
    }

    std::cout<<result<<std::endl;
}