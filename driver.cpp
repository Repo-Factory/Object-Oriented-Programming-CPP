/* Driver Tests Functionality Of Database */

#include <fstream>
#include <iostream>
#include <sstream>
#include "employees.hpp"
using namespace std;

int main()
{   
    /* Capture user input for profits and waiter tips */
    float profits, tips1, tips2, tips3;

    cout << "Hello, Welcome to the Restaurant Database\n";
    cout << "Give us the statistics for the month and we can show you projected employee profits\n\n";
    cout << "Type in the profits for the month: ";
    cin  >> profits;
    cout << "\nLet's record the tips for each waiter\n";
    cout << "Tips for waiter 1: ";
    cin  >> tips1;
    cout << "Tips for waiter 2: ";
    cin  >> tips2;
    cout << "Tips for waiter 3: ";
    cin  >> tips3; 

    /* Construct Object Pointers Based On File Information and Print Database Info */
    Restaurant restaurant(profits);
    restaurant.populateEmployees("employees.txt", tips1, tips2, tips3);
    restaurant.printInfo();  
}

