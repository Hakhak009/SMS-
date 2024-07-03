#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stdexcept>

class Staff{
protected:
    std::string name;
    int id;
    std::string phone;
public:
    Staff(){}
    Staff(int id,std::string phone,std::string name) :id(id),name(name),phone(phone){}
    //getter
    int getId(){
        return id;
    }
    std::string getPhone(){
        return phone;
    }
    std::string getName(){
        return name;
    }
    //setter
    void setId(int id){
        this->id=id;
    }
    void setPhone(std::string phone){
        this->phone=phone;
    }
    void setName(std::string name){
        this->name=name;
    }
    virtual std::string getType() const = 0;

 virtual void displayname() const {
        
        std::cout << std::left << std::setw(20) << getType()
                  << std::setw(20) << id
                  << std::setw(15) << name
                  << std::setw(15) << phone << std::endl;
    }

    virtual ~Staff() = default;

};
