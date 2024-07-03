#pragma once
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <stdexcept>
#include "Staff.cpp"

class PartTimeStaff : public Staff {
    public:
        // Constructor that takes in a name, id, and phone number
        PartTimeStaff(const std::string& name, int id,std::string phone){
            // Set the name, id, and phone of the PartTimeStaff object
            this->name=name;
            this->id=id;
            this->phone=phone;
        }
        // Override the getType method to return "Part Time Staff"
        std::string getType() const override{
            return "Part Time Staff";
        }
};