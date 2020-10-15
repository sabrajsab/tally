#include <iostream>
#include "string.hpp"
#include "customio.hpp"
#include "principal.hpp"
#include "teacher.hpp"
#include "developer.hpp"
#include "linkedList.hpp"

int main ()
{        
        Person *   person_pointer          = nullptr;
        Person *   Dummy                   = new Person;
        node   *   LlStart                 = CreateNewNode(Dummy);
        node   * & (*next_fun)               (node *);
        bool       (* compare_function_ptr)  (Person *, Person *);
        int        choice {0};

    while (printf("\nChoose :\n1. insert      2. Display      3. exit\n")) {

        choice = scan<int> ();
        if (choice == 1) {

            while (printf("\n1. Principal     2. Teacher     3. Employee:\n")) {

                choice = scan<int> ();
                if (choice == 1) {

                    person_pointer = new Principal;
                    next_fun = &NextPrincipal;
                    break;
                } else if (choice == 2) {
                    
                    person_pointer = new Teacher;
                    next_fun = &NextTeacher;
                    break;
                } else if (choice == 3) {

                    person_pointer = new Developer;
                    next_fun = &NextDeveloper;
                    break;
                } else {

                    printf ("Invalid choice");
                }
            }

            person_pointer -> TakeInput ();
            node * newNode = CreateNewNode (person_pointer);
            Push (LlStart, newNode, next_fun);
        } else if (choice == 2) {

            DisplayAll (LlStart, &NextPerson);
            while (printf ("\nSelect professoin\n1. Principal     2. Teacher     3. Employee:\n")) {

                choice = scan <int> ();
                if (choice == 1) {

                    next_fun = &NextPrincipal;
                    break;
                } else if (choice == 2) {
                    
                    next_fun = &NextTeacher;
                    break;
                } else if (choice == 3) {

                    next_fun = &NextDeveloper;
                    break;
                } else {

                    printf ("Invalid choice");
                }
            }

            while (printf ("\nSort by:\n1. Name    2. Age    3. Salary\n")) {
                choice = scan <int> ();
                if (choice == 1) {

                    compare_function_ptr = &CompareName;
                    break;
                } else if (choice == 2) {
                        
                    compare_function_ptr = &CompareAge;
                    break;
                } else if (choice == 3) {

                    compare_function_ptr = &CompareSalary;
                    break;
                } else {

                    printf ("Invalid choice");
                }
            }

            BubbleSort (LlStart, next_fun, compare_function_ptr);
            DisplayAll (LlStart, next_fun);

        } else if (choice == 3) {

            break;
        }
    }

    system ("pause");
    return 0;
}

