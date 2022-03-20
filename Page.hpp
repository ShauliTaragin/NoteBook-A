//
// Created by shaul on 20/03/2022.
//
#pragma once
#include <iostream>
#include <vector>
#include <array>
#include <stdexcept>
#include <algorithm>
#include "Direction.hpp"

using namespace std;

class Page {
    // Each page consists of a vector of rows. each row is an array of 100 chars.
    vector<array<char, 100>> page;
public:
    Page();

    unsigned int size();

    void ResizePage(unsigned int rows_to_add);

    void write_to_page(unsigned int row , unsigned int column , char char_to_write);

    char read_from_page(unsigned int row , unsigned int column);
};
