//
// Created by shaul on 20/03/2022.
//
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include "Direction.hpp"
#include "Notebook.hpp"
#include <string>

using namespace std;

using namespace ariel;


void
Notebook::write(int page_num, int row, int column, ariel::Direction d, string to_write) {
    //we first deal with 3 cases for which we need to throw an exception.
    if (to_write.length() > 99) {
        throw invalid_argument("Your message is too long");
    }
    if (page_num < 0 || row < 0 || column < 0|| to_write.length() < 0) {
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
        if(static_cast<unsigned long>(column)+ to_write.length()> 100){
            throw invalid_argument("Your message is too long");
        }
        string key_to_add = to_string(page_num) + "," + to_string(row);

        if (this->notebook.find(key_to_add) == this->notebook.end()) {//if The row does not exist yet
            array<char, 100> row_to_add{};
            for (unsigned int j = 0; j < 100; ++j) {
                row_to_add[j] = '_';
            }
            for (unsigned long j = 0; j < to_write.length(); ++j) {
                row_to_add[static_cast<unsigned long>(column)+j] = to_write.at(j);
            }
            this->notebook[key_to_add] = row_to_add;//if this wont work consider first adding array to map and then changing it
        } else {//the row already exits, and we have room to write where we need
            for (unsigned int j = 0; j < to_write.length(); ++j) {
                notebook[key_to_add][static_cast<unsigned long>(column) + j] = to_write.at(j);
            }
        }
    } else {//direction is Vertical
        for (unsigned int i = 0; i < to_write.length(); ++i) {
            string key_to_add = to_string(page_num) + "," + to_string(static_cast<unsigned long>(row) + i);

            if (this->notebook.find(key_to_add) == this->notebook.end()) {//if The row does not exist yet
                //then we create it by adding '_' to all of it and the char in its correct location
                array<char, 100> row_to_add{};
                for (unsigned int j = 0; j < 100; ++j) {
                    row_to_add[j] = '_';
                }
                row_to_add[static_cast<unsigned long>(column)] = to_write.at(i);
                this->notebook[key_to_add] = row_to_add;//if this wont work consider first adding array to map and then changing it
            } else {//the row already exits, and we have room to write where we need
                this->notebook[key_to_add][static_cast<unsigned long>(column)] = to_write.at(i);
            }
        }
    }
}

string Notebook::read(int page_num, int row, int column, ariel::Direction d, int length) {
    if (length > 99) {
        throw invalid_argument("Your message is too long");
    }
    if (page_num < 0 || row < 0 || column < 0 || length < 0) {
        throw invalid_argument("Please enter only positive parameters");
    }
    if (d == Direction::Horizontal) {//we will work 2 cases either writing Horizontal or Vertical
        if(column+length > 100){
            throw invalid_argument("Your message is too long");
        }
        string key_to_check = to_string(page_num) + "," + to_string(row);
        string what_I_read;
        if(this->notebook.find(key_to_check) == this->notebook.end()){//row is empty!
            for (int i = 0; i <length ; ++i) {
                what_I_read += '_';
            }
        }
        else{//row is not empty
            for (unsigned int i = 0; i <length ; ++i) {
                what_I_read += this->notebook[key_to_check][static_cast<unsigned long>(column)+i];
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
                what_I_read += this->notebook[key_to_check][static_cast<unsigned long>(column)];
            }
        }
        return what_I_read;
    }
}


void
Notebook::erase(int page_num, int row, int column, ariel::Direction d,int length) {
    if (length > 99) {
        throw invalid_argument("Your message is too long");
    }
    if (page_num < 0 || row < 0 || column < 0|| length < 0) {
        throw invalid_argument("Please enter only positive parameters");
    }
    if(d== Direction::Horizontal){
        if(column+length > 100){
            throw invalid_argument("Your message is too long");
        }
        string key_to_check = to_string(page_num) + "," + to_string(row);
        int column_iterator =row;
        for (int i = 0; i <length ; ++i) {
            if(column_iterator > 99){ // if we need to move to a new row we do that.
                key_to_check = to_string(page_num) + "," + to_string(row+1);
                column_iterator=0;
            }
            this->notebook[key_to_check][static_cast<unsigned long>(column_iterator)]='~';
        }
    }
    else{
        for (int i = 0; i <length ; ++i) {
            string key_to_check = to_string(page_num) + "," + to_string(row+i);
            this->notebook[key_to_check][static_cast<unsigned long>(column)]= '~';
        }
    }

}

void Notebook::show(int page_num) {

}

/**
 * @param notebook -> receiving a reference to the notebook which we are working on.
 * @param pages_to_add -> The amount additional pages we need to add
 */



