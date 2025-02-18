#ifndef MOVIE_H
#define MOVIE_H

#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include "product.h"

class Movie: public Product {
public:
    // Constructor
    Movie(const std::string& category, const std::string& name, 
            double price, int qty, const std::string& genre, const std::string& rating);

    // Override destructor
    virtual ~Movie();

    // Override keywords function
    virtual std::set<std::string> keywords() const override;

    // Override isMatch function for detailed search
    virtual bool isMatch(std::vector<std::string>& searchTerms) const override;

    // Override displayString function
    virtual std::string displayString() const override;

    // Override dump function
    virtual void dump(std::ostream& os) const override;

private:
    std::string genre_;
    std::string rating_;


};

#endif