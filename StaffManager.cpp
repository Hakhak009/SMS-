#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stdexcept>
#include "Staff.cpp"
#include "DataValidInput.cpp"
#include "StaffRepository.cpp"
#include "FullTimeStaff.cpp"
#include "PartTimeStaff.cpp"
#include "display.cpp"

class StaffManager : public StaffRepository{
private:
    std::vector<Staff*> staffs;

    Staff* findstaffbyID(int id){
        auto it = std::find_if(staffs.begin(),staffs.end(),[id](Staff* staffs){
            return staffs->getId() == id;
        });
        return (it != staffs.end()) ? *it : nullptr;
    }
public:
    ~StaffManager(){
        for(auto staff : staffs){
            delete staff;
        }
    }
    void addStaff(int id,std::string name,int type,std::string phone){
        if(type==1){
                staffs.push_back(new FullTimeStaff(name,id,phone));
        } else if (type==2){
                staffs.push_back(new PartTimeStaff(name,id,phone));
        } else{
            throw std::invalid_argument("Invalide Staff Type.");
        }
        std::cout << "Staff added successfully.\n";
    }
    void updateStaff(int id){
        Staff* staff = findstaffbyID(id);
        if(staff == nullptr){
            throw std::invalid_argument("staff not found");
            return;
        }
        std::string newPhone;
        newPhone = DataValidInput::getPhoneInput("Enter staff number: ");
        staff->setPhone(newPhone);

        std::string newName;
        newName = DataValidInput::getStringInput("Enter Staff Name: ");
        staff->setName(newName);
        std::cout <<"Staff update successfully.\n";
    }
    void deleteStaff(int id){
        if (!confirmation()) {return;} 
        auto it = std::remove_if(staffs.begin(),staffs.end(),[id](Staff* staff){
            if (staff->getId() == id){
                delete staff;
                return true;
            }
            return false;
        });
        if(it != staffs.end()){
            staffs.erase(it,staffs.end());
            std::cout <<"Staff delete successfully.\n";
        } else {
            throw std::invalid_argument("Staff not found");
        }
    }
    void viewStaff(){
        if (staffs.empty()){
            throw std::invalid_argument("No staff available");
            return;
        }
        displayStaff();
        for(const auto& staff : staffs){
            staff->displayname();
        }
    }

    bool confirmation() {
        string confirm;
        while (true)
        {
            cout <<"Are you Sure? <yes/no>: ";
            std::getline(std::cin, confirm);
            if (confirm =="no" || confirm == "n")
            {
                return false;
            }
            else if (confirm == "yes" || confirm == "y")
            {
                return true;
            }
            else
            {
                cout << "Invalid input. Please enter 'yes' or 'no'.\n";
            }
        }
    }
};
