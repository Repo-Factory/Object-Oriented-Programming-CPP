/* Driver Tests Functionality Of Database */

#include <fstream>
#include <iostream>
#include "employees.hpp"

using namespace std;

#define PROFITS 5000

int main()
{   
    /* Construct Object Pointers Based On File Information */
    Restaurant restaurant                           (PROFITS);
    employee_ptr_t owner   =    make_shared<Owner>  ("Dale",      1           );
    employee_ptr_t chef1   =    make_shared<Chef>   ("Luigi",     2, "Italian");
    employee_ptr_t chef2   =    make_shared<Chef>   ("Francisco", 3, "Spanish");
    employee_ptr_t waiter1 =    make_shared<Waiter> ("Jeremiah",  4, 150, 3   );
    employee_ptr_t waiter2 =    make_shared<Waiter> ("Bradley",   5, 240, 4   );
    employee_ptr_t waiter3 =    make_shared<Waiter> ("Cheryll",   6, 300, 5   );

    /* Add Employees to Database */
    restaurant.addEmployee(owner);
    restaurant.addEmployee(chef1);
    restaurant.addEmployee(chef2);
    restaurant.addEmployee(waiter1);
    restaurant.addEmployee(waiter2);
    restaurant.addEmployee(waiter3);

    /* Print Data For Each Employee */
    restaurant.printInfo();  
}
