//
// Created by shaul on 20/03/2022.
//
#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include "Direction.hpp"
#include "Page.hpp"
#include "Notebook.hpp"

using namespace std;

namespace ariel {
    class Notebook {
        double re, im;

    public:
        Notebook() { re = im = 999; }    // inline constructor
        Notebook(double re, double im);  // "outline" constructor

        string to_string() {           // inline method
            return std::to_string(re) + "+" + std::to_string(im) + "i";
        }

    };

    void write(unsigned int page, unsigned int row, unsigned int column, ariel::Direction d, string to_write) {

    }

    string read(unsigned int page, unsigned int row, unsigned int column, ariel::Direction d, unsigned int length) {

    }
    void erase(unsigned int page, unsigned int row, unsigned int column, ariel::Direction d, unsigned int length) {

    }
    void show(unsigned int page) {

    }

}
