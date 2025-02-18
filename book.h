#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include "product.h"


class Book : public Product {
public:  
    // Constructor
     Book(const std::string& category, const std::string& name, 
            double price, int qty, const std::string& isbn, const std::string& author);

    // Destuctor 
    virtual ~Book();

    // Override keywords function
    virtual std::set<std::string> keywords() const override;

    // Override isMatch function for detailed search
    virtual bool isMatch(std::vector<std::string>& searchTerms) const override;

    // Override displayString function
    virtual std::string displayString() const override;

    // Override dump function
    virtual void dump(std::ostream& os) const override;

private:
    std::string isbn_;
    std::string author_;

};

#endif