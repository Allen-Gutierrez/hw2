#ifndef CLOTHING_H
#define CLOTHING_H

#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include "product.h"

class Clothing : public Product {
public:  

    // Constructor
    Clothing(const std::string& category, const std::string& name, 
                double price, int qty, const std::string& size, const std::string& brand);

    // Override destructor
    virtual ~Clothing();

    // Override keywords function
    virtual std::set<std::string> keywords() const override;

    // Override isMatch function for detailed search
    virtual bool isMatch(std::vector<std::string>& searchTerms) const override;

    // Override displayString function
    virtual std::string displayString() const override;

    // Override dump function
    virtual void dump(std::ostream& os) const override;

private:
    std::string size_;
    std::string brand_;

};


#endif