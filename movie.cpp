#include <sstream>
#include <iomanip>
#include <algorithm>
#include "movie.h"
#include "util.h"

using namespace std;

// Constructor
Movie::Movie(const std::string& category, const std::string& name, 
                double price, int qty, const std::string& genre, const std::string& rating)
    : Product(category, name, price, qty), genre_(genre), rating_(rating) 
{

}

// Destructor
Movie::~Movie() 
{

}

// Override keywords function
std::set<std::string> Movie::keywords() const {
    std::set<std::string> keywords = parseStringToWords(name_ + " " + genre_ + " " + rating_);
    return keywords;
}

// Override isMatch function
bool Movie::isMatch(std::vector<std::string>& searchTerms) const {
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
std::string Movie::displayString() const {
    std::ostringstream oss;
    oss << name_ << "\n"
        << "Genre: " << genre_ << " " << "Rating: " << rating_ << "\n"
        << price_ << " " << qty_ << " left.";
        
    return oss.str();
}

// Override dump function
void Movie::dump(std::ostream& os) const {
    os << category_ << "\n"
       << name_ << "\n"
       << price_ << "\n"
       << qty_ << "\n"
       << genre_ << "\n"
       << rating_ << std::endl;
}