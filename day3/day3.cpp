//
// Created by nathan on 03-12-23.
//

#include "stdio.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
struct Coord{
    int x;
    int y;
    Coord(int x,int y): x(x),y(y){}

    Coord(): x(0),y(0){}

    inline bool operator==(const Coord& rhs) {
        if(this->x == rhs.x && this->y == rhs.y){
            return true;
        } else{
            return false;
        }
    }
};

struct PartNumber{
    int value;
    Coord startingCoord;
};

void runpart1() {
    std::ifstream infile("../day3/input.txt");
    std::string line;
    std::vector<Coord> symbolcoords;
    std::vector<PartNumber> partNumbers;
    int linecount = 0;
    int count = 0;
    while (std::getline(infile, line)){
        // get all coordinates of symbols
        for (int i = 0; i < line.length(); ++i) {
            if(!std::isdigit(line[i]) && line[i] != '.'){
                Coord coord(i,linecount);
                symbolcoords.push_back(coord);
            }
        }
        //get all part numbers
        std::string number;
        Coord startingCoord(0,0);
        line.push_back('.');
        for (int i = 0; i < line.length(); ++i) {
            if(std::isdigit(line[i])){
                number.push_back(line[i]);
                if (number.length() == 1){
                    Coord coord(i,linecount);
                    startingCoord = coord;
                }
            }else{
                if (number.length() > 0){
                    PartNumber partNumber;
                    partNumber.startingCoord = startingCoord;
                    partNumber.value = std::stoi(number);
                    partNumbers.push_back(partNumber);
                    number = "";
                }
            }
        }


        linecount++;
    }

    for (auto pn:partNumbers) {
        std::vector<Coord> validSymbolLocs;
        validSymbolLocs.push_back(Coord(pn.startingCoord.x -1,pn.startingCoord.y));
        validSymbolLocs.push_back(Coord(pn.startingCoord.x + std::to_string(pn.value).length(),pn.startingCoord.y));
        int num = std::to_string(pn.value).length() +1;
        for (int i = -1; i < num; ++i) {
            validSymbolLocs.push_back(Coord(pn.startingCoord.x + i,pn.startingCoord.y -1));
            validSymbolLocs.push_back(Coord(pn.startingCoord.x + i,pn.startingCoord.y +1));
        }
        for (auto loc: validSymbolLocs) {
            if(std::find(symbolcoords.begin(), symbolcoords.end(), loc) != symbolcoords.end()) {
                count += pn.value;
            }
        }
    }

    std::cout<<count<<std::endl;
}
void runpart2() {
    std::ifstream infile("../day3/input.txt");
    std::string line;
    std::vector<Coord> symbolcoords;
    std::vector<PartNumber> partNumbers;
    int linecount = 0;
    int count = 0;
    while (std::getline(infile, line)){
        // get all coordinates of symbols
        for (int i = 0; i < line.length(); ++i) {
            if(line[i] == '*'){
                Coord coord(i,linecount);
                symbolcoords.push_back(coord);
            }
        }
        //get all part numbers
        std::string number;
        Coord startingCoord(0,0);
        line.push_back('.');
        for (int i = 0; i < line.length(); ++i) {
            if(std::isdigit(line[i])){
                number.push_back(line[i]);
                if (number.length() == 1){
                    Coord coord(i,linecount);
                    startingCoord = coord;
                }
            }else{
                if (number.length() > 0){
                    PartNumber partNumber;
                    partNumber.startingCoord = startingCoord;
                    partNumber.value = std::stoi(number);
                    partNumbers.push_back(partNumber);
                    number = "";
                }
            }
        }


        linecount++;
    }
    for (auto gearloc:symbolcoords) {
        // loop through pn
        std::vector<PartNumber> adjacentPN;
        for (auto pn:partNumbers) {
            std::vector<Coord> validSymbolLocs;
            validSymbolLocs.push_back(Coord(pn.startingCoord.x -1,pn.startingCoord.y));
            validSymbolLocs.push_back(Coord(pn.startingCoord.x + std::to_string(pn.value).length(),pn.startingCoord.y));
            int num = std::to_string(pn.value).length() +1;
            for (int i = -1; i < num; ++i) {
                validSymbolLocs.push_back(Coord(pn.startingCoord.x + i,pn.startingCoord.y -1));
                validSymbolLocs.push_back(Coord(pn.startingCoord.x + i,pn.startingCoord.y +1));
            }
            for (auto loc: validSymbolLocs) {
                if(loc == gearloc){
                    adjacentPN.push_back(pn);
                }
            }
        }
        if(adjacentPN.size() == 2){
            count += adjacentPN[0].value * adjacentPN[1].value;
        }
    }

    std::cout<<count<<std::endl;
}