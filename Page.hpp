//
// Created by shaul on 20/03/2022.
//
#include <iostream>
#include <vector>
#include <array>
#include <stdexcept>
#include <algorithm>
#include "Direction.hpp"

using namespace std;

class Page {
    // Each page consists of a vector of rows. each row is an array of 100 chars.
    vector<array<char,100>> page ;
public:
    Page() {
        for (int i = 0; i <page.size() ; ++i) {
            for (int j = 0; j <100 ; ++j) {
                page.at(i)[j]='_';
            }
        }
    }
};
