/**
 * Outline: The tokStr function tokenizes a string given a token.
 * Date: 12/4/21
 * Author: Gabriel Mongaras
 * Input: A string and a token
 * Output: A vector of strings broken up by the token
 */




#include "tokStr.h"


std::vector<std::string> tokStr(std::string& str, std::string tok, int times) {
    // Vector to hold the tokenized string
    std::vector<std::string> tokenizedString;

    // Temporary string to hold each substring
    std::string substr;

    // The number of times the token was found
    int numTimes = 0;

    // The size of the token
    int tokSize = tok.size();

    // Iterate over all values in the string
    for (int i = 0; i < str.size(); i++) {
        // If the string size is greater than the token size and the
        // current ith value, check if the token is found
        if (i+tokSize < str.size()) {
            // If the substring from the ith value to the
            // ith value + token size is the token, then the token is
            // found. If this condition is true and the number of times the token is found
            // is less than the specified amount, add the substring to the vector
            if (str.substr(i, tokSize) == tok && (numTimes < times || times == -1)) {
                i += tokSize-1;
                numTimes++;

                // If the substring is not empty, add it to the vector
                if (!substr.empty()) {
                    tokenizedString.emplace_back(substr);
                }

                // Clear the substring
                substr.clear();
                continue;
            }
        }

        // Add the next character to the substring
        substr += str[i];
    }

    // Add the final substring to the vector
    if (!substr.empty()) {
        tokenizedString.emplace_back(substr);
    }

    // Return the vector of substring
    return tokenizedString;
}