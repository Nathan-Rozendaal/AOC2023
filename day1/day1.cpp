//
// Created by nathan on 01-12-23.
//
#include "stdio.h"
#include <fstream>
#include <sstream>
#include <vector>

void runpart1() {
    std::ifstream infile("../day1/input.txt");
    std::string line;
    int count = 0;
    char const* digits = "0123456789";
    while (std::getline(infile, line)){
        char num1 = line[line.find_first_of(digits)];
        char num2 = line[line.find_last_of(digits)];
        std::stringstream ss;
        ss << num1 << num2;

        count += std::stoi(ss.str());
    }

    std::cout<<count<<std::endl;
}
void runpart2() {
    std::ifstream infile("../day1/input.txt");
    std::string line;
    int count = 0;
    std::vector<std::string> numbers = {"zero", "one","two","three","four","five","six","seven","eight","nine"};
    char const* digits = "0123456789";
    while (std::getline(infile, line)){
        for (int i = 0; i < 10; ++i) {
            while (line.find(numbers[i]) != std::string::npos) {
                line[line.find(numbers[i]) + 1] = std::to_string(i)[0];
            }
        }
        char num1 = line[line.find_first_of(digits)];
        char num2 = line[line.find_last_of(digits)];
        std::stringstream ss;
        ss << num1 << num2;
        count += std::stoi(ss.str());
    }

    std::cout<<count<<std::endl;
}