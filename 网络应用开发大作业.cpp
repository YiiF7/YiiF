#pragma once
#include <string>
#include <vector>

class User {
public:
    std::string username;
    std::string password;
    std::vector<std::string> cart;

    User(const std::string& uname, const std::string& pwd) : username(uname), password(pwd) {}
};

class UserManager {
private:
    std::vector<User> users;
public:
    bool registerUser(const std::string& username, const std::string& password);
    User* loginUser(const std::string& username, const std::string& password);
};

#include "User.h"

bool UserManager::registerUser(const std::string& username, const std::string& password) {
    for (const auto& user : users) {
        if (user.username == username) {
            return false; // User already exists
        }
    }
    users.emplace_back(username, password);
    return true;
}

User* UserManager::loginUser(const std::string& username, const std::string& password) {
    for (auto& user : users) {
        if (user.username == username && user.password == password) {
            return &user;
        }
    }
    return nullptr;
}
#pragma once
#include <string>
#include <vector>
#include "Product.h"

class Salesperson {
public:
    std::string id;
    std::string password;

    Salesperson(const std::string& id, const std::string& password) : id(id), password(password) {}

    void addProduct(ProductManager& pm, const std::string& name, double price, int stock);
    void modifyProduct(ProductManager& pm, const std::string& name, double price, int stock);
    void viewLogs();
};

class SalespersonManager {
private:
    std::vector<Salesperson> salespersons;
public:
    bool addSalesperson(const std::string& id, const std::string& password);
    Salesperson* loginSalesperson(const std::string& id, const std::string& password);
};

#include "Salesperson.h"
#include <iostream>

bool SalespersonManager::addSalesperson(const std::string& id, const std::string& password) {
    for (const auto& sp : salespersons) {
        if (sp.id == id) {
            return false; // Salesperson already exists
        }
    }
    salespersons.emplace_back(id, password);
    return true;
}

Salesperson* SalespersonManager::loginSalesperson(const std::string& id, const std::string& password) {
    for (auto& sp : salespersons) {
        if (sp.id == id && sp.password == password) {
            return &sp;
        }
    }
    return nullptr;
}

void Salesperson::addProduct(ProductManager& pm, const std::string& name, double price, int stock) {
    pm.addProduct(name, price, stock);
}

void Salesperson::modifyProduct(ProductManager& pm, const std::string& name, double price, int stock) {
    pm.modifyProduct(name, price, stock);
}

void Salesperson::viewLogs() {
    // Implement log viewing
    std::cout << "Viewing logs..." << std::endl;
}

#pragma once
#include <string>
#include <vector>
#include "Salesperson.h"

class Administrator {
public:
    std::string id;
    std::string password;

    Administrator(const std::string& id, const std::string& password) : id(id), password(password) {}

    void addSalesperson(SalespersonManager& spm, const std::string& id, const std::string& password);
    void resetSalespersonPassword(SalespersonManager& spm, const std::string& id, const std::string& newPassword);
    void viewSalesStats();
};

class AdministratorManager {
private:
    std::vector<Administrator> administrators;
public:
    bool addAdministrator(const std::string& id, const std::string& password);
    Administrator* loginAdministrator(const std::string& id, const std::string& password);
};
#include "Administrator.h"
#include <iostream>

bool AdministratorManager::addAdministrator(const std::string& id, const std::string& password) {
    for (const auto& admin : administrators) {
        if (admin.id == id) {
            return false; // Administrator already exists
        }
    }
    administrators.emplace_back(id, password);
    return true;
}

Administrator* AdministratorManager::loginAdministrator(const std::string& id, const std::string& password) {
    for (auto& admin : administrators) {
        if (admin.id == id && admin.password == password) {
            return &admin;
        }
    }
    return nullptr;
}

void Administrator::addSalesperson(SalespersonManager& spm, const std::string& id, const std::string& password) {
    spm.addSalesperson(id, password);
}

void Administrator::resetSalespersonPassword(SalespersonManager& spm, const std::string& id, const std::string& newPassword) {
    Salesperson* sp = spm.loginSalesperson(id, "");
    if (sp) {
        sp->password = newPassword;
    }
}

void Administrator::viewSalesStats() {
    // Implement sales stats viewing
    std::cout << "Viewing sales stats..." << std::endl;
}
#pragma once
#include <string>
#include <vector>
#include <iostream>

class Product {
public:
    std::string name;
    double price;
    int stock;

    Product(const std::string& name, double price, int stock) : name(name), price(price), stock(stock) {}
};

class ProductManager {
private:
    std::vector<Product> products;
public:
    void addProduct(const std::string& name, double price, int stock);
    void modifyProduct(const std::string& name, double price, int stock);
    void listProducts();
};
#include "Product.h"

void ProductManager::addProduct(const std::string& name, double price, int stock) {
    products.emplace_back(name, price, stock);
}

void ProductManager::modifyProduct(const std::string& name, double price, int stock) {
    for (auto& product : products) {
        if (product.name == name) {
            product.price = price;
            product.stock = stock;
            break;
        }
    }
}

void ProductManager::listProducts() {
    for (const auto& product : products) {
        std::cout << "Product: " << product.name << ", Price: " << product.price << ", Stock: " << product.stock << std::endl;
    }
}
#include <iostream>
#include "User.h"
#include "Salesperson.h"
#include "Administrator.h"
#include "Product.h"

int main() {
    UserManager userManager;
    SalespersonManager salespersonManager;
    AdministratorManager adminManager;
    ProductManager productManager;

    // Sample administrators and salespersons
    adminManager.addAdministrator("admin", "admin123");
    salespersonManager.addSalesperson("sales1", "sales123");

    int choice;
    std::string username, password;

    while (true) {
        std::cout << "1. User\n2. Salesperson\n3. Administrator\n4. Exit\nEnter your role: ";
        std::cin >> choice;

        if (choice == 1) {
            // User operations
            std::cout << "1. Register\n2. Login\nEnter your choice: ";
            std::cin >> choice;
            if (choice == 1) {
                std::cout << "Enter username: ";
                std::cin >> username;
                std::cout << "Enter password: ";
                std::cin >> password;
                if (userManager.registerUser(username, password)) {
                    std::cout << "Registration successful.\n";
                }
                else {
                    std::cout << "User already exists.\n";
                }
            }
            else if (choice == 2) {
                std::cout << "Enter username: ";
                std::cin >> username;
                std::cout << "Enter password: ";
                std::cin >> password;
                User* user = userManager.loginUser(username, password);
                if (user) {
                    std::cout << "Login successful.\n";
                    // User operations
                    while (true) {
                        std::cout << "1. Browse Products\n2. Add to Cart\n3. View Cart\n4. Logout\nEnter your choice: ";
                        std::cin >> choice;
                        if (choice == 1) {
                            productManager.listProducts();
                        }
                        else if (choice == 2) {
                            std::string productName;
                            std::cout << "Enter product name to add to cart: ";
                            std::cin >> productName;
                            user->cart.push_back(productName);
                            std::cout << "Added to cart.\n";
                        }
                        else if (choice == 3) {
