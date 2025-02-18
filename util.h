#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>


/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates).
 *  Both functions should run in time O(n*log(n)) and not O(n^2)
 */
template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{
  std::set<T> ending; // keeping track of the final outcome

    typename std::set<T>::const_iterator track1; // tracking the s1 and go through it

    // go through the set and compare s1 and s2
    for (track1 = s1.begin(); track1 != s1.end(); track1++) {
        T item = *track1;
        if (s2.find(item) != s2.end()) {
            ending.insert(item);
        }
    }

    return ending; // return the final

}

template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{
  std::set<T> ending = s1; // making ending equal to s1 to unionize later

  ending.insert(s2.begin(), s2.end());

  return ending; // return the final

}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// Removes any leading whitespace
std::string &ltrim(std::string &s) ;

// Removes any trailing whitespace
std::string &rtrim(std::string &s) ;

// Removes leading and trailing whitespace
std::string &trim(std::string &s) ;
#endif
