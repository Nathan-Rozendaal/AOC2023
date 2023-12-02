//
// Created by nathan on 01-12-23.
//
#include "stdio.h"
#include <fstream>
#include <sstream>
#include <vector>
struct Set{
    int red = 0;
    int green = 0;
    int blue = 0;
};

struct Game{
    int id = 0;
    std::vector<Set> sets;
};

void replaceAll(std::string& str, const std::string& from, const std::string& to) {
    if(from.empty())
        return;
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }
}
void runpart1() {
    std::ifstream infile("../day2/input.txt");
    std::vector<Game> games;
    std::string line;
    int count = 0;
    //parsing
    while (std::getline(infile, line)){
        replaceAll(line,";"," ;");
        replaceAll(line,","," ,");
        std::istringstream stream(line);
        Game game;
        std::string word;
        stream >> word;
        stream >> word;
        word.pop_back();
        game.id = std::stoi(word);

        while (!stream.eof()){
            stream >> word;
            Set set;
            while (word != ";" && !stream.eof()){
                if (word == ",") stream>>word;
                int number = std::stoi(word);
                stream >> word;

                if(word == "red") set.red = number;
                if(word == "green") set.green = number;
                if(word == "blue") set.blue = number;
                stream >> word;
            }
            game.sets.push_back(set);
        }
        games.push_back(game);

    }
    //solution
    for (auto game:games) {
        bool gpossible = true;
        bool rpossible = true;
        bool bpossible = true;
        for (auto set:game.sets) {
            if(set.blue > 14) bpossible = false;
            if(set.green > 13) gpossible = false;
            if(set.red > 12) rpossible = false;
        }
        if(gpossible && rpossible && bpossible) count += game.id;
    }
    std::cout<<count<<std::endl;
}
void runpart2() {
    std::ifstream infile("../day2/input.txt");
    std::vector<Game> games;
    std::string line;
    int count = 0;
    // parsing
    while (std::getline(infile, line)){
        replaceAll(line,";"," ;");
        replaceAll(line,","," ,");
        std::istringstream stream(line);
        Game game;
        std::string word;
        stream >> word;
        stream >> word;
        word.pop_back();
        game.id = std::stoi(word);

        while (!stream.eof()){
            stream >> word;
            Set set;
            while (word != ";" && !stream.eof()){
                if (word == ",") stream>>word;
                int number = std::stoi(word);
                stream >> word;

                if(word == "red") set.red = number;
                if(word == "green") set.green = number;
                if(word == "blue") set.blue = number;
                stream >> word;
            }
            game.sets.push_back(set);
        }
        games.push_back(game);
    }
    //solution
    for (auto game:games) {
        int maxr = 0;
        int maxg = 0;
        int maxb = 0;
        for (auto set:game.sets) {
            if(set.red > maxr) maxr = set.red;
            if(set.green > maxg) maxg = set.green;
            if(set.blue > maxb) maxb = set.blue;
        }
        count += maxr * maxg * maxb;
    }
    std::cout<<count<<std::endl;
}