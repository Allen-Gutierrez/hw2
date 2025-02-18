#include <sstream>
#include <iomanip>
#include <algorithm>
#include "book.h"
#include "util.h"

using namespace std;

// Constructor with elements taken from the Product class
Book::Book(const std::string& category, const std::string& name, 
            double price, int qty, const std::string& isbn, const std::string& author)
    : Product(category, name, price, qty), isbn_(isbn), author_(author)
{

}

// Destructor
Book::~Book() 
{

}

// Override keywords function
std::set<std::string> Book::keywords() const {

    std::set<std::string> keywords = parseStringToWords(name_ + " " + author_); // Creating keywords to hold and return the keywords
    // Add ISBN as a keyword
    keywords.insert(isbn_);
    return keywords;
}

// Override isMatch function
bool Book::isMatch(std::vector<std::string>& searchTerms) const {
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
std::string Book::displayString() const {
    std::ostringstream oss;
    oss << name_ << "\n"  
        << "Author: " << author_ << " " << "ISBN: " << isbn_ << "\n"
        << price_ << " " << qty_ << " left.";

    return oss.str();
}

// Override dump function
void Book::dump(std::ostream& os) const {
    os << category_ << "\n"
       << name_ << "\n"
       << price_ << "\n"
       << qty_ << "\n"
       << isbn_ << "\n"
       << author_ << "\n";
}
