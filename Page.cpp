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
    vector<array<char, 100>> page;
    for (int i = 0; i < page.size(); ++i) {
        for (int j = 0; j < 100; ++j) {
            page.at(i)[j] = '_';
        }
    }
}

int Page::size() {
    return page.size();
}

void Page::ResizePage(int rows_to_add) {
    array<char, 100> row;
    fill_n(row, 100, '_');
    for (int i = page.size(); i < rows_to_add; i++) {
        page.push_back(row);
    }
}
void write_to_page()