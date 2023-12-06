//
// Created by nathan on 01-12-23.
//
#include "stdio.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <limits>

struct range{
    uint64_t start;
    uint64_t length;
    std::pair<uint64_t,uint64_t> getLowerUpperBound() const{
        std::pair<uint64_t,uint64_t> result;
        result.first = start;
        result.second = start + length;
        return result;
    }
    uint64_t getEnd() const{
        return start + length -1;
    }

    bool isSplittableAt(uint64_t index) const{
        if(index > start && index <= getEnd()){
            return true;
        }
        return false;
    }
    range splitAt(uint64_t startIndex){
        uint64_t newLength = startIndex - start;
        range newRange;
        newRange.start = startIndex;
        newRange.length = length - newLength;
        length = newLength;

        return newRange;
    }

    uint64_t getIntersectingIndex(range input) const{
        if(isSplittableAt(input.start)){
            return input.start;
        }
        if(isSplittableAt(input.getEnd() +1)){
            return input.getEnd() +1;
        }
        return std::numeric_limits<uint64_t>::max();
    }

};
struct mapping{
    range sourceRange;
    uint64_t destinationOffset;
    uint64_t mapValue(uint64_t input) const{
        uint64_t result = input;
        std::pair<uint64_t,uint64_t> bounds = sourceRange.getLowerUpperBound();
        if(input >= bounds.first && input < bounds.second){
            result = input + destinationOffset - sourceRange.start;
        }
        return result;

    }
    uint64_t getSplitIndex(range input) const {
        return input.getIntersectingIndex(sourceRange);
    }
};
struct map{
    std::vector<mapping> mappings;

    uint64_t mapValue(uint64_t input){
        for (auto mapping:mappings) {
            uint64_t result = mapping.mapValue(input);
            if(result != input){
                return result;
            }
        }
        return input;
    }
    uint64_t getSplitIndex(range input){
        for (auto mapping:mappings) {
            uint64_t result = mapping.getSplitIndex(input);
            if(result != std::numeric_limits<uint64_t>::max()){
                return result;
            }
        }
        return std::numeric_limits<uint64_t>::max();
    }
};
void runpart1() {
    std::vector<map> maps;
    std::vector<uint64_t> seeds;
    std::ifstream infile("../day5/input.txt");
    std::string line;
    uint64_t result = 0;
    // parsing
    std::getline(infile, line);
    std::istringstream stream(line);
    std::string throwaway;
    stream >> throwaway; // throw away first word
    // parse seeds
    while (!stream.eof()){
        uint64_t value;
        stream >> value;
        seeds.push_back(value);
    }

    while (std::getline(infile, line)){
        if(line==""){
            getline(infile,line);
            map newmap;
            maps.push_back(newmap);
            continue;
        }
        uint64_t v1,v2,v3;
        std::istringstream numbers(line);
        numbers >> v1 >> v2 >> v3;
        mapping newMapping;
        range sourceRange;
        newMapping.destinationOffset = v1;
        sourceRange.start = v2;
        sourceRange.length = v3;
        newMapping.sourceRange = sourceRange;
        maps.back().mappings.push_back(newMapping);

    }

    for (auto map: maps) {
        for (unsigned long & seed : seeds) {
            seed = map.mapValue(seed);
        }
    }
    result = *std::min_element(seeds.begin(),seeds.end());
    std::cout<<result<<std::endl;
}
void runpart2() {
    std::vector<map> maps;
    std::ifstream infile("../day5/input.txt");
    std::string line;
    uint64_t result = 0;
    // parsing
    std::getline(infile, line);
    std::istringstream stream(line);
    std::string throwaway;
    stream >> throwaway; // throw away first word
    std::vector<range> seedRanges;
    // parse seeds
    while (!stream.eof()){
        range newRange;
        uint64_t v1,v2;
        stream >> v1;
        stream >> v2;
        newRange.start = v1;
        newRange.length = v2;
        seedRanges.push_back(newRange);
    }

    while (std::getline(infile, line)){
        if(line.empty()){
            getline(infile,line);
            map newmap;
            maps.push_back(newmap);
            continue;
        }
        uint64_t v1,v2,v3;
        std::istringstream numbers(line);
        numbers >> v1 >> v2 >> v3;
        mapping newMapping;
        range sourceRange;
        newMapping.destinationOffset = v1;
        sourceRange.start = v2;
        sourceRange.length = v3;
        newMapping.sourceRange = sourceRange;
        maps.back().mappings.push_back(newMapping);

    }
    std::vector<range> splitQueue;
    splitQueue = seedRanges;
    std::vector<range> processlist;
    uint64_t currentMin = std::numeric_limits<uint64_t>::max();
    for (auto map: maps) {
        //split
        processlist.clear();
        while (!splitQueue.empty()){
            uint64_t imax = std::numeric_limits<uint64_t>::max();
            uint64_t splitIndex = map.getSplitIndex(splitQueue.back());
            if(splitIndex != imax){
                splitQueue.push_back(splitQueue.back().splitAt(splitIndex));
            }else{
                processlist.push_back(splitQueue.back());
                splitQueue.pop_back();
            }
        }
        //map
        for (auto &range:processlist) {
            range.start = map.mapValue(range.start);

            if(range.start < currentMin){
                currentMin = range.start;
            }
        }
        std::cout << "this map min = " << currentMin << std::endl;
        currentMin = std::numeric_limits<uint64_t>::max();
        splitQueue = processlist;
    }
}