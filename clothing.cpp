#include <sstream>
#include <iomanip>
#include <algorithm>
#include "clothing.h"
#include "util.h"

using namespace std;

// Constructor
Clothing::Clothing(const std::string& category, const std::string& name, 
                    double price, int qty, const std::string& size, const std::string& brand)
    : Product(category, name, price, qty), size_(size), brand_(brand) 
{

}

// Destructor
Clothing::~Clothing() 
{
    
}

// Override keywords function
std::set<std::string> Clothing::keywords() const {
    std::set<std::string> keywords = parseStringToWords(name_ + " " + brand_ + " "  + size_);
    return keywords;
}

// Override isMatch function
bool Clothing::isMatch(std::vector<std::string>& searchTerms) const {
    // Check if any of the search terms match the keywords
    for (std::vector<std::string>::const_iterator it = searchTerms.begin(); it != searchTerms.end(); ++it) {
        std::string term_lower = *it;
        std::transform(term_lower.begin(), term_lower.end(), term_lower.begin(), ::tolower);
        
        if (keywords().count(term_lower) > 0) {
            return true;
        }
    }
    return false;
}

// Override displayString function
std::string Clothing::displayString() const {
    std::ostringstream oss;
    oss << name_ << "\n"
        << "Size: " << size_ << " " << "Brand: " << brand_ << "\n"
        << price_ << " " << qty_ << " left.";
       
    return oss.str();
}

// Override dump function
void Clothing::dump(std::ostream& os) const {
    os << category_ << "\n"
       << name_ << "\n"
       << price_ << "\n"
       << qty_ << "\n"
       << size_ << "\n"
       << brand_ << std::endl;
}