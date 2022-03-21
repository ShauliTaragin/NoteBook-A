//
// Created by shaul on 20/03/2022.
//
#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include "Direction.hpp"
#include <unordered_map>

using namespace std;

namespace ariel {
    class Notebook {

    public:
        unordered_map<string , array<char,100>> notebook;


    void write(unsigned int page_num, unsigned int row, unsigned int column, Direction d, string to_write);

    string read(unsigned int page_num, unsigned int row, unsigned int column, ariel::Direction d, unsigned int length);

    void erase(unsigned int page_num, unsigned int row, unsigned int column, ariel::Direction d, unsigned int length);

    void show(unsigned int page_num);

    };
}

