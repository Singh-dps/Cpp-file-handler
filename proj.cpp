#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Product {
private:
    int productID;
    string productName;
    int quantity;
    double price;

public:
    Product(int id = 0, string name = "", int qty = 0, double pr = 0.0) {
        productID = id;
        productName = name;
        quantity = qty;
        price = pr;
    }
    
    int getID() {
        return productID;
    }
    
    string getName() {
        return productName;
    }
    
    int getQty() {
        return quantity;
    }
    
    double getPrice() {
        return price;
    }
    
    void setName(string name) {
        productName = name;
    }
    
    void setQty(int qty) {
        quantity = qty;
    }
    
    void setPrice(double pr) {
        price = pr;
    }
    
    void display() {
        cout << "ID: " << productID << " | Name: " << productName << " | Qty: " << quantity << " | Price: $" << price << endl;
    }
    
    void saveToFile(ofstream& file) {
        file << productID << endl;
        file << productName << endl;
        file << quantity << endl;
        file << price << endl;
    }
    
    void loadFromFile(ifstream& file) {
        file >> productID;
        file.ignore();
        getline(file, productName);
        file >> quantity;
        file >> price;
        file.ignore();
    }
};

class InventoryManager {
private:
    vector<Product> inventory;
    string filename;

    int findProduct(int id) {
        for (int i = 0; i < inventory.size(); i++) {
            if (inventory[i].getID() == id) {
                return i;
            }
        }
        return -1;
    }

public:
    InventoryManager(string file = "inventory.txt") {
        filename = file;
        loadFromFile();
    }
    
    void addProduct() {
        int id, qty;
        string name;
        double price;
        
        cout << "\nEnter Product ID: ";
        cin >> id;
        
        if (findProduct(id) != -1) {
            cout << "Product already exists!" << endl;
            return;
        }
        
        cin.ignore();
        cout << "Enter Product Name: ";
        getline(cin, name);
        cout << "Enter Quantity: ";
        cin >> qty;
        cout << "Enter Price: ";
        cin >> price;
        
        Product p(id, name, qty, price);
        inventory.push_back(p);
        
        cout << "Product added successfully!" << endl;
        saveToFile();
    }
    
    void updateProduct() {
        int id;
        cout << "\nEnter Product ID: ";
        cin >> id;
        
        int index = findProduct(id);
        if (index == -1) {
            cout << "Product not found!" << endl;
            return;
        }
        
        int qty;
        double price;
        
        cout << "Enter new Quantity: ";
        cin >> qty;
        cout << "Enter new Price: ";
        cin >> price;
        
        inventory[index].setQty(qty);
        inventory[index].setPrice(price);
        
        cout << "Product updated successfully!" << endl;
        saveToFile();
    }
    
    void deleteProduct() {
        int id;
        cout << "\nEnter Product ID: ";
        cin >> id;
        
        int index = findProduct(id);
        if (index == -1) {
            cout << "Product not found!" << endl;
            return;
        }
        
        inventory.erase(inventory.begin() + index);
        cout << "Product deleted successfully!" << endl;
        saveToFile();
    }
    
    void searchProduct() {
        int id;
        cout << "\nEnter Product ID: ";
        cin >> id;
        
        int index = findProduct(id);
        if (index != -1) {
            inventory[index].display();
        } else {
            cout << "Product not found!" << endl;
        }
    }
    
    void displayAll() {
        if (inventory.empty()) {
            cout << "\nNo products available!" << endl;
            return;
        }
        
        cout << "\n--- Product List ---" << endl;
        for (int i = 0; i < inventory.size(); i++) {
            inventory[i].display();
        }
        cout << "Total Products: " << inventory.size() << endl;
    }
    
    void saveToFile() {
        ofstream file(filename);
        
        if (!file) {
            cout << "Error opening file!" << endl;
            return;
        }
        
        file << inventory.size() << endl;
        
        for (int i = 0; i < inventory.size(); i++) {
            inventory[i].saveToFile(file);
        }
        
        file.close();
    }
    
    void loadFromFile() {
        ifstream file(filename);
        
        if (!file) {
            return;
        }
        
        int count;
        file >> count;
        file.ignore();
        
        inventory.clear();
        
        for (int i = 0; i < count; i++) {
            Product p;
            p.loadFromFile(file);
            inventory.push_back(p);
        }
        
        file.close();
    }
};

int main() {
    InventoryManager manager;
    int choice;
    
    cout << "Inventory Management System" << endl;
    
    while (true) {
        cout << "\n1. Add Product" << endl;
        cout << "2. Update Product" << endl;
        cout << "3. Delete Product" << endl;
        cout << "4. Search Product" << endl;
        cout << "5. Display All Products" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        
        if (choice == 1) {
            manager.addProduct();
        } else if (choice == 2) {
            manager.updateProduct();
        } else if (choice == 3) {
            manager.deleteProduct();
        } else if (choice == 4) {
            manager.searchProduct();
        } else if (choice == 5) {
            manager.displayAll();
        } else if (choice == 6) {
            cout << "Thank you!" << endl;
            break;
        } else {
            cout << "Invalid choice!" << endl;
        }
    }
    
    return 0;
}