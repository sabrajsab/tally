#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include "person.hpp"

struct node {

    Person * uObj;
    node   * uNext;
    node   * uNextPrincipal;
    node   * uNextTeacher;
    node   * uNextDeveloper;
};

node * CreateNewNode (Person *);

node * & NextPerson (node *);

node * & NextTeacher (node *);

node * & NextDeveloper (node *);

void DisplayAll (node * pLlStart, node * & (*) (node *));

void Push (node * & pLlStart, node * & pNewNode, node * & (*pFunPtr) (node *));

void BubbleSort (node * pPtr, node * & (*pFunPtr) (node *), bool (* CompareFunptr) (Person *, Person *));

#include "linkedList.hxx"
#endif
