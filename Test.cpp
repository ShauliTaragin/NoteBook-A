//
// Created by shaul on 21/03/2022.
//
#include "doctest.h"
#include "Notebook.hpp"
#include "Direction.hpp"

#include <iostream>
#include <stdexcept>
using namespace std;
using namespace ariel;

ariel::Notebook notebook;

TEST_CASE("simple page test") {

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

}


//TEST_CASE("test empty line") {
//
//    notebook.write(15,15,Direction::Vertical, "abcd");
//            CHECK(notebook.read(1,1,Direction::Vertical, 4) == "____");
//            CHECK(notebook.read(14,15,Direction::Vertical, 2) == "_a");
//            CHECK(notebook.read(14,15,Direction::Vertical, 3) == "_ab");
//            CHECK(notebook.read(14,15,Direction::Vertical, 4) == "_abc");
//            CHECK(notebook.read(14,15,Direction::Vertical, 5) == "_abcd");
//            CHECK(notebook.read(14,15,Direction::Vertical, 6) == "_abcd_");
//
//}

