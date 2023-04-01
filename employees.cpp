/* 
 * @author Conner Sommerfield
 * Implementation of Class Functions
 * Special Attention to Unique Constructors of Each Derived Class
 * And Specific Implementations of Salary Calculation and Info Printing
 */

#include "employees.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

/*
 * Restaurant must Be Initialized With Profits 
 * for the Month Which Will be Taken into Account
 * For Salary Calculations and Detail Printing
 */
Restaurant::Restaurant(float profits)
{
    this->setProfits(profits);
}

/* Restaurant only has One Entry Point For Adding Elements to The Database */
void Restaurant::addEmployee(employee_ptr_t employee)
{
    this->database_.push_back(employee);
}

/* Pass in File and Info About Tips to Create Employee Objects for Database */
void Restaurant::populateEmployees(string filename, float tips1, float tips2, float tips3)
{
    // Sample Text From File:
    // Chef    Luigi        2  Italian

    // Before our while loop, prep file and create a vector of tips we will loop through for waiters
    fstream file;
    file.open(filename, ios::in);
    std::string line;
    int i = 0;
    vector<float> tips = vector<float>{tips1, tips2, tips3};

    // Scan each line of file and call constructor with data fields as arguments
    while(std::getline(file, line))
    {
        // Prepare to store each entry of line in variable
        string employee_type;
        string name;
        int ID;
        string cuisine_type = "";
        int service_years = 0;

        stringstream line_buffer(line);
        line_buffer >> employee_type >> name >> ID >> cuisine_type >> service_years;

        // Depending on type of employee, create object by calling appropriate constructor
        if(employee_type == "Owner")
        {
            employee_ptr_t owner =  make_shared<Owner>(name, ID);
            this->addEmployee(owner);
        }

        if(employee_type == "Chef")
        {
            employee_ptr_t chef =   make_shared<Chef>(name, ID, cuisine_type);
            this->addEmployee(chef);
        }

        if(employee_type == "Waiter")
        {
            employee_ptr_t waiter = make_shared<Waiter>(name, ID, tips[i], service_years);
            this->addEmployee(waiter);
            i++;
        }
    }
}

/* Call printInfo() and printSalary() Function of All Employees in Database */
void Restaurant::printInfo()
{
    cout << "\nRestaurant Profits For the Month: " << this->getProfits() << endl;
    for (employee_ptr_t& employee : this->database_)
    {
        employee->printInfo();
        employee->printSalary(this->getProfits());
    }
    cout << endl;
}

/* Every Employee Must Have basic Info of Name And ID */
Employee::Employee(string name, int ID)

{
    this->setName           (name);
    this->setID             (ID);
    this->setCategory       ("None");
    this->setSalary         (0);
    this->setProfitShare    (0);
}

/* Specific Employees must Have Specifications on Category, Salary, and Share of Profits */
Owner::Owner(string name, int ID)
: Employee::Employee(name, ID)
{
    this->setCategory       ("O");
    this->setSalary         (15000);
    this->setProfitShare    (.60);
}

/* Chef Must Take Into Account Specific Cuisine Speciality */
Chef::Chef(string name, int ID, string speciality)
: Employee::Employee(name, ID)
{
    this->setCategory       ("C");
    this->setSalary         (10000);
    this->setProfitShare    (.2);
    this->setSpeciality     (speciality);
}

/* Waiter Must Take Into Accounts Tips and Years of Service */
Waiter::Waiter(string name, int ID, float tips_earned, int service_years) 
: Employee::Employee(name, ID)
{
    this->setCategory       ("W");
    this->setSalary         (3000);
    this->setTips           (tips_earned);
    this->setYears          (service_years);
}

/* Print All Mandatory Fields of Any Employee Object */
void Employee::printInfo()
{
    cout << " \n________________________________________\n\n";
    cout << "Name: "            << this->getName()                          << endl; 
    cout << "ID: "              << this->getID()                            << endl;
    cout << "Class: "           << this->getCategory()                      << endl;
    cout << "Base Salary: "     << this->getSalary()                        << endl;
    cout << "Profit Share: "    << this->getProfitShare()*100   << "%"      << endl;
}

void Chef::printInfo()
{
    Employee::printInfo();
    cout << "Cuisine Speciality: "     << this->getSpeciality()             << endl;
}


void Waiter::printInfo()
{
    Employee::printInfo();
    cout << "Years Of Service: "        << this->getYears()                 << endl;
    cout << "Tips Earned: "             << this->getTips()                  << endl;
}

/*
 * Printing Salary Is Apart For Its Reliance On Profits Argument 
 * Plus I Wanted It To Always Come At the End 
 */
void Employee::printSalary(float profits)
{
    cout << "TOTAL SALARY: "    << this->calculateSalary(profits)           << endl;
}

/* 
 * Add Base Salary and Profit Share, 
 * If Profits are Less than Zero, Don't Count Against Employee 
 * Implemented with Max Between 0 and Profits
 */
float Employee::calculateSalary(float profits)
{
    return this->getSalary() + this->getProfitShare() * std::max(profits, 0.0F); 
}

/* Waiter Adds Tips into Total Salary */
float Waiter::calculateSalary(float profits)
{
     return Employee::calculateSalary(profits) + this->getTips();
}
       
