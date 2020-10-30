#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

struct node {

    int    uObj;
    node * uNextDown;
    node * uNextSide;
};

node * CreateNewNode (int);

node * & NextDown (node *);

node * & NextDown (node *);

void DisplayAll (node * pLlStart, node * & (*) (node *));

void SortLinkedList (node *);

#include "linkedList.hxx"
#endif
