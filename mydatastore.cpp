#include <algorithm>
#include <iostream>
#include "mydatastore.h"
#include "util.h"
#include "product.h" 
#include <sstream> 
#include <set>
#include <vector>
#include <string>


// deleting the objects from product and users
MyDataStore::~MyDataStore() {
    // Clean up dynamically allocated products and users
    for (std::set<Product*>::iterator p = products.begin(); p != products.end(); ++p) {
        delete *p;
    }
    for (std::map<std::string, User*>::iterator u = users.begin(); u != users.end(); ++u) {
        delete u->second;
    }
}

// adding the products recieved from the Product class 
void MyDataStore::addProduct(Product* p) {

    products.insert(p); // Add product to the set
    
    std::set<std::string> keywords = p->keywords(); // obtain the keywords for for loop
    // for loop through the Products to add 
    for (std::set<std::string>::iterator it = keywords.begin(); it != keywords.end(); it++) {
        std::string keyword = *it;
        keywordMap[keyword].insert(p);
    }
}

// adding a user recieved from the User class
void MyDataStore::addUser(User* u) {
    users.insert(std::make_pair(u->getName(), u)); // Add user to the set
}


std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type) {
    for (int i = 0; i < terms.size(); i++) {
        terms[i] = convToLower(terms[i]);
    }
    if (type == 0) {
        // AND search (intersection)
        std::set<Product*> result = searchProductsAnd(terms);
        return std::vector<Product*>(result.begin(), result.end());
    } else {
        // OR search (union)
        std::set<Product*> result = searchProductsOr(terms);
        return std::vector<Product*>(result.begin(), result.end());
    }
}

// dump the contents from products and users
void MyDataStore::dump(std::ostream& ofile) {
    // Output products
    ofile << "<products>\n";
    for (std::set<Product*>::iterator product = products.begin(); product != products.end(); ++product) {
         (*product)->dump(ofile); 
    }
    ofile << "</products>\n";
    // Output users
    ofile << "<users>\n";
    for (std::map<std::string, User*>::iterator user = users.begin(); user != users.end(); ++user) {
        user->second->dump(ofile); 
    }
    ofile << "</users>\n";
}

// Search for products matching all terms (AND logic)
std::set<Product*> MyDataStore::searchProductsAnd(const std::vector<std::string>& terms) {

    std::set<Product*> result;

    if (terms.empty()) {
        return result; // Return empty set if no terms are provided
    }

    std::string term = terms[0];
    result = keywordMap[term];

    // cycle through the terms to search the Products
    for (size_t i = 1; i < terms.size(); ++i) {
        term = terms[i];
        std::set<Product*> curr = keywordMap[term];
        result = setIntersection<Product*>(result,curr);
    }

    return result; // Return final set of products matching all terms

}

// Search for products matching any term (OR logic)
std::set<Product*> MyDataStore::searchProductsOr(const std::vector<std::string>& terms) {

    std::set<Product*> result;

    // Return empty set if no terms are provided
    if (terms.empty()) {
        return result;
    }

    std::string term = terms[0];
    result = keywordMap[term];

    // cycle through the terms to search the Products
    for (size_t i = 1; i < terms.size(); ++i) {
        term = terms[i];
        std::set<Product*> curr = keywordMap[term];
        result = setUnion<Product*>(result,curr);
    }

    return result; // Return the set of products that match any term

}

void MyDataStore::addToCart(std::string username, Product* product) {
    username = convToLower(username);
    // Check if user exists
    if (users.find(username) == users.end()) {
        std::cout << "Invalid Request" << std::endl;
        return;
    }

    // Add product to the user's cart
    carts[username].push_back(product);
    std::cout << "Added " << product->getName() << " to " << username << "'s cart." << std::endl;
}

void MyDataStore::viewCart(std::string username) {
    username = convToLower(username);
    // Check if user exists 
    if( users.find(username) ==  users.end()) {
        std::cout << "Invalid Username" << std::endl;
        return;
    }
    // for loop to check if user products in cart 
    std::vector<Product*> list = carts[username];
    for (int i = 0; i < list.size(); i++) {
        std::cout << "Item " << i+1 << std::endl;
        std::cout << list[i]->displayString() << std::endl;
    }
}

void MyDataStore::buyCart(std::string username) {
    username = convToLower(username);

    // check if user exists 
     if (carts.find(username) == carts.end()) {
        std::cout << "Invalid Username" << std::endl;
        return;
    }

    User* user = users[username]; // Get the user pointer
    std::vector<Product*> cart = carts[username]; // Get the user's cart
    std::vector<Product*> newCart; // newcart for cases when user cant get product

    // Calculate total cost and check product availability
    for (int i = 0; i < cart.size(); i++) {
        Product* product = cart[i]; // Dereference iterator to get product

        // Check if product is in stock or if user has enough balance to buy product
        if (product->getQty() == 0 || user->getBalance() < product->getPrice()) {
            newCart.push_back(product); // places the item into the newCart since user cant get it.
        } else {
            product->subtractQty(1);
            user->deductAmount(product->getPrice());
        }
        
    }

    carts[username] = newCart;
}