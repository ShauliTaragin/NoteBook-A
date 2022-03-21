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


void
Notebook::write(unsigned int page_num, unsigned int row, unsigned int column, ariel::Direction d, string to_write) {
    //we first deal with 3 cases for which we need to throw an exception.
    if (to_write.length() > 99) {
        throw invalid_argument("Your message is too long");
    }
    if (page_num < 0 || row < 0 || column < 0) {
        throw invalid_argument("Please enter only positive parameters");
    }
    //last case is if there is no room to write in that location.
    string what_I_Read = read(page_num, row, column, d,
                              to_write.length());//read will check if the appropriate place is availble
    for (unsigned int i = 0; i < to_write.length(); ++i) {
        if (what_I_Read.at(i) != '_') {
            throw invalid_argument("Can't write your message in this location");
        }
    }
    //If we reached here we know we should be writing the message.
    if (d == Direction::Horizontal) {//we will work 2 cases either writing Horizontal or Vertical
        string key_to_add = to_string(page_num) + "," + to_string(row);

        if (this->notebook.find(key_to_add) == this->notebook.end()) {//if The row does not exist yet
            array<char, 100> row_to_add{};
            for (unsigned int j = 0; j < 100; ++j) {
                row_to_add[j] = '_';
            }
            for (unsigned int j = 0; j < to_write.length(); ++j) {
                row_to_add[column + j] = to_write.at(j);
            }
            this->notebook[key_to_add] = row_to_add;//if this wont work consider first adding array to map and then changing it
        } else {//the row already exits, and we have room to write where we need
            for (unsigned int j = 0; j < to_write.length(); ++j) {
                notebook[key_to_add][column + j] = to_write.at(j);
            }
        }
    } else {//direction is Vertical
        for (int i = 0; i < to_write.length(); ++i) {
            string key_to_add = to_string(page_num) + "," + to_string(row + i);

            if (this->notebook.find(key_to_add) == this->notebook.end()) {//if The row does not exist yet
                //then we create it by adding '_' to all of it and the char in its correct location
                array<char, 100> row_to_add{};
                for (unsigned int j = 0; j < 100; ++j) {
                    row_to_add[j] = '_';
                }
                row_to_add[column] = to_write.at(i);
                this->notebook[key_to_add] = row_to_add;//if this wont work consider first adding array to map and then changing it
            } else {//the row already exits, and we have room to write where we need
                this->notebook[key_to_add][column] = to_write.at(i);
            }
        }
    }
}

string Notebook::read(unsigned int page_num, unsigned int row, unsigned int column, ariel::Direction d, unsigned int length) {
    if (d == Direction::Horizontal) {//we will work 2 cases either writing Horizontal or Vertical
        string key_to_check = to_string(page_num) + "," + to_string(row);
        string what_I_read;
        if(this->notebook.find(key_to_check) == this->notebook.end()){//row is empty!
            for (int i = 0; i <length ; ++i) {
                what_I_read += '_';
            }
        }
        else{//row is not empty
            for (int i = 0; i <length ; ++i) {
                what_I_read += this->notebook[key_to_check][row+i];
            }
        }
        return what_I_read;
    }
    else {//direction is Vertical
        string what_I_read;
        for (int i = 0; i < length; i++) {
            string key_to_check = to_string(page_num) + "," + to_string(row+i);
            if (this->notebook.find(key_to_check) == this->notebook.end()) {//row is empty!
                what_I_read+='_';
            } else {//row is not empty
                what_I_read += this->notebook[key_to_check][column];
            }
        }
        return what_I_read;
    }
}




//Notebook::Notebook() {
//    for (unsigned int i = 0; i < 10; ++i) {
//        this->notebook[i] = Page();//this should call the page constructor and create a page filled with '_' in it.
//    }
//}

//void Notebook::write(unsigned int page_num, unsigned int row, unsigned int column, ariel::Direction d, string to_write) {
//    //First we check if we need to resize the notebook i.e create more pages we do that.
//    if (page_num > this->notebook.size()) {
//        ResizeNotebook(this->notebook, page_num - this->notebook.size());//check here if need to add 1(start from 0)
//    }
//
//    Page page_to_write = this->notebook.at(page_num);
//    if (d == Direction::Horizontal) {//we will work 2 cases either writing Horizontal or Vertical
//
//        //we have 2 things to check. If we have that space in our notebook and if that space has not been written on.
//        if (page_to_write.size() < row) {//first check
//            page_to_write.ResizePage(row - page_to_write.size());
//        }
//
//        string what_I_Read = read(page_num, row, column, d, to_write.length());
//        for (unsigned int i = 0; i < to_write.length(); ++i) {//second check
//            if (what_I_Read.at(i) != '_') {
//                throw invalid_argument("Can't write your message in this location");
//            }
//        }
//
//        for (auto i = column; i < to_write.length(); ++i) {
//            page_to_write.write_to_page(row, column + i, to_write.at(i));
//        }
//    }
//    else {//direction is Vertical
//
//        //we have 2 things to check. If we have that space in our notebook and if that space has not been written on.
//        if (page_to_write.size() < row + to_write.length()) {//first check
//            page_to_write.ResizePage(row + to_write.length() - page_to_write.size());
//        }
//        string what_I_Read = read(page_num, row, column, d, to_write.length());
//        for (unsigned int i = 0; i < to_write.length(); ++i) {//second check
//            if (what_I_Read.at(i) != '_') {
//                throw invalid_argument("Can't write your message in this location");
//            }
//        }
//        for (unsigned int i = 0; i < to_write.length(); ++i) {
//            page_to_write.write_to_page(row + i, column, to_write.at(i));
//        }
//    }
//}

//string Notebook::read(unsigned int page_num, unsigned int row, unsigned int column, ariel::Direction d, unsigned int length) {
//    string word;
//    if (page_num > this->notebook.size()) {
//        ResizeNotebook(this->notebook, page_num - this->notebook.size());//check here if need to add 1(start from 0)
//    }
//    Page page_to_read = this->notebook.at(page_num);
//    if (d == Direction::Horizontal) {//we will work 2 cases either reading Horizontal or Vertical
//
//        //if we want to read from a row that we have yet to initialize, we shall initialize it.
//        if (page_to_read.size() < row) {
//            page_to_read.ResizePage( row + length - page_to_read.size());
//        }
//        //Connect chars to word and return the word.
//        for (auto i = 0; i < length; ++i) {
//            word+= page_to_read.read_from_page(row , column+i);
//        }
//        return word;
//    }
//    else {//direction is Vertical
//
//        //if we want to read from a row that we have yet to initialize, we shall initialize it.
//        if (page_to_read.size() < row+length) {
//            page_to_read.ResizePage(row - page_to_read.size());
//        }
//        //Connect chars to word and return the word.
//        for (auto i = 0; i < length; ++i) {
//            word+= page_to_read.read_from_page(row+i , column);
//        }
//        return word;
//    }
//    return "";
//}

void
Notebook::erase(unsigned int page_num, unsigned int row, unsigned int column, ariel::Direction d,
                unsigned int length) {

}

void Notebook::show(unsigned int page_num) {

}

/**
 * @param notebook -> receiving a reference to the notebook which we are working on.
 * @param pages_to_add -> The amount additional pages we need to add
 */



