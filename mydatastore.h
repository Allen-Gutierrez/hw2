#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include <map>
#include "product.h"
#include "datastore.h"
#include "user.h"

class MyDataStore : public DataStore {

public:
    // Constructor
    MyDataStore() = default;

    // Destructor
    ~MyDataStore() override;

    // adding Product, from datastore
    void addProduct(Product* p) override;

    // adding User, from datastore
    void addUser(User* u) override;

    // searching for a Product based on the keywords of the text, from datastore
    std::vector<Product*> search(std::vector<std::string>& terms, int type) override;

    // dump the product, from datastore
    void dump(std::ostream& ofile) override;

    // adding a product to the user's cart
    void addToCart(std::string username, Product* product);

    // view the products in the user's cart
    void viewCart(std::string username);

    // buy the products in the user's cart
    void buyCart(std::string username);

private: 
    std::set<Product*> products; // the set of products
    std::map<std::string,std::set<Product*>> keywordMap; // the keywordMap, used to add products in a set 
    
    std::map<std::string, User*> users; // the map of users, containg their username and class User

    std::map<std::string, std::vector<Product*>> carts; // user carts, username and Products

    // Helper functions for searching products
    std::set<Product*> searchProductsAnd(const std::vector<std::string>& terms); // search for And command
    std::set<Product*> searchProductsOr(const std::vector<std::string>& terms); // search for Or command

};

#endif