//
// Created by shaul on 21/03/2022.
//
#include "doctest.h"
#include "Notebook.hpp"
#include "Direction.hpp"

#include <stdexcept>
using namespace std;
using namespace ariel;

const int n33 = 33;
const int n256 = 256;

ariel::Notebook notebook;

TEST_CASE("Simple Page Test") {

    notebook.write(0,0,20,Direction::Horizontal, "rich");
            CHECK(notebook.read(0,0,20,Direction::Horizontal, 4) == "rich");
            CHECK(notebook.read(0,0,20,Direction::Vertical, 1) == "r");
            CHECK(notebook.read(0,0,21,Direction::Vertical, 1) == "i");
            CHECK(notebook.read(0,0,22,Direction::Vertical, 1) == "c");
            CHECK(notebook.read(0,0,23,Direction::Vertical, 1) == "h");


    notebook.write(0,10,10,Direction::Vertical, "abcd");
            CHECK(notebook.read(0,10,10,Direction::Vertical, 4) == "abcd");
            CHECK(notebook.read(0,10,10,Direction::Horizontal, 1) == "a");
            CHECK(notebook.read(0,11,10,Direction::Horizontal, 1) == "b");
            CHECK(notebook.read(0,12,10,Direction::Horizontal, 1) == "c");
            CHECK(notebook.read(0,13,10,Direction::Horizontal, 1) == "d");

    notebook.write(0,50,50,Direction::Horizontal, "abcdefghijklmnopqrstuvwxyz");
        for (int i = 0; i <26 ; ++i) {
            string letter;
            letter += char(97+i);
            CHECK(notebook.read(0,50,50+i,Direction::Horizontal, 1) == letter);
        }

    notebook.write(2,50,50,Direction::Vertical, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");//now we check Vertically
        for (int i = 0; i <26 ; ++i) {
            string letter;
            letter += char(65+i);
            CHECK(notebook.read(2,50+i,50,Direction::Horizontal, 1) == letter);
        }
    //Let's test some large numbers
    for (int i = 0; i <10000 ; ++i) {
        notebook.write(2,700+i,10,Direction::Horizontal, "$");//now we check Vertically
    }
    for (int i = 0; i <10000 ; ++i) {
            CHECK(notebook.read(2,700+i,10,Direction::Horizontal, 1) == "$");
    }
}


TEST_CASE("Test Erasing") {

    notebook.write(1,15,15,Direction::Vertical, "grau");
            CHECK(notebook.read(1,1,1,Direction::Vertical, 4) == "____");
            CHECK(notebook.read(1,14,15,Direction::Vertical, 2) == "_g");
            CHECK(notebook.read(1,14,15,Direction::Vertical, 3) == "_gr");
            CHECK(notebook.read(1,14,15,Direction::Vertical, 4) == "_gra");
            CHECK(notebook.read(1,14,15,Direction::Vertical, 5) == "_grau");
            CHECK(notebook.read(1,14,15,Direction::Vertical, 6) == "_grau_");

    notebook.erase(1,16,15,Direction::Vertical, 7);
            CHECK(notebook.read(1,15,15,Direction::Vertical, 9) == "g~~~~~~~_");
            CHECK(notebook.read(1,14,15,Direction::Vertical, 2) == "_g");
            CHECK(notebook.read(1,14,15,Direction::Vertical, 3) == "_g~");
            CHECK(notebook.read(1,13,15,Direction::Vertical, 5) == "__g~~");
            CHECK(notebook.read(1,16,14,Direction::Horizontal, 3) == "_~_");
            //I now want to test that even though we only wrote 1 letter in row 15 (since we wrote vertically) all row 15 is filled.
    for (int i = 0; i <99 ; ++i) {
        if(i==15){
            CHECK(notebook.read(1,15,i,Direction::Horizontal, 1) == "g");
        }
        else{
            CHECK(notebook.read(1,15,i,Direction::Horizontal, 1) == "_");
        }
    }
}
TEST_CASE ("Bad input - Sentence too long") {
        string sentence;
        for (int i = 0; i <101 ; ++i) {
            sentence+='a';
        }
            CHECK_THROWS(notebook.write(14,0,15,Direction::Vertical, sentence));
            CHECK_THROWS(notebook.write(15,78,15,Direction::Vertical, sentence));//checking that it doesn't matter where we start our sentence from
            CHECK_THROWS(notebook.write(14,0,15,Direction::Horizontal, sentence));
            CHECK_THROWS(notebook.write(15,78,15,Direction::Horizontal, sentence));
            CHECK_THROWS(notebook.read(1,0,15,Direction::Vertical, 100));
            CHECK_THROWS(notebook.read(1,17,0,Direction::Vertical, 1253));
            CHECK_THROWS(notebook.read(1,0,15,Direction::Horizontal, 100));
            CHECK_THROWS(notebook.read(1,17,0,Direction::Horizontal, 125));
            CHECK_THROWS(notebook.erase(1,0,15,Direction::Vertical, 100));
            CHECK_THROWS(notebook.erase(1,17,0,Direction::Vertical, 1253));
            CHECK_THROWS(notebook.erase(1,0,15,Direction::Horizontal, 100));
            CHECK_THROWS(notebook.erase(1,17,0,Direction::Horizontal, 125));
}

TEST_CASE ("Bad input - Sentence in bad location") {
    string sentence = "Dear Diary";
            notebook.write(7,0,15,Direction::Vertical, sentence);
            CHECK_THROWS(notebook.write(7,0,15,Direction::Vertical, sentence));//checking that it doesn't matter where we start our sentence from
            CHECK_THROWS(notebook.write(7,4,14,Direction::Horizontal, sentence));
            CHECK_THROWS(notebook.write(7,7,12,Direction::Horizontal, sentence));
            CHECK_THROWS(notebook.write(7,5,92,Direction::Horizontal, sentence));
            CHECK_THROWS(notebook.write(7,500,99,Direction::Horizontal, sentence));
            CHECK_THROWS(notebook.write(7,0,13,Direction::Horizontal, "abracadbra"));//test writing on writing
            CHECK_THROWS(notebook.write(7,1,15,Direction::Vertical, "abracadbra"));
            CHECK(notebook.read(7,0,15,Direction::Vertical, 10) == "Dear Diary");
            CHECK(notebook.read(7,0,14,Direction::Horizontal, 3) == "_D_");
            CHECK_THROWS(notebook.read(7,0,76,Direction::Horizontal, 30));
            CHECK_THROWS(notebook.read(7,5,40,Direction::Horizontal, 78));
            CHECK_THROWS(notebook.read(7,10,76,Direction::Horizontal, 30));
            CHECK_THROWS(notebook.erase(7,8,40,Direction::Horizontal, 78));
            CHECK_THROWS(notebook.erase(1,17,17,Direction::Horizontal, 90));
}

TEST_CASE ("Bad input - Negative numbers") {
            CHECK_THROWS(notebook.write(7,-1,15,Direction::Vertical, "sentence"));
            CHECK_THROWS(notebook.write(-1,4,14,Direction::Vertical, "sentence"));
            CHECK_THROWS(notebook.write(7,7,-10,Direction::Vertical, "sentence"));
            CHECK_THROWS(notebook.write(7,-1,15,Direction::Horizontal, "sentence"));
            CHECK_THROWS(notebook.write(-1,4,14,Direction::Horizontal, "sentence"));
            CHECK_THROWS(notebook.write(7,7,-10,Direction::Horizontal, "sentence"));
            CHECK_THROWS(notebook.read(-7,0,1,Direction::Horizontal, 30));
            CHECK_THROWS(notebook.read(7,-5,2,Direction::Horizontal, 78));
            CHECK_THROWS(notebook.read(7,10,-2,Direction::Horizontal, 30));
            CHECK_THROWS(notebook.read(7,10,2,Direction::Horizontal, -4));
            CHECK_THROWS(notebook.read(-7,0,1,Direction::Vertical, 7));
            CHECK_THROWS(notebook.read(7,-5,2,Direction::Vertical, 8));
            CHECK_THROWS(notebook.read(7,10,-2,Direction::Vertical, 2));
            CHECK_THROWS(notebook.read(7,10,2,Direction::Vertical, -4));
            CHECK_THROWS(notebook.erase(-7,0,1,Direction::Horizontal, 30));
            CHECK_THROWS(notebook.erase(7,-5,2,Direction::Horizontal, 78));
            CHECK_THROWS(notebook.erase(7,10,-2,Direction::Horizontal, 30));
            CHECK_THROWS(notebook.erase(7,10,2,Direction::Horizontal, -4));
            CHECK_THROWS(notebook.erase(-7,0,1,Direction::Vertical, 7));
            CHECK_THROWS(notebook.erase(7,-5,2,Direction::Vertical, 8));
            CHECK_THROWS(notebook.erase(7,10,-2,Direction::Vertical, 2));
            CHECK_THROWS(notebook.erase(7,10,2,Direction::Vertical, -4));
}
TEST_CASE ("Bad input - Bad Chars") {
            CHECK_THROWS(notebook.write(8,0,15,Direction::Vertical, "~"));
            CHECK_THROWS(notebook.write(8,4,14,Direction::Horizontal, "fasgdas~'f"));
            CHECK_THROWS(notebook.write(8,7,12,Direction::Horizontal, "~~~"));
            CHECK_THROWS(notebook.write(8,7,12,Direction::Horizontal, "abra cadbra~"));
            CHECK_THROWS(notebook.write(9,0,15,Direction::Vertical, "agsa\ndf"));
            CHECK_THROWS(notebook.write(9,4,14,Direction::Horizontal, "ags\r"));
            CHECK_THROWS(notebook.write(9,7,12,Direction::Horizontal, "for\tsg"));
            CHECK_THROWS(notebook.write(9,7,12,Direction::Horizontal, "abra\rsf"));
            //now we check that all the unprintable characters throw exceptions.
    for (int i = 0; i < 32; ++i) {
        string letter;
        letter += char(i);
            CHECK_THROWS(notebook.write(8,7,12,Direction::Vertical, letter));
    }
    for (int i = 126; i <256 ; ++i) {
        string letter;
        letter += char(i);
            CHECK_THROWS(notebook.write(8,14,12,Direction::Horizontal, letter));
    }

}

