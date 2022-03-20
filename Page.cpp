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

    class Page {
        //each row is an array of 100 chars. A page consists of a vector of rows.
        vector<array<char,100>> page ;

    public:
        Page() {
            fill(page.begin(), page.end(), '_');
        }


        string to_string() {           // inline method
            return std::to_string(re) + "+" + std::to_string(im) + "i";
        }

    };


