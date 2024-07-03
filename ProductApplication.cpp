#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stdexcept>
#include "ProductManager.cpp"
#include "DataValidInput.cpp"
#include "Product.cpp"

class ProductApplication {
private:
    // Declare private attributes
    ProductManager manager;
public:
    // Declare public methods
    void run(){

        int choice;
        bool done = false;
        do {
            // Display the product management options
         displayProductManagement();
            // Get the user's choice
            choice = DataValidInput::getIntInput(">>> ");
            try {
                // Based on the user's choice, perform the corresponding action
                switch (choice)
                {
                case 1: {
                    // Input the product details
                    int id;
                    std::string name;
                    int type;
                    int price;
                    int quantity;
                    id = DataValidInput::getIntInput("Enter Product ID: ");
                    name = DataValidInput::getStringInput("Enter Product Name: ");
                    type = DataValidInput::getIntInput("Enter 1 for Popular Product, 2 for Normal product: ");
                    // Validate the product type
                    if (type != 1 && type != 2) {
                        throw std::invalid_argument(" Invalid Product Type!");
                    }
                    price = DataValidInput::getIntInput("Enter Product Price: ");
                    quantity = DataValidInput::getIntInput("Enter Product Quantity: ");
                    // Add the product to the inventory
                    manager.addProduct(id, name, type, price, quantity);
                    break;
                }
                case 2: {
                    // Input the product ID
                    int id;
                    id = DataValidInput::getIntInput("Enter Product ID: ");
                    // Validate the ID
                    DataValidInput::validateId(id);

                    // Update the product details
                    manager.updateProduct(id);
                    break;
                }
                case 3:
                    // View the product details
                    manager.viewProduct();
                    break;
                    
                case 4: {
                    // Input the product ID
                    int id;
                    id = DataValidInput::getIntInput("Enter Product ID: ");
                    // Validate the ID
                    DataValidInput::validateId(id);
                    // Delete the product
                    manager.deleteProduct(id);
                    break;
                }
                case 5:
                    // Exit the program
                    done = true;
                    break;
                default:
                    // Invalid choice
                    std::cout << "Invalide choice. Please try again.\n";
                }
            } catch (const std::exception& e) {
                // Print the error message
                std::cout << "Error!" << e.what() << std::endl;
            }
        } while (choice != 5);
    }
};