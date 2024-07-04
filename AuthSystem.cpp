#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include "ProductApplication.cpp"
#include "StaffApplication.cpp"
#include "DataValidInput.cpp"
#include "User.cpp"
using namespace std;


class AuthSystem {
    ProductManager productManager;
    StaffManager staffmanager;
    DataValidInput dataValidInput;
    //StaffApplication staffApplication;
    //ProductApplication productApplication;
    //DataValidInput dataValidInput;
   
private:
    vector<User> users;
    string usersFile = "users.txt";

public:
    AuthSystem() {
        User user("user", "user123", "User");
        User admin("admin", "admin123", "Admin");
        users.push_back(user);
        users.push_back(admin);
        void app();
        void runAdminMenu();
    }

    bool authenticate(const string& username, const string& password, User& authenticatedUser) {
        for (User user : users)
        {
            if (user.getUsername() == username && user.getPassword() == password) {
                authenticatedUser = user;
                return true;
            }
        }
        return false;
    }

    void login() {
        string username, password;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;

        User authenticatedUser;
        if (authenticate(username, password, authenticatedUser)) {
            cout << "Login successful!" << authenticatedUser.getRole() << endl;
            if (authenticatedUser.getRole() == "Admin") {
                adminMenu();
            } else {
                userMenu();
            }
        } else {
            cout << "\nInvalid username or password." << endl;
        }
    }
       void regis() {
        string username, password, role;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
        cout << "Enter role (Admin/User): ";
        cin >> role;

        users.push_back(User(username, password, role));
        cout << "User added successfully!" << endl;
    }

    void adminMenu() {
        enum MainMenu {EXIT = 3, PRODUCT =1, STAFF =2, USER=0};
        int choice;
        cout.setf(ios::fixed|ios::showpoint);
        cout<<setprecision(2); 

        do{
            displayMain();
            choice = DataValidInput::getIntInput("Enter your choice: ");
            switch(choice){
                    case PRODUCT: {
                    ProductApplication productApplication ;
                    productApplication.run();
                    break;
                }
                case STAFF: {
                    StaffApplication staffApplication ;
                    staffApplication.run();
                    break;
                }
                case USER: {
                    cout<<"User Management"<<endl;
                    break;
                } 
                case EXIT: {
                    cout<<"Back to Main Menu"<<endl;
                    break;
                }
                default : {
                    cout<<"Invalid input"<<endl;
                    cout<<"\a";
                    
                }
            }
        }while(choice!=EXIT);
    }

    void userMenu() {
        int choice;
        do {
            LoginDisplay();
            cout << "Enter choice: ";
            cin >> choice;
            switch (choice) {
            case 1:
                cout << "Viewing user profile..." << endl;
                // Add profile viewing logic here
                break;
            case 2:
                cout << "Logging out..." << endl;
                break;
            default:
                cout << "Invalid choice, please try again." << endl;
            }
        } while (choice != 2);
    }

    void viewUsers() {
        cout << "\nRegistered Users:\n";
        for (const auto& user : users) {
            cout << "Username: " << user.getUsername() << ", Role: " << user.getRole() << endl;
        }
    }

    void menu() {
        int choice;
        do {
            LoginDisplay();
            cout << "Enter choice: ";
            cin >> choice;
            switch (choice) {
            case 1:
                login();
                break;
            default:
                cout << "Exiting the program. Goodbye." << endl;
            } 
        } while (choice != 2);
    }
    
};


