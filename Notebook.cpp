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

using namespace ariel;

Notebook::Notebook() {
    for (int i = 0; i < notebook.size(); ++i) {
        notebook[i] = Page();
    }
};

void write(unsigned int page, unsigned int row, unsigned int column, ariel::Direction d, string to_write) {
    //first we create a pointer to the page we wish to work on
}

string read(unsigned int page, unsigned int row, unsigned int column, ariel::Direction d, unsigned int length) {

}

void erase(unsigned int page, unsigned int row, unsigned int column, ariel::Direction d, unsigned int length) {

}

void show(unsigned int page) {

}

