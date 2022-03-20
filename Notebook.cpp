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

void ResizePage(vector<array<char,100>> &page , unsigned int rows_to_add){
    array<char,100> row ;
    fill_n(row,100,'_');
    for (int i = page.size(); i <rows_to_add ; i++) {
        page.push_back(row);
    }
}


Notebook::Notebook() {
    vector<Page> notebook;
    for (int i = 0; i < notebook.size(); ++i) {
        notebook[i] = Page();
    }
};

void Notebook::write(unsigned int page_num, unsigned int row, unsigned int column, ariel::Direction d, string to_write) {
    //first we create a pointer to the page we wish to work on
    if(page_num>notebook.size()){

    }
    if(d==Direction::Horizontal){//we will work 2 cases either writing Horizontal or Vertical

    }
    else{//direction is Vertical

    }
}

string Notebook::read(unsigned int page, unsigned int row, unsigned int column, ariel::Direction d, unsigned int length) {

}

void Notebook::erase(unsigned int page, unsigned int row, unsigned int column, ariel::Direction d, unsigned int length) {

}

void Notebook::show(unsigned int page) {

}

