/* 
 * @author Conner Sommerfield
 * Program is designed to provide info for all employees in restaurant database
 * Restaurant has three types of employees - Owner, Chef, and Waiter
 * Program revolves around inheritance with Employee as the base class
 */

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

using namespace std;

class Restaurant;
class Employee;
class Owner;
class Chef;
class Waiter;

typedef vector<shared_ptr<Employee>>    employee_vector_t;
typedef shared_ptr<Employee>            employee_ptr_t;

/* Restaurant stores database that is implemented as a vector of Employee pointers (std::shared_ptr) */
class Restaurant
{
    public:
        Restaurant(float profits);

        inline float getProfits()                               {return this->profits_;}
        void setProfits(float profits)                          {this->profits_ = profits;}

        void addEmployee(employee_ptr_t employee);
        void populateEmployees(string filename, float tips1, float tips2, float tips3);
        void printInfo();
        
    private:
        employee_vector_t database_;
        float profits_;
};

/* Base Class for Employees that Consists of Shared Data Members and Basic Implementations
 * Of Necessary Functions like Salary Calculation and Info Printing
 */
class Employee
{
    public:
        Employee(string name, int ID);
        Employee(Employee& other);
        Employee& operator= (Employee& other);
        virtual ~Employee() {}

        inline string getName()                                 {return this->name_;}
        inline int getID()                                      {return this->ID_;}
        inline string getCategory()                             {return this->category_;}
        inline float getSalary()                                {return this->salary_;}
        inline float getProfitShare()                           {return this->profit_share_;}
        void setName(string name)                               {this->name_ = name;}
        void setID(int ID)                                      {this->ID_ = ID;}
        void setCategory(string category)                       {this->category_ = category;}
        void setSalary(float salary)                            {this->salary_ = salary;}
        void setProfitShare(float profit_share)                 {this->profit_share_ = profit_share;}
        
        virtual float calculateSalary(float profits);
        virtual void printInfo();
        void printSalary(float profits);

    private:
        string name_;
        int ID_;
        string category_;
        float salary_;
        float profit_share_;
};

/* Owner has No Extra Information But Unique Constructor */
class Owner : public Employee
{
    public:
        Owner(string name, int ID);
};

/* Chef has Additional Data Member of Chef's Cuisine Speciality*/
class Chef : public Employee
{
    public:
        Chef(string name, int ID, string speciality="None");

        inline string getSpeciality()                           {return this->cuisine_speciality_;}
        void setSpeciality(string cuisine_speciality)           {this->cuisine_speciality_ = cuisine_speciality;}
        
        virtual void printInfo();
    private:
        string cuisine_speciality_;

};

/* Waiter Has Additional Tips and Years of Service Data Members */
class Waiter : public Employee
{       
    public:
        Waiter(string name, int ID, float tips_earned=0, int service_years=0);

        inline float getYears()                                 {return this->service_years_;}
        void setYears(float service_years)                      {this->service_years_ = service_years;}
        inline float getTips()                                  {return this->tips_earned_;}
        void setTips(float tips_earned)                         {this->tips_earned_ = tips_earned;}

        virtual float calculateSalary(float profits);
        virtual void printInfo();
        void printSalary(float profits);
    private:
        int service_years_;
        float tips_earned_;
};
