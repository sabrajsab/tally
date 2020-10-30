#ifndef IMPORTLL_HPP
#define IMPORTLL_HPP
#include "linkedList.hpp"

int rows = 4;                                             
                                                           
int arr_size[] = {4, 3, 4, 2};                              
                                                           
int arr [][4] =    {{1, 6, 99, 101},
                {20, 22, 60},
                {40, 41, 46, 80},
                {50, 100}};

node * llstart = nullptr;
node * llsidestart = nullptr;
bool flag = false;
node * llcurrent = nullptr;
node * ptr = nullptr;

void CreateLinkedList()
{
    for (int i = 0; i < rows; ++i) {

        for (int j = 0; j < arr_size [i]; ++j) {

            ptr = CreateNewNode(arr [i][j]);
            if (!llstart) {

                llstart     = ptr;
                llcurrent   = ptr;
                llsidestart = ptr;
                continue;
            }
            if (!flag) {

                llsidestart -> uNextSide = ptr;
                llsidestart = llsidestart->uNextSide;
                llcurrent = llsidestart;
                flag = true;
                continue;
            }
        llcurrent->uNextDown = ptr;
        llcurrent = llcurrent -> uNextDown;
        }

        flag = false;
    }
}

#endif
