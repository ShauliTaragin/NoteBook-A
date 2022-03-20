//
// Created by shaul on 20/03/2022.
//
#include <iostream>
#include <vector>
#include <array>
#include <stdexcept>
#include <algorithm>
#include "Direction.hpp"
#include "Page.hpp"

using namespace std;

Page::Page() {
    // Each page consists of a vector of rows. each row is an array of 100 chars.
    for (int i = 0; i < this->page.size(); ++i) {
        for (int j = 0; j < 100; ++j) {
            this->page.at(i)[j] = '_';
        }
    }
}

int Page::size() {
    return this->page.size();
}

void Page::ResizePage(int rows_to_add) {
    array<char, 100> row;
    fill_n(row, 100, '_');
    int size = this->page.size();
    for (int i = size; i < rows_to_add; i++) {
        this->page.push_back(row);
    }
}
void Page::write_to_page(unsigned int row , unsigned int column , char char_to_write){
    this->page[column][row] = char_to_write;
}
char Page::read_from_page(unsigned int row , unsigned int column){
    return this->page[column][row];
}