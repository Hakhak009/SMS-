#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stdexcept>
#include "Product.cpp"
#include "DataValidInput.cpp"
#include "ProductRepository.cpp"
#include "PopularProduct.cpp"
#include "NormalProduct.cpp"
#include "display.cpp"



class ProductManager : public ProductRepository{
private:
    std::vector<Product*> products;

    Product* findproductbyID(int id){
        auto it = std::find_if(products.begin(), products.end(),[id](Product* products){
            return products->getId() == id;
        });
        return (it != products.end()) ? *it : nullptr;
    }
public:
    ~ProductManager(){
        for (auto product : products) {
            delete product;
        }
    }
    void addProduct(int id, std::string name,int type, int price, int quantity) {
        if (type == 1) {
                    products.push_back(new PopularProduct(name, id, price, quantity));
                } else if (type == 2) {
                    products.push_back(new NormalProduct(name, id, price, quantity));
                } else {
                    throw std::invalid_argument("Invalid Product type.");
                }
    std::cout << "\nAdded Successfully.\n";
    }
    void updateProduct(int id){
        Product* product = findproductbyID(id);
        if(product == nullptr){
            throw std::invalid_argument("Product not found\n\n");
            return;
        }
        std::string newName;
        newName = DataValidInput::getStringInput("Enter Product name: ");

        product->setName(newName);
        std::cout << "\nUpdated successfully.\n";
    }
    void deleteProduct(int id){
        if (!confirmation()) {return;} 
        auto it = std::remove_if(products.begin(), products.end(),[id](Product* product){
            if(product->getId() == id){
                delete product;
                return true;
            }
            return false;
        });
        if(it != products.end()){
            products.erase(it, products.end());
            std::cout << "\nDeleted successfully.\n";
        } else {
            throw std::invalid_argument("Product not found\n");
        }
    }
    void viewProduct(){
        if (products.empty()) {
            throw std::invalid_argument("No product available\n");
            return;
        }
        displayProduct();
        for(const auto& product :products){
            product->displayname();
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
