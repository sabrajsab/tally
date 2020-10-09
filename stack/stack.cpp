//tested working for int, float, double, char, char *


#include <iostream>
#include "customio.hpp"
#include "stack.hpp"


template <class T>
customStack <T> :: customStack ()
{
    origin =  (T *) malloc (10 * sizeof(T));
    size   =  0;
    top    = -1;
}

template <class T>
int customStack <T> :: push(const T val)
{
    if (top++ == size) {

        size += 10;
        T * newptr = (T *) realloc (origin, size * sizeof (T));
        if (newptr == nullptr) {

            return -1;
        }
        origin = newptr;
    }
    origin [top] = val;
    return 0;
}

template <class T>
int customStack <T> :: pop (void)
{
    if (top == -1) {

        return 1;
    }

    T returnVal = origin[top--];
    if ((size - top) > 12) {

        size -= 10;
        T * newptr = (T *) realloc (origin, size * sizeof (T));
        if (newptr == nullptr) {

            return -1;
        }
        origin = newptr;
    }
    print (returnVal);
    return 0;
}

template <class T>
void customStack <T> :: display ()
{
    for (int i = 0; i <= top; ++i) {

        print (origin [i]);
    }
}

template <class T>
void customStack <T> :: destroy ()
{
    free (origin);
}


template <class T>
void processStack()
{
        int choice {0};
    customStack <T> newStack;
    while (printf("\nChoose :\n1. push      2. pop      3. Display      4. exit\n")) {
        choice = scanPositiveInt();
        if(choice == 1){

            printf("\nEnter value to push :\n");
            T val = scan<T> ();
            newStack.push(val);
        } else if (choice == 2) {

            newStack.pop();
        } else if (choice == 3) {

            newStack.display();
        } else if (choice == 4) {

            newStack.destroy();
            break;
        }
    }
}

template void processStack<int>();
template void processStack<float>();
template void processStack<double>();
template void processStack<char>();
template void processStack<char *>();
