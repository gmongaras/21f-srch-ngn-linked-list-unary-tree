#include "tokStr.h"


std::vector<std::string> tokStr(std::string& str, char tok, int times) {
    // Vector to hold the tokenized string
    std::vector<std::string> tokenizedString;

    // Temporary string to hold each substring
    std::string substr;

    // The number of times the token was found
    int numTimes = 0;

    // Iterate over all values in the string
    for (int i = 0; i < str.size(); i++) {
        // If the current character is the token, and the number of times is
        // less than the specified amount, add the substring to the vector
        if (str[i] == tok && (numTimes < times || times == -1)) {
            numTimes++;

            // If the substring is not empty, add it to the vector
            if (!substr.empty()) {
                tokenizedString.emplace_back(substr);
            }

            // Clear the substring
            substr.clear();
            continue;
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