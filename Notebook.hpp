//
// Created by shaul on 20/03/2022.
//
#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include "Direction.hpp"
#include "Page.hpp"

using namespace std;

namespace ariel {
    class Notebook {
        vector<Page> notebook;
    public:
        Notebook();


    void ResizeNotebook(vector<Page> &notebook, unsigned int pages_to_add) ;

    void write(unsigned int page_num, unsigned int row, unsigned int column, Direction d, string to_write);

    string read(unsigned int page_num, unsigned int row, unsigned int column, ariel::Direction d, unsigned int length);

    void erase(unsigned int page_num, unsigned int row, unsigned int column, ariel::Direction d, unsigned int length);

    void show(unsigned int page_num);

    };
}

