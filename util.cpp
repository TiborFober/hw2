#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
set<string> parseStringToWords(string rawWords)
{
    set<string> setWords;

    string word;

    for (size_t i = 0; i < rawWords.length(); i++)
    {
        char c = tolower(rawWords[i]);

        if (ispunct(c) || isspace(c)) // if punctuation or space, see if want to add word to set
        {
            if (word.length() >= 2)
            {
                setWords.insert(word);
            }
            word.clear();
        } 
        else // is a digit or letter
        {
            word.push_back(c);
        }
        
    }

    if (word.length() >= 2)
    {
        setWords.insert(word);
    }
    return setWords;
}








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
