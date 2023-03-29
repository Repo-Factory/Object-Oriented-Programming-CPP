#include "employees.hpp"
#include <iostream>

Restaurant::Restaurant(float profits)
{
    this->setProfits(profits);
}

void Restaurant::addEmployee(employee_ptr_t employee)
{
    this->database_.push_back(employee);
}

void Restaurant::printInfo()
{
    cout << "\nRestaurant Profits For the Month: " << this->getProfits() << endl;

    for (employee_ptr_t& employee : this->database_)
    {
        employee->printInfo(this->getProfits());
    }

    cout << endl;
}

Employee::Employee(string name, int ID)

{
    this->setName(name);
    this->setID(ID);
}

void Employee::printInfo(float profits)
{
    cout << " \n________________________________________\n\n";
    cout << "Name: "            << this->getName()                          << endl; 
    cout << "ID: "              << this->getID()                            << endl;
    cout << "Class: "           << this->getCategory()                      << endl;
    cout << "Base Salary: "     << this->getSalary()                        << endl;
    cout << "Profit Share: "    << this->getProfitShare()*100   << "%"      << endl;
    cout << "Total Salary: "    << this->calculateSalary(profits)           << endl;
}

Owner::Owner(string name, int ID)
: Employee::Employee(name, ID)
{
    this->setCategory("O");
    this->setSalary(15000);
    this->setProfitShare(.60);
}

Chef::Chef(string name, int ID, string speciality)
: Employee::Employee(name, ID)
{
    this->setCategory("C");
    this->setSalary(10000);
    this->setProfitShare(.2);
    this->setSpeciality(speciality);
}

void Chef::printInfo(float profits)
{
    Employee::printInfo(profits);
    cout << "Cuisine Speciality: "     << this->getSpeciality()             << endl;
}

Waiter::Waiter(string name, int ID, float tips_earned, int service_years) 
: Employee::Employee(name, ID)
{
    this->setCategory("W");
    this->setSalary(3000);
    this->setProfitShare(0);
    this->setTips(tips_earned);
    this->setYears(service_years);
}

void Waiter::printInfo(float profits)
{
    Employee::printInfo(profits);
    cout << "Years Of Service: "        << this->getYears()                 << endl;
    cout << "Tips Earned: "             << this->getTips()                  << endl;
}


float Employee::calculateSalary(float profits)
{
    return this->getSalary() + this->getProfitShare() * profits; 
}

float Waiter::calculateSalary(float profits)
{
     return Employee::calculateSalary(profits) + this->getTips();
}
       
