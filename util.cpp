#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
    rawWords = convToLower(rawWords);
    std::set<std::string> keywords; // declaring a set of strings to be used to store the keywords

    string currentWord; // used to store the rawWord in use

    // using a for loop to go through the entire rawWord to find and seperate the word to a set of words
    for ( int i = 0; i < rawWords.length(); i++) {

        char c = rawWords[i]; // Gets the character from the string

        // Checking if the character is a letter of a hyphen
        if (isalnum(c)) {
            currentWord += c; // stores the character to the current word
        }
        else { // checking the currentWord is an actual word
            if (currentWord.length() >= 2) {
                keywords.insert(currentWord); // set into keywords and making all words lowercase to remove case sensitivity
            }
            currentWord.clear(); // reset the currentWord after placed in keywords
        }
    }

    // Safty checks 
    if (currentWord.length() > 1) { // checking the currentWord is an actual word
        keywords.insert(currentWord); // set into keywords and making all words lowercase to remove case sensitivity
    }

    return keywords;

}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
